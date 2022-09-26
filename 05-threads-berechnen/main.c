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
int x = 4;
int ergebnis;

void *funcThread(void *arg) {
  /* int ret = *((int *)arg);
  ret*=2; */
  //Return Calculated Result and exit Thread
  ergebnis = x * 2;
}

int main() {
  pthread_t secondThread;

  //Create Thread
  if(pthread_create(&secondThread, NULL, funcThread, NULL) != 0) {
    printf("Fehler beim erstellen des Threads");
    exit(1);
  }

  //Join Thread (Wait for Thread and save return value)
  if(pthread_join(secondThread, NULL) != 0) {
    printf("Fehler beim Thread join");
    exit(2);
  }  

  //Print Result
  printf("x = %i\n", x);
  printf("ergebnis = %i\n", ergebnis);
  return 0;
}
