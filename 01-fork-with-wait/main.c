#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void main() {
  printf("PID von Eltern Prozess bevor Fork %i \n", getpid());

  int PID = fork();

  // Wenn Fehler beim Forken
  if (PID == -1) {
    printf("Fehler beim Forken");
    return;
  }

  if (PID) {
    wait(NULL);
    printf("PID von Eltern Prozess nach  Fork %i \n", getpid());
  } else
    printf("PID von Kind   Prozess nach  Fork %i \n", getpid());
}
