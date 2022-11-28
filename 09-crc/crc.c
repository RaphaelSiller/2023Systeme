#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crc.h"

/**
 * @brief Kann ein Generatorpolynom mit der crc-verschlüsselung generieren
 *
 * @param argv:	1. Modus (-v verschlüsseln, -e entschlüsseln)
 * 				2. Nachricht
 * 				3. Generatorpolynom
 * @return int
 */
int main(int argc, char *argv[]) {
  if (argc < 2) {
    perror("Benutze -h um volle Hilfe zu erhalten");
    exit(1);
  }

  // v = verschlüsseln e = entschlüsseln
  char modus = 'a';
  // Lese commandline Argumente
  if (argv[1][0] == '-') {
    // help
    if (strstr(argv[1], "h")) {
      system("cat README");
      exit(0);
    }
    
    // v = verschlüsseln e = entschlüsseln
    if (strstr(argv[1], "v")) {
      modus = 'v';
    } else if (strstr(argv[1], "e")) {
      modus = 'e';
    }

    if (strstr(argv[1], "c")) {
      fclose(stdout);
    }
  } else {
    perror("Es muss mindestens eine Option angegeben werden\n");
    exit(1);
  }

  if (argc < 4) {
    perror("Zu wenig Argumente übergeben\n");
    exit(1);
  }
<<<<<<< HEAD
  
=======

  // printf("argv[1] = %s\n", argv[1]);

>>>>>>> f57b5a2b20e49e84d6f49256e637c324e0ffa18a
  // Eingabe Nachricht zu Binary
  long msg = 0, gen = 0, checksum = 0;
  for (int i = 0; i < strlen(argv[2]); i++) {
    msg = msg << 1;
    switch (argv[2][i]) {
    case '1':
      msg++;
      break;
    case '0':
      break;

    default:
      perror("Nachricht ist nicht '0' oder '1'\n");
      exit(1);
    }
  }

  // Eingabe generator zu Binary
  for (int i = 0; i < strlen(argv[3]); i++) {
    gen = gen << 1;
    switch (argv[3][i]) {
    case '1':
      gen++;
      break;
    case '0':
      break;

    default:
      perror("Generator ist nicht '0' oder '1'\n");
      exit(1);
    }
  }

  // Eingabe Checksum zu Binary
  if (modus == 'e') {
    if (argc < 5) {
      perror("Fuers entschluesseln muss eine Pruefsumme eingegeben werden");
      exit(1);
    }

    for (int i = 0; i < strlen(argv[4]); i++) {
      checksum = checksum << 1;
      switch (argv[4][i]) {
      case '1':
        checksum++;
        break;
      case '0':
        break;

      default:
        perror("checksum ist nicht '0' oder '1'\n");
        exit(1);
      }
    }
  }

  if (modus == 'v') {
    printf("Es wird Nachricht %s mit Generator %s verschluesselt\n", argv[2],
           argv[3]);
    verschluesseln(msg, gen);
  } else if (modus == 'e') {
    printf("Es wird Nachricht %s mit Generator %s entschluesselt. Pruefsumme "
           "sollte %s sein\n",
           argv[2], argv[3], argv[4]);
    if (entschluesseln(msg, gen, checksum) != 0)
      exit(2);
  } else {
    perror("Modus muss entweder '-v' oder '-e' sein");
    exit(1);
  }

  exit(0);
}

void verschluesseln(long msg, long gen) {
  if (gen > msg) {
    perror("generator kann nicht groesser als Nachricht sein");
    exit(1);
  }

  // Fuege nDigits hinzu, wobei nDigits Anzahl der Ziffern des größtmöglichen
  // Rests ist
  msg = msg << getNumberOfDigits(gen);

  printf("Checksum = ");
  fprintf(stderr, "%li", msg % gen);
}

int entschluesseln(long msg, long gen, long checksum) {
  if (checksum >= gen) {
    perror("Checksum muss kleiner als Generator sein");
    exit(1);
  }

  // Füge Rest am Ende der Message hinzu
  msg = msg << getNumberOfDigits(gen);
  msg += (gen - checksum);

  if (msg % gen == 0) {
    printf("Checksum wurde richtig errechnet\n");
  } else {
    printf("Checksum wurde falsch errechnet\n");
    printf("msg = %li\ngen = %li\nuebergebene checksum = %li\n", msg, gen,
           checksum);
    printf("Checksum sollte %li sein\n", msg % gen);
  }
  return msg % gen;
}

int getNumberOfDigits(int n) {
  int ret = 0;
  while (n > 0) {
    n /= 2;
    ret++;
  }
  return ret;
}