#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void main() {
  int result = 0;
  int fildes[2];
  int pid;

  if (pipe(fildes) == -1) {
    printf("Fehler beim Pipe legen");
    return -1;
  }

  switch (fork()) {
  case -1:
    printf("Fehler beim forken");
    return -1;
    break;

  case 0: //Kind
    

    break;

  default: //Elternprozess
    

    break;
  }
}
