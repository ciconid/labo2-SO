#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h> // para usar isalnum(char) y tolower(char)
#include <string.h>

//toLower y limpiar especiales
void limpiar_y_to_lower(char *palabra) {
	int j= 0;
	for (int i = 0; palabra[i] != '\0'; i++) {
		if (isalnum((unsigned char) palabra[i]) ) {
			palabra[j] = tolower(palabra[i]);
			j++;
		} 
	}
	palabra[j] = '\0';
}


int main(int argc, char *argv[]) {

	FILE *archivo;
	FILE *salida;
	char palabra[100];

	// crear ruta_archivo
	char *inicio = "./data/";
	char *final = argv[1]; 
	char ruta_archivo[strlen(inicio) + strlen(final) + 1];
	strcpy(ruta_archivo, inicio);
	strcat(ruta_archivo, final);

	archivo = fopen(ruta_archivo, "r");
	if (archivo == NULL) {
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);
	}

	// crear ruta_tokens
	char *medio_tokens = argv[1];
	medio_tokens[strlen(medio_tokens) - 4] = '\0'; // le saco ".txt" a la cadena 
	char *final_tokens = "_tokens.txt";
	char ruta_tokens[strlen(inicio) + strlen(medio_tokens) + strlen(final_tokens) + 1];
	strcpy(ruta_tokens, inicio);
	strcat(ruta_tokens, medio_tokens);
	strcat(ruta_tokens, final_tokens);

	salida = fopen(ruta_tokens, "w"); 
	if (salida == NULL) {
		perror("Error al crear el archivo");
		exit(EXIT_FAILURE);
	}		


	// leer del original y escribir en archivo
	fprintf(salida, "[");
	bool primera_iteracion = true;
	while (fscanf(archivo, "%99s", palabra) == 1 ) {
		
		limpiar_y_to_lower(palabra);

		if (primera_iteracion) {
			fprintf(salida, "%s", palabra); 
			primera_iteracion = false;
		} else {
			fprintf(salida, ", %s", palabra); 
		}

	}
	fprintf(salida, "]\n");
	
	
	// cierres	
	fclose(archivo);
	fclose(salida);

	exit(EXIT_SUCCESS);
}
