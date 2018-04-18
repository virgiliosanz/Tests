#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

struct {
    char ip[16];
    size_t asn;
} ips[] = {{"213.37.69.31", 6739},
           {"92.123.73.11", 20940},
           {"212.89.0.56", 12946},
           {"172.217.18.163", 15169},
           {"63.245.215.53", 36856},
           {"38.229.36.110", 23028},
           {"5.56.58.219", 57286},
           {"52.222.151.234", 16509},
           {"157.240.2.35", 32934},
           {"88.221.76.60", 20940},
           {{0}, 0}};

struct {
    char network[20];
    int number;
    uint8_t mask;
} asns[] = {{"213.37.0.0/16", 6739, 16},    {"92.123.73.0/24", 20940, 24},
            {"212.89.0.0/19", 12946, 19},   {"63.245.208.0/20", 36856, 20},
            {"172.217.0.0/16", 15169, 16},  {"172.217.0.0/24", 15169, 24},
            {"38.229.32.0/19", 23028, 19},  {"5.56.56.0/22", 57286, 22},
            {"52.222.148.0/22", 16509, 22}, {"157.240.2.0/24", 32934, 24},
            {"88.221.76.0/22", 20940, 22},  {{0}, 0, 0}};

int main() {
    int i = 0, j = 0;
    char network[19];
    int bits;
    uint32_t mask, ip, net;
    struct in_addr net_addr, ip_addr;

    while (0 != asns[i].number) {
	    strcpy(network, asns[i].network);
	    strtok(network, "/");
	    bits = atoi(strtok(NULL, "/"));

        inet_aton(network, &net_addr);
        net = ntohl(net_addr.s_addr); // Machine ENDIAN

        printf("IPs in %s/%d\n", network, bits);
        j = 0;
        while (0 != ips[j].asn) {
            inet_aton(ips[j].ip, &ip_addr);
        	ip = ntohl(ip_addr.s_addr); // Machine ENDIAN
			mask = -1 << (32 - bits);
            net &= mask;
            if ((ip & mask) == net) {
                printf("%s (%zu) is in %s (%d)\n", ips[j].ip, ips[j].asn,
                       asns[i].network, asns[i].number);
            }
            j++;
        }

        i++;
    }
}
