#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#define BIT(var, pos) (((var) >> (31 - pos)) & 1)
void bin(uint32_t n) {
    uint32_t i;
    for (i = 1 << 31; i > 0; i = i / 2)
        (n & i) ? printf("1") : printf("0");
}

void bin2(uint32_t n) {
    /* step 1 */
    if (n > 1)
        bin2(n / 2);

    /* step 2 */
    printf("%d", n % 2);
}

void bin3(uint32_t n) {
    uint32_t i;
    for (i = 0; i < 32; i++) {
        putchar(BIT(n, i) ? '1' : '0');
    }
}

int main(void) {
    const char fname[] = "ips.txt";

    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    size_t lines = 0;
    struct in_addr in;

    fp = fopen(fname, "r");
    while ((read = getline(&line, &len, fp)) != -1) {
        strtok(line, "\n");

        inet_aton(line, &in);
        printf("%s -> [", line);
        bin(in.s_addr);
        printf("] - [");
        bin2(in.s_addr);
        printf("] - [");
        bin3(in.s_addr);
        printf("]\n");

        lines++;
    }

    fclose(fp);
    if (line)
        free(line);

    printf("%zu lines read\n", lines);

    return 1;
}
