#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <inttypes.h>

#define EXAMPLE_PORT 3937
#define EXAMPLE_GROUP "239.0.2.129"

//#define EXAMPLE_GROUP "239.0.2.154"
//#define EXAMPLE_PORT 3937

struct mcast_msg {
	uint8_t  end;
	uint32_t size;
	uint8_t  type;
	uint32_t id;
	uint16_t chunk_num;
	uint8_t  total_chunks;
	uint8_t  sep;
	char    *data;
};

/*
 #Struct of header - first 12 bytes
 # end   xmlsize   type   ?  id        chunk# *10   total chunks     \0
 # --   --------   -----  ------  ----  ---------  -------------      --
 # 00   00 00 00    F1    X 0 00   00     00 00          00           00
 #FIXME: XMLsize print is incorrect
 data = socket.recv(1500)
 chunk = {}
 chunk["end"] = struct.unpack('B',data[:1])[0]
 chunk["size"] = struct.unpack('>HB',data[1:4])[0]
 chunk["filetype"] = struct.unpack('B',data[4:5])[0]
 chunk["fileid"] = struct.unpack('>H',data[5:7])[0]&0x0fff
 chunk["chunk_number"] = struct.unpack('>H',data[8:10])[0]/0x10
 chunk["chunk_total"] = struct.unpack('B',data[10:11])[0]
 chunk["data"] = data[12:]
 */

struct mcast_msg *
unpack(uint8_t * data)
{
	if (!data) return NULL;

	struct mcast_msg *mc = malloc(sizeof(struct mcast_msg));

	mc->end = (data[0] << 0);
	mc->size = (data[3] << 0) | (data[2] << 8) | (data[1] << 16);
	mc->type = (data[4] << 0);
//	mc->id = ((data[6] << 0) | (data[5] << 8)) & 0x0fff;
	mc->id = ((data[7] << 0) | (data[6] << 8) | (data[5] << 16)) & 0x0fff;
	mc->chunk_num = ((data[9] << 0) | (data[8] << 8)) / 0x10;
	mc->total_chunks = (data[10] << 0);
	mc->data = strdup((char *)&data[12]);

	return mc;
}

void
mcast_msg_free(struct mcast_msg *msg)
{
	if (!msg) return;

	if (msg->data) free(msg->data);
	free(msg);
}

int
main()
{
	struct sockaddr_in addr;
	int                sock;
	int                cnt;
	socklen_t          addrlen;
	struct ip_mreq     mreq;
	struct mcast_msg  *msg = NULL;
	int                size;
	uint8_t            data[300*1024];


	/* set up socket */
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {
		perror("socket");
		exit(1);
	}

	size = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &mreq, sizeof(mreq));
	if (size < 0) {
		perror("setsockopt mreq - reuse");
		exit(1);
	}

	bzero((char *)&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(EXAMPLE_PORT);
	addrlen = sizeof(addr);

	if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("bind");
		exit(1);
	}

	mreq.imr_multiaddr.s_addr = inet_addr(EXAMPLE_GROUP);
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);

	size = setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
	if (size < 0) {
		perror("setsockopt mreq");
		exit(1);
	}


	// Esperamos por el primer fichero completo
	msg->end = 0;
	while (!msg->end) {
		bzero(data, sizeof(data));
		recvfrom(sock, data, sizeof(data), 0, (struct sockaddr *)&addr, &addrlen);
		msg = unpack(data);

		if (msg->end) break;
	}

	uint8_t xml[2001]; // buffer para guardar el xml
	while (1) {
		bzero(data, sizeof(data));
		cnt = recvfrom(sock, data, sizeof(data), 0, (struct sockaddr *)&addr, &addrlen);
		if (cnt < 0) {
			perror("recvfrom");
			exit(1);
		} else if (cnt == 0) {
			break;
		}

		msg = unpack(data);
		strcat((char *)xml, (const char *)msg->data);
		printf("end: %u size: %u type: %u id: %u, chunk_num: %u, chunk_total: %u data size: %lu\n",
		       msg->end, msg->size, msg->type, msg->id,
		       msg->chunk_num, msg->total_chunks,
		       strlen(msg->data));

		if (msg->end) break;
	}
	if (msg->end) printf("------------------------------------\n");
	xml[strlen((char *)xml) - 4] = 0; // Hay que quitar los últimos 4 bytes... separación??¿?¿?¿?
	printf("XML:\n%s\n", xml);
	if (msg->end) printf("------------------------------------\n");

	return EXIT_SUCCESS;
}

