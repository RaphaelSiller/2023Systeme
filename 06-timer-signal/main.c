	#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int nTimesInterrupted = 3;

void interrupt() {
	printf("CTRL+C\n"); 
	fflush(stdout);

	nTimesInterrupted--;
	if (nTimesInterrupted<=0)
		raise(SIGKILL);
}

int main() {
	printf("PID = %i\n", getpid());
	signal(SIGINT, interrupt);
	while(1) {
		sleep(2);
		fprintf(stderr, "bling!\n");
	}
}
