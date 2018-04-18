#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
   	size_t *numPtr, i;
   	size_t tamanyo=0;

   	printf("Introduzca el tamaño de la lista: ");
   	scanf("%zu", &tamanyo);

   	puts("Adjudicamos espacio a la lista.");
   	numPtr = (size_t *)malloc(tamanyo * sizeof(int));

   	for(i = 0; i < tamanyo; i++)
      		printf("%zu, ", numPtr[i] = rand() % 100 + 1);
	printf("\n");

   	numPtr = (size_t *)realloc(numPtr, tamanyo /= 2);
   	printf("Recortamos la lista a la mitad: %zu\n", tamanyo);
   	for(i = 0; i < tamanyo; i++)
      		printf("%zu, ", numPtr[i]);
	printf("\n");

   	numPtr = (size_t *)realloc(numPtr, tamanyo *= 3);
   	printf("Trplicamos la lista (y randomizamos los nuevos): %zu\n", tamanyo);

   	for(i = tamanyo / 3; i < tamanyo; i++)
      		numPtr[i] = rand() % 100 + 1;

   	for(i = 0; i < tamanyo; i++)
      		printf("%zu, ", numPtr[i]);
	printf("\n");


   	puts("Liberamos el espacio.");
   	free(numPtr);

   	return EXIT_SUCCESS;
}

