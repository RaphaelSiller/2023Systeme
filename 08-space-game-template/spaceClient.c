#define _POSIX_C_SOURCE 200112L

// asprintf() does not appear on linux without this
#define _GNU_SOURCE
// gettimeofday() does not appear on linux without this
#define _DEFAULT_SOURCE

#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
#include <time.h>

#include <fcntl.h> /* Defines O_* constants */
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h> /* Defines mode constants */
#include <sys/types.h>
#include <unistd.h> /* for close() + ftruncate() */

/*
 * Space Game: Client
 */

#include "spaceHeader.h"

/* Shared memory buffer */
struct shmbuf {
  sem_t sem;                       /* Semaphore for playfield */
  char playfield[N_ROWS * N_COLS]; /* The playfield/space */
};

int main() {
  /*
   * Creates or gets the preexisting shared memory area reserved with the name
   * "SHARED_MEMORY_NAME" for the space game.
   */
  int fd = shm_open(SHARED_MEMORY_NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  if (fd < 0) { // Fehler beim erstellen/zugreifen
    perror("Fehler beim erstellen zugreifen von shared memory");
    return 0;
  }
  /* set size of SHM object */
  if (ftruncate(fd, sizeof(struct shmbuf)) < 0) {
    perror("Fehler beim setzen der Länge");
    return -1;
  }

  /* map SHM object into caller's address space */
  struct shmbuf *shmp;
  if ((shmp = mmap(NULL, sizeof(struct shmbuf),
                   PROT_EXEC | PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) ==
      MAP_FAILED) {
    perror("Fehler beim mappen");
    return -1;
  }

  /* close unused file descriptor */
  close(fd);

  /* initialize semaphore */
  if (sem_init(&shmp->sem, 1, 1) < 0) {
    perror("Fehler beim Initialisieren des Semaphoren");
    return -1;
  }

  /* Init playfield/space */
  {
    int x, y;

    /* lock the semaphore (decrement) */
    sem_wait(&shmp->sem);

    for (y = 0; y < N_ROWS; y++)
      for (x = 0; x < N_COLS; x++)
        shmp->playfield[y * N_COLS + x] = '.';

    /* unlock the semaphore (increase) */
    sem_post(&shmp->sem);
  }

  /* Reset terminal buffer */
  {
    struct termios sets;
    struct termios newsets;

    tcgetattr(0, &sets);
    newsets = sets;
    newsets.c_cc[VMIN] = 1;
    newsets.c_cc[VTIME] = 0;
    newsets.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &newsets);
  }

  /* Reset STDIN buffer */
  fflush(stdin);
  setvbuf(stdin, NULL, _IONBF, 0);

  /*
   * Game play:
   * w ... Up
   * a ... Left
   * s ... Down
   * d ... right
   * q ... Game end
   */
  {
    /* Key buffer */
    char c;
    /* Spaceship (new) and old coordinates. Start values are x = 10, y = 20 */
    int ssX = 10 - 1, ssY = 20 - 1, ssXOld = 10 - 1, ssYOld = 20 - 1;

    do {
      /* lock the semaphore (decrease) */
      sem_wait(&shmp->sem);

      shmp->playfield[ssYOld * N_COLS + ssXOld] = '.';
      shmp->playfield[ssY * N_COLS + ssX] = '@';

      /* unlock the semaphore (increase) */
      sem_post(&shmp->sem);

      ssXOld = ssX;
      ssYOld = ssY;

      c = getchar();

      /* change the coordinates ssX, ssY depending on the pressed characters
       * "w,a,s,d" */
      switch (c) {
      case 'w': /* Up */
        if (ssY > 0)
          ssY--;
        break;
      case 'a': /* Left */
        if (ssX > 0)
          ssX--;
        break;
      case 's': /* Down */
        if (ssY < N_ROWS-1)
          ssY++;
        break;
      case 'd': /* Right */
        if (ssX < N_COLS-1)
          ssX++;
        break;
      }
    } while (c != 'q');

    putchar('\n');
  }

  /* delete the mapping for the specified range */
  if (munmap(shmp, sizeof(struct shmbuf)) < 0) {
    perror("Fehler beim Unmappen");
    return -1;
  }
}
