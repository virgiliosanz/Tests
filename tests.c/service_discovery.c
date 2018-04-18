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

#define DATA_SIZE 1536
#define EXAMPLE_PORT 3937
// Service Discovery
//#define EXAMPLE_GROUP "239.0.2.129"
// Canales para Madrid
//#define EXAMPLE_GROUP "239.0.2.154"
// Programación de mañana
#define EXAMPLE_GROUP "239.0.2.131"


//#define EXAMPLE_GROUP "239.0.2.154"
//#define EXAMPLE_PORT 3937

// Ver página 59
struct multicast_s {
	uint8_t end;
	uint32_t size;
	uint8_t type;
	uint32_t id;
	uint16_t chunk_num;
	uint8_t total_chunks;
	uint8_t sep;
	char data[DATA_SIZE - 12 + 1];
};
typedef struct multicast_s multicast_s;

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

void
unpack(const uint8_t *data, multicast_s *mc)
{
	mc->end = (data[0] << 0);
	mc->size = (data[3] << 0) | (data[2] << 8) | (data[1] << 16);
	mc->type = (data[4] << 0);
	mc->id = ((data[6] << 0) | (data[5] << 8)) & 0x0fff;
	mc->chunk_num = ((data[9] << 0) | (data[8] << 8)) & 0x10;
	mc->total_chunks = (data[10] << 0);
	strcpy(mc->data, (char *)&data[12]);
}

int
main()
{
	struct sockaddr_in addr_in;
	struct sockaddr *addr = (struct sockaddr *)&addr_in;
	int sock, cnt;
	socklen_t addrlen;
	struct ip_mreq mreq;
	multicast_s msg;
	int size;
	uint8_t data[DATA_SIZE + 1];

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

	memset((char *)&addr_in, 0, sizeof(addr_in));
	addr_in.sin_family = AF_INET;
	addr_in.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_in.sin_port = htons(EXAMPLE_PORT);
	addrlen = sizeof(addr_in);

	if (bind(sock, addr, addrlen) < 0) {
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
	msg.end = 0;
	while (!msg.end) {
                memset(data, 0, sizeof(data));
		recvfrom(sock, data, sizeof(data), 0, addr, &addrlen);
		unpack(data, &msg);

		if (msg.end) break;
	}
	printf("Empezamos con el siguiente al %d", msg.type);
	printf("end: %u size: %u type: %u id: %u, chunk_num: %u, chunk_total: %u data size: %lu\n\n",
	       msg.end, msg.size, msg.type, msg.id, msg.chunk_num, msg.total_chunks, strlen(msg.data));
/*
	const char *fname = "service_discovery.xml";
	FILE *f = fopen(fname, "w");
*/
	while (1) {
		// printf("Receiving...");
                memset(data, 0, sizeof(data));
		cnt = recvfrom(sock, data, sizeof(data), 0, addr, &addrlen);
		// printf("%d bytes", cnt);
		if (cnt < 0) {
			perror("recvfrom");
			exit(1);
		} else if (cnt == 0) {
			printf("Cnt == 0");
			break;
		}

		unpack(data, &msg);
		if (msg.end) {
			printf("end: %u size: %u type: %u id: %u, chunk_num: %u, chunk_total: %u data size: %lu cnt: %d\n",
		     	       msg.end, msg.size, msg.type, msg.id, msg.chunk_num, msg.total_chunks, strlen(msg.data), cnt);
		}
/*
		printf("DATA:\n\n%s\n\n", msg.data);

		fputs(msg.data, f);
        	if (msg.end) {
//			break;
        	}
*/
	}
	//xml[strlen((const char *)xml) - 4] = 0; // Hay que quitar los últimos 4 bytes... separación??¿?¿?¿?

//	fclose(f);
//	printf("Write xml to %s", fname);

	return EXIT_SUCCESS;
}
