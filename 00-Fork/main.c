#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

void main() {
	printf("PID von Eltern Prozess bevor Fork %i \n", getpid());

	int PID = fork();
	
	//Ween Fehler beim Forken
	if (PID == -1) {
		printf("Fehler beim Forken");
		return;
	}

	if(PID)
		printf("PID von Eltern Prozess nach  Fork %i \n", getpid());
	else
		printf("PID von Kind   Prozess nach  Fork %i \n", getpid());
		
}
