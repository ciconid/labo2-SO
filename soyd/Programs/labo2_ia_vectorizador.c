#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define BLOQUE 10

typedef struct {
	char **datos;
	int capacidad;
	int usados;
} array_string;

typedef struct {
	int *datos;
	int capacidad;
	int usados;
} array_int;

// inicializadores de arrays
void init_array_string(array_string *array) {
	array->datos = malloc(BLOQUE * sizeof(char*) );
	array->capacidad = BLOQUE;
	array->usados = 0;
}
void init_array_int(array_int *array) {
	array->datos = malloc(BLOQUE * sizeof(int) );
	array->capacidad = BLOQUE;
	array->usados = 0;
}

// agregar un string al array dinamico
void insertArray(array_string* array, const char* string) {
	if (array->usados == array->capacidad ) {
		// aumentar capacidad
		array->capacidad += BLOQUE;
		array->datos = realloc(array->datos, array->capacidad * sizeof(char*) );
		if (array->datos == NULL) {
			perror("Error en realloc");
			exit(EXIT_FAILURE);
		}
	}

	// agregar al array
	array->datos[array->usados] = malloc(strlen(string) + 1);
	strcpy(array->datos[array->usados], string);
	array->usados++;
}

void insert_array_int(array_int *array, int num) {
	if (array->usados == array->capacidad ) {
		// aumentar capacidad
		array->capacidad += BLOQUE;
		array->datos = realloc(array->datos, array->capacidad * sizeof(int) );
		if (array->datos == NULL) {
			perror("Error en realloc");
			exit(EXIT_FAILURE);
		}
	}

	// agregar al array
	//array->datos[array->usados] = malloc(strlen(string) + 1);
	//strcpy(array->datos[array->usados], string);
	array->datos[array->usados] = num;
	array->usados++;
}

int contains(array_string* array, const char* string) {
	// si encuentra la palabra, devuelve su posicion, sino -1
	for (int i = 0; i < array->usados; i++) {
		if (strcmp(array->datos[i], string) == 0) {
			return i;
		}	
	}
	
	return -1;
}


// imprimir array
void imprimir_array_string(array_string *array) {
	for (int i = 0; i < array->usados; i++) {
		printf("%s ", array->datos[i]);
	}
	printf("\n");
}

void imprimir_array_int(array_int *array) {
	for (int i = 0; i < array->usados; i++) {
		printf("%d ", array->datos[i]);
	}
	printf("\n");
}

// liberar memoria
void free_array_string(array_string* array) {
	for (int i = 0; i < array->usados; i++) {
		free(array->datos[i]);
	}
	free(array->datos);
	array->datos = NULL;
}
void free_array_int(array_int *array) {
	//for (int i = 0; i < array->usados; i++) {
	//	free(array->datos[i]);
	//}
	free(array->datos);
	array->datos = NULL;
}

//toLower y limpiar especiales
void limpiar_y_to_lower(char* palabra) {
	int i,j= 0;
	for (int i = 0; palabra[i] != '\0'; i++) {
		if (isalnum((unsigned char) palabra[i]) ) {
			//printf("palabra[i]=%c \n", palabra[i]);

			palabra[j] = tolower(palabra[i]);
			j++;
		} 
	}
	palabra[j] = '\0';
}

int main(int arcg, char* argv[]) {
	//printf("Vectorizando... \n");
	//sleep(60);

	// abrir archivo
	char *path_ruta_archivo = "./data/";
	char *nombre_archivo = argv[1]; // esta validado en labo2_ia
	char ruta_archivo[strlen(path_ruta_archivo) + strlen(nombre_archivo) + 1];				 strcpy(ruta_archivo, path_ruta_archivo);
	strcat(ruta_archivo, nombre_archivo);

	FILE* archivo = fopen(ruta_archivo, "r");
 	if (archivo == NULL) {
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);
	}	

	// inicializo arrays
	array_string vocabulario;
	init_array_string(&vocabulario);

	array_int vector;
	init_array_int(&vector);

	// leer archivo 
	char palabra[100];
	while (fscanf(archivo, "%99s", palabra) == 1 ) {
		//printf("%s \n",palabra);
		limpiar_y_to_lower(palabra);

		// empezar a poblar vocab y vector
		int posicion = contains(&vocabulario, palabra);
		if (posicion == -1 ){
			insertArray(&vocabulario, palabra);
			insert_array_int(&vector, 1);
		} else {
			vector.datos[posicion]++;
		}

	}

	// abro/creo archivo de salida
	char nombre_salida[strlen(argv[1])];
	strcpy(nombre_salida, argv[1]);
	nombre_salida[strlen(nombre_salida) - 4] = '\0'; // le saco el .txt
	char *fin_nombre_salida = "_vector.txt"; 
	char ruta_salida[strlen(path_ruta_archivo) + strlen(nombre_salida) +
	       	strlen(fin_nombre_salida) + 1];
	strcpy(ruta_salida, path_ruta_archivo);
	strcat(ruta_salida, nombre_salida);
	strcat(ruta_salida, fin_nombre_salida);

	FILE *salida = fopen(ruta_salida, "w");
	if (salida == NULL) {
		perror("Error al crear el archivo");
		exit(EXIT_FAILURE);
       	}

	// escribir en archivo de salida Vocabulario y Vector
	fprintf(salida, "Vocabulario: [");
	for (int i = 0; i < vocabulario.usados; i++) {
		if (i == 0) {
			fprintf(salida, "%s", vocabulario.datos[i]);
		} else {
			fprintf(salida, ", %s", vocabulario.datos[i]);
		}
	}
	fprintf(salida, "] \n");

	fprintf(salida, "Vector: [");
	for (int i = 0; i < vector.usados; i++) {
		if (i == 0) {
			fprintf(salida, "%d", vector.datos[i]);
		} else {
			fprintf(salida, ", %d", vector.datos[i]);
		}
	}
	fprintf(salida, "] \n");






	// imprimir arrays PARA TESTEAR NOMAS
	//printf("Vocabulario: \n");
	//imprimir_array_string(&vocabulario);
	//printf("Vector: \n");
	//imprimir_array_int(&vector);
	//printf("------------ \n");



	// cerrar archivos abiertos y liberar memoria de arrays
	free_array_string(&vocabulario);
	free_array_int(&vector);
	fclose(archivo);
	fclose(salida);

	//printf("** saliendo de vectorizador ** \n");
	exit(EXIT_SUCCESS);
}


