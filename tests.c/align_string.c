#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* if room_width < 0 align right */
void align_str(char* dest, const char* src, int room_width)
{
    int len = strlen(src);
    int width = abs(room_width);
    int i;

    // align right
    if (0 > room_width) {
        for (i = 0; i < (width - len); i++) { *dest = ' '; dest++; }
        while (i < width) { *dest = *src; dest++; src++; i++; }
    }
    else {
        for (i = 0; i < len; i++) { *dest = *src; dest++; src++; }
        while (i < width) { *dest = ' '; dest++; i ++; }
    }
}

int main()
{
    // pos = 3  y width 8
    char* src = "80";

    char* dest = strdup(">>>xxxxxxxx<<<");
    puts(dest);

    align_str(&dest[3], src, 8);
    puts(dest);

    char* dest2 = strdup(">>>xxxxxxxx<<<");
    align_str(&dest2[3], src, -8);
    puts(dest2);

    char* src2 = "123456789";
    char* dest3 = strdup(">>>xxxxxxxx<<<");
    align_str(&dest3[3], src2, 8);
    puts(dest3);


		return EXIT_SUCCESS;
}
