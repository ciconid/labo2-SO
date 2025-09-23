#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main (void){
	
	pid_t child_pid;

	printf("main PPID: %d\n", getppid() );
	printf("main PID: %d\n", getpid() );

	child_pid = fork();

	if (child_pid != 0) {

 		printf("Proceso padre, PID: %d\n",(int) getpid() );
		printf("Proceso hijo, PID: %d\n", (int) child_pid );
		
		int status;
		wait(&status);

		printf("Espere a mi hijo con PID: %d \n", (int) child_pid );
	} else {
		printf("Ejecucion proceso hijo, PID: %d\n", (int) getpid() );
	}

	sleep(2);

	//printf("saliendo \n");
	return EXIT_SUCCESS;
}
