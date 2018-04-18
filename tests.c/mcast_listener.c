/*
 * listener.c -- joins a multicast group and echoes all data it receives from
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


#define LISTEN_PORT 3937
#define MULTICAST_IP "239.0.2.129"
#define MSGBUFSIZE 1024

int main()
{
    	int sd;
    	// create what looks like an ordinary UDP socket
    	if ((sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        	perror("socket");
        	abort();
    	}

    	// allow multiple sockets to use the same port number
    	u_int reuse = 1;
    	if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        	perror("Reusing ADDR failed");
        	abort();
    	}

    	// bind to receive address
    	struct sockaddr_in addr;
    	memset(&addr, 0, sizeof(addr));
    	addr.sin_family      = AF_INET;
    	addr.sin_addr.s_addr = htonl(INADDR_ANY);
    	addr.sin_port        = htons(LISTEN_PORT);
    	if (bind(sd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        	perror("bind");
        	abort();
    	}

    	// use setsockopt() to request that the kernel join a multicast group
    	struct ip_mreq mreq;
    	mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_IP);
    	mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    	if (setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
        	perror("setsockopt");
        	abort();
    	}

    	printf("listening for %s on port %d\n", MULTICAST_IP, LISTEN_PORT);

    	/* now just enter a read-print loop */
    	char msgbuf[MSGBUFSIZE];
    	socklen_t addrlen = sizeof(addr);
    	int recv_bytes;
    	while (1) {
		memset(msgbuf, 0, MSGBUFSIZE);
		memset(&addr, 0, addrlen);
        	recv_bytes = recvfrom(sd, msgbuf, MSGBUFSIZE, 0, (struct sockaddr *)&addr, &addrlen);
        	if (recv_bytes < 0) {
            		perror("recvfrom");
            		abort();
        	} else if (0 == recv_bytes) {
        		break;
        	}
        	printf("%s: received (%d -> %lu): >%s<\n",
        	       inet_ntoa(addr.sin_addr), recv_bytes,  strlen(msgbuf), msgbuf);
    	}

    	if (setsockopt(sd, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
        	perror("setsockopt");
        	abort();
    	}
	close(sd);


    	return 0;
}


