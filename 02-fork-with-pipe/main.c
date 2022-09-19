#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
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

  case 0: //Kind schreibt "Hallo Welt"
    close(fildes[0]); // Schließe unbenutztes Read
    result = 6-4;
    
    write(fildes[1], &result, sizeof result);
    return 0;

  default: //Elternprozess
    close(fildes[1]); //Schließe unbenutztes Write
    result=3+1;
    int resultFromChild;
    wait(NULL);
    
    read(fildes[0], &resultFromChild, sizeof resultFromChild);

    printf("Ergebnis von x = (3 + 1) * (6 – 4) = %i\n", (result * resultFromChild));
    printf("Ergebnis von Kind (6 - 4) war %i\n", resultFromChild);
    printf("Ergebnis von Elt. (3 + 1) war %i\n", result);

    return 0;
  }
}
