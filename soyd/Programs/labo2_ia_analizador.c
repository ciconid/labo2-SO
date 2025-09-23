#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define CANT_PALABRAS 5

char *positivas[5] = {
	"hola",
	"bien",
	"estas",
	"todo",
	"regio"
};
char *negativas[5] = {
	"mal",
	"medio",
	"triste",
	"topo",
	"gigio"
};


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

int contains(char **array, const char* string) {
	// si encuentra la palabra, devuelve su posicion, sino -1
	for (int i = 0; i < CANT_PALABRAS; i++) {
		if (strcmp(array[i], string) == 0) {
			return i;
		}	
	}
	
	return -1;
}

int main(int argc, char *argv[]) {
	//printf("Analizando... \n");
	//sleep(60);

	// abrir archivo
	char *path_archivo = "./data/";
	char *nombre_archivo = argv[1];
	char ruta_archivo[strlen(path_archivo) + strlen(nombre_archivo) + 1];
	strcpy(ruta_archivo, path_archivo);
	strcat(ruta_archivo, nombre_archivo);

	FILE *archivo = fopen(ruta_archivo, "r");
 	if (archivo == NULL) {
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);
	}	

	// leer archivo
	int resultado_numerico = 0;
	char palabra[100];
	while (fscanf(archivo, "%99s", palabra) == 1 ) {
		//printf("%s \n", palabra);
		limpiar_y_to_lower(palabra);

		if (contains(positivas, palabra) >= 0) {
			// está en el array
			resultado_numerico++;
		}
		if (contains(negativas, palabra) >= 0) {
			// está en el array
			resultado_numerico--;
		}
		

	}


	// abrir archivo de salida
	char nombre_salida[strlen(nombre_archivo)];
	strcpy(nombre_salida, nombre_archivo);
	nombre_salida[strlen(nombre_salida) - 4] = '\0'; // le saco el .txt
	char *fin_nombre_salida = "_analisis.txt";
	char ruta_salida[strlen(path_archivo) + strlen(nombre_salida) + 
		strlen(fin_nombre_salida) + 1];
	strcpy(ruta_salida, path_archivo);
	strcat(ruta_salida, nombre_salida);
	strcat(ruta_salida, fin_nombre_salida);

	FILE *salida = fopen(ruta_salida, "w");	

	// escribir resultado_numerico en archivo de salida
	char resultado[10];	
	if (resultado_numerico > 0) {
		strcpy(resultado, "positivo\n");
	} else if (resultado_numerico < 0) {
		strcpy(resultado, "negativo\n");
	} else {
		strcpy(resultado, "neutro\n");
	}


	fprintf(salida, resultado);









	// cerrar archivos
	fclose(salida);
	fclose(archivo);



	//printf("** saliendo de analizador **\n");
	exit(EXIT_SUCCESS);
}
