#include <stdio.h>
#include <string.h>

union Data {
	int i;
	float f;
	char s[20];
};

int main()
{
	union Data data;

	data.i = 10;
	printf("data.i : %d data.f: %f data.s: %s\n", data.i, data.f, data.s);

	data.f = 220.5;
	printf("data.i : %d data.f: %f data.s: %s\n", data.i, data.f, data.s);

	strcpy(data.s, "C Programming");
	printf("data.i : %d data.f: %f data.s: %s\n", data.i, data.f, data.s);

	return 0;
}
