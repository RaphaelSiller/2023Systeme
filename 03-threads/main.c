#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * Aufgabe 1
 * Das Programm soll einen zweiten Thread erstell.
 * Jeder Thread soll PID und lwp ID ausgeben
 */

void *funcThread(void *arg) {
  printf("PID vom secondThread: %i\n", getpid());
  printf("LWP ID vom secondThread: %lu\n", pthread_self());
}

int main() {
  pthread_t secondThread;

  pthread_create(&secondThread, NULL, funcThread, NULL);

  pthread_join(secondThread, NULL);
  
  printf("PID vom mainThread: %i\n", getpid());
  printf("LWP ID vom mainThread: %lu\n", pthread_self());
  return 0;
}
