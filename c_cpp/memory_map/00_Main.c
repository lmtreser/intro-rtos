#include <stdio.h>
#include <stdlib.h>

// Variable global en el segmento de datos
int global_data = 10;

// Variable global no inicializada en el segmento BSS
int global_bss;

int main() {
	
	// Variable local en el segmento stack
	int stack_var = 5;
	
	// Asignación dinámica en el segmento heap
	int* heap_var = (int*)malloc(sizeof(int));
	*heap_var = 7;
	
	// Segmento de código
	printf("Global Data: %d\n", global_data);
	printf("Stack Variable: %d\n", stack_var);
	printf("Heap Variable: %d\n", *heap_var);
	
	// Liberar memoria asignada dinámicamente
	free(heap_var);
}
