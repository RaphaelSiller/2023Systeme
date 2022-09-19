#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * Aufgabe 2
 * Der zweite Thread soll von 10 Abwärts zählen
 * Der mainThread wartet mit einem geeigneten sleep
 */

void *funcThread(void *arg) {
  for (int i = 10; i > 0; i--)
  {
	printf("%i\n", i);
	sleep(1);
  }
  
}

int main() {
  pthread_t secondThread;

  pthread_create(&secondThread, NULL, funcThread, NULL);

  sleep(10);
  return 0;
}
