#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFSIZE   1536
#define TTL_VALUE 2
#define TEST_ADDR "239.0.2.129"
#define TEST_PORT 3937
#define LOOPMAX 10

/**
 * C++ version 0.4 char* style "itoa":
 *
 * Written by Lukás Chmela
 * http://www.strudel.org.uk/itoa/
 *
 * Released under GPLv3.
 */
char* itoa(int value, char* result, int base)
{
	// check that the base if valid
	if (base < 2 || base > 36) {
		*result = '\0';
		return result;
	}

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
	} while ( value );

	// Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';
	*ptr-- = '\0';
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
	return result;
}


int main()
{
	struct sockaddr_in stLocal, stTo, stFrom;
	char achIn[BUFSIZE];
	char achOut[] = "Message number:              ";
	int s;
	struct ip_mreq stMreq;
	int iTmp, i;

	/* get a datagram socket */
	s = socket(AF_INET, SOCK_DGRAM, 0);

	/* avoid EADDRINUSE error on bind() */
	iTmp = true;
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *)&iTmp, sizeof(iTmp));

	/* name the socket */
	stLocal.sin_family = 	  AF_INET;
	stLocal.sin_addr.s_addr = htonl(INADDR_ANY);
	stLocal.sin_port = 	  htons(TEST_PORT);
	bind(s, (struct sockaddr*) &stLocal, sizeof(stLocal));

	/* join the multicast group. */
	stMreq.imr_multiaddr.s_addr = inet_addr(TEST_ADDR);
	stMreq.imr_interface.s_addr = INADDR_ANY;
	setsockopt(s, IPPROTO_IP,
	           IP_ADD_MEMBERSHIP,
	           (char *)&stMreq,
	           sizeof(stMreq));

	/* set TTL to traverse up to multiple routers */
	iTmp = TTL_VALUE;
	setsockopt(s,
	           IPPROTO_IP,
	           IP_MULTICAST_TTL,
	           (char *)&iTmp,
	           sizeof(iTmp));

	/* disable loopback */
	iTmp = false;
	setsockopt(s,
	           IPPROTO_IP,
	           IP_MULTICAST_LOOP,
	           (char *)&iTmp,
	           sizeof(iTmp));

	/* assign our destination address */
	stTo.sin_family =      AF_INET;
	stTo.sin_addr.s_addr = inet_addr(TEST_ADDR);
	stTo.sin_port =        htons(TEST_PORT);

	for (i = 0; i < LOOPMAX; i++) {
		int addr_size = sizeof(struct sockaddr_in);
		static int iCounter = 1;
		int i;

		/* send to the multicast address */
		itoa(iCounter++, &achOut[16], 10);
		i = sendto(s, achOut, sizeof(achOut),
		           0,(struct sockaddr*)&stTo, addr_size);
		if (i < 0) {
			perror("sendto() failed\n");
			exit(1);
		}

		i = recvfrom(s, achIn, BUFSIZE, 0,
		             (struct sockaddr*)&stFrom,
		             (socklen_t *)&addr_size);

		if (i < 0) {
			perror("recvfrom() failed\n");
			exit(1);
		}
		printf("From host:%s port:%d, %s\n",
		       inet_ntoa(stFrom.sin_addr),
		       ntohs(stFrom.sin_port), achIn);
	}
}


