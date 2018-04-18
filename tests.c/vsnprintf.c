#include <stdio.h>

char buffer[200];
int i, j;
double fp;
char *s = "baltimore";
char c;

int main(void)
{
   	c = 'l';
   	i = 35;
   	fp = 1.7320508;

   	/* Format and print various data */
   	j = snprintf(buffer, 6, "%s\n", s);
	printf("j= %d", j);
   	j += snprintf(buffer+j, 6, "%c\n", c);
	printf("j= %d", j);
   	j += snprintf(buffer+j, 6, "%d\n", i);
	printf("j= %d", j);
   	j += snprintf(buffer+j, 6, "%f\n", fp);
	printf("j= %d", j);
   	printf("string:\n%s\ncharacter count = %d\n", buffer, j);
}

