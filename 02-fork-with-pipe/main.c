#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int result = 0;
  int fildes[2];

  // Erstellen der Pipe
  if (pipe(fildes) == -1) {
    printf("Fehler beim Pipe legen");
    return -1;
  }

  // Hier wird geforkt
  switch (fork()) {
  case -1:
    printf("Fehler beim forken");
    return -1;

  case 0: // Kind schreibt "Hallo Welt"
    // Schließe unbenutztes Read
    close(fildes[0]);

    // Berechne Teil vom Kind
    result = 6 - 4;

    // Schreibe Ergebnis zurück zum Parent Process
    write(fildes[1], &result, sizeof result);

    return 0;

  default: // Elternprozess
    // Schließe unbenutztes Write
    close(fildes[1]);

    // Berechne Teil vom Elt.
    result = 3 + 1;

    // Bekomme Ergebnis vom Kind
    int resultFromChild;
    wait(NULL);
    read(fildes[0], &resultFromChild, sizeof resultFromChild);

    // Ausgeben des Ergebnis
    printf("Ergebnis von x = (3 + 1) * (6 – 4) = %i\n", (result * resultFromChild));
    printf("Ergebnis von Kind (6 - 4) war %i\n", resultFromChild);
    printf("Ergebnis von Elt. (3 + 1) war %i\n", result);

    return 0;
  }
}
