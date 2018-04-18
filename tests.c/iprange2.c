#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    unsigned int ip[4], ip_min[4], ip_max[4], netmask, tmp1, tmp2;
    char ip_string[19];

    for (; fgets(ip_string, 19, stdin) == NULL; perror(
             	"Please enter an IP and a subnetwork mask!\nEg.:192.168.1.254/32"))
        ;
    sscanf(ip_string, "%d.%u.%u.%u/%u", &ip[0], &ip[1], &ip[2], &ip[3],
            &netmask);
    /*Set the bytes which won't be changed*/
    for (tmp1 = tmp2 = netmask / 8; tmp1 > 0; tmp1--) {
        ip_min[tmp1 - 1] = ip[tmp1 - 1];
        ip_max[tmp1 - 1] = ip[tmp1 - 1];
    }
    /*Set the bytes which should be 0ed or 255ed.*/
    for (tmp1 = tmp2, ++tmp2; tmp2 < 4; tmp2++) {
        ip_min[tmp2] = 0;
        ip_max[tmp2] = 255;
    }
    /* Finally set the one which has to be shifted.*/
    if (tmp1 < 4) {
        tmp2 = 8 - netmask % 8;
        ip_min[tmp1] = ip[tmp1] >> tmp2;
        ip_min[tmp1] <<= tmp2;
        ip_max[tmp1] = ip_min[tmp1] + pow(2, tmp2) - 1;
    }
    printf("Valid addresses range from %u.%u.%u.%u to %u.%u.%u.%u\n", ip_min[0],
            ip_min[1], ip_min[2], ip_min[3], ip_max[0], ip_max[1], ip_max[2],
            ip_max[3]);
    return 0;
}
