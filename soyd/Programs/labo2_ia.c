#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> // para usar strcmp()

pid_t pid;

void reemplazar(char *nom_programa, char *archivo) {
	char *args[] = {nom_programa, archivo, NULL};

	char ruta[256];
	strcpy(ruta, "./");
	strcat(ruta, nom_programa);

	execvp(ruta, args);

	perror("execvp");
	exit(EXIT_FAILURE);
}

void comparar_y_fork(char *nom_programa, char *archivo) {
	pid = fork();
	if (pid < 0) {
		perror(nom_programa);
	} else if (pid == 0) {
		reemplazar(nom_programa, archivo);
	}
}

bool validar_archivo(char *archivo) {
	int l = strlen(archivo);
	if (l < 5 || archivo[l - 1] != 't' || archivo[l - 2] != 'x' || archivo[l - 3] != 't' ||
			archivo[l - 4] != '.') {
		// nombre de archivo invalido (no es .txt)
		printf("Ingrese un archivo valido! <nombre_archivo>.txt \n");
		return 0;
	} else {
		return 1;
	}
}
		

void crear_proceso_secundario(char *cmd, char *archivo) {
	
	if (strcmp(cmd, "tokenizar") == 0 ){
		// tokenizador
		printf("Launch tokenizador \n");
		
		comparar_y_fork("labo2_ia_tokenizador", archivo);

	} else if (strcmp(cmd, "vectorizar") == 0 ){
		// vectorizador
		printf("Launch vectorizador \n");

		comparar_y_fork("labo2_ia_vectorizador", archivo);

	} else if (strcmp(cmd, "analizar") == 0 ){
		// analizador
		printf("Launch analizador \n");
			
		comparar_y_fork("labo2_ia_analizador", archivo);
	} else {
		printf("Ingrese comando valido \n");
	}

}

int main(void) {

	char linea[100];
	char comando[20];
	char archivo[50];
	char extra[2]; // para control de parametro extra

	while (true) {
	
		// chequeo de formatos y validez de prompt	
		printf("prompt> "); 
		fgets(linea, sizeof(linea), stdin);
		
		if (sscanf(linea, "%19s %49s %1s", comando, archivo, extra) != 2 ) { 
			if (strcmp(comando,"exit") == 0 ) {
				exit(EXIT_SUCCESS);
			}

			printf("Formato invalido \n");
		} else { // se ingresaron exactamente 2 strings
			if (validar_archivo(archivo) ) {
				crear_proceso_secundario(comando, archivo);
			} 
		}


	}


	exit(EXIT_SUCCESS); 
}
