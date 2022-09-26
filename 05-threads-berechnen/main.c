#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * Aufgabe 1
 * Das Programm soll einen zweiten Thread erstell.
 * Der zweite Thread macht eine Berechnung und gibt das Ergebnis dem ersten Thread zurück.
 * Der erste Thread gibt das Ergebnis wieder aus
 */

void *funcThread(void *arg) {
  /* int ret = *((int *)arg);
  ret*=2; */
  pthread_exit((*((int *)arg)) * 2);
}

int main() {
  pthread_t secondThread;

	int x = 4, ergebnis;

  if(pthread_create(&secondThread, NULL, funcThread, (void *) &x) != 0) {
    printf("Fehler beim erstellen des Threads");
    exit(1);
  }

  if(pthread_join(secondThread, &ergebnis) != 0) {
    printf("Fehler beim Thread join");
    exit(2);
  }

  

  printf("x= %i\n", x);
  printf("ergebnis= %i\n", ergebnis);
  return 0;
}
