#define _POSIX_C_SOURCE 200112L

// asprintf() does not appear on linux without this
#define _GNU_SOURCE
// gettimeofday() does not appear on linux without this
#define _DEFAULT_SOURCE

#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <fcntl.h> /* Defines O_* constants */
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h> /* Defines mode constants */
#include <unistd.h>   /* for close() */

/*
 * Space Game: Graphic Server
 */

#include "spaceHeader.h"

/* A value <> 0 terminates the program */
static bool exitRequest = false;

/* Shared memory buffer */
struct shmbuf {
  sem_t sem;                       /* Semaphore for playfield */
  char playfield[N_ROWS * N_COLS]; /* The playfield/space */
};

/*
 * Handles an incoming termination request signal
 */
static void exitHandle(int sig) { exitRequest = true; }

int main() {
  /*
   * Creates or gets the preexisting shared memory area reserved with the name
   * "SHARED_MEMORY_NAME" for the space game.
   */
  int fd = shm_open(SHARED_MEMORY_NAME, O_CREAT | O_EXCL | O_RDWR,
                    S_IRUSR | S_IWUSR);
  if (fd < 0) { // Fehler beim erstellen/zugreifen
    perror("Fehler beim erstellen/zugreifen von shared memory");
    return -1;
  }

  /* set size of SHM object */
  if (ftruncate(fd, sizeof(struct shmbuf)) <0) {
	perror("Fehler beim Festlegen der Groesse vom shmp");
	return 0;
  }

  /* map SHM object into caller's address space */
  struct shmbuf *shmp;
  if ((shmp = mmap(NULL, sizeof(struct shmbuf), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
	perror("Fehler beim callen des SHM Objekts in Addressbereich");
	return 0;
  }

  /* close unused file descriptor */
  close(fd);

  /* initialize semaphore */
  if (sem_init(&shmp->sem, 1, 1) < 0) {
    perror("Fehler beim Initialisieren des Semaphoren");
    return 0;
  }

  /* Clear screen */
  system("clear");

  /* Register the signals for termination requests */
  signal(SIGINT, exitHandle);
  signal(SIGTERM, exitHandle);

  while (!exitRequest) {
    int x, y;
    /* 0,1 sec. delay for "nanosleep" in print loop */
    struct timespec delay = {0, 100000000L};

    /* lock the semaphore (decrease) */
    sem_wait(&shmp->sem);

    /* Draw playfield */
    printf("\033[1;1H");
    for (y = 0; y < N_ROWS; y++) {
      for (x = 0; x < N_COLS; x++)
        putchar(shmp->playfield[y * N_COLS + x]);
      putchar('\n');
    }
    fflush(stdout);

    /* unlock the semaphore (increase) */
    sem_post(&shmp->sem);

    nanosleep(&delay, NULL);
  }

  /* delete the mapping for the specified range */
  if (munmap(shmp, sizeof(struct shmbuf)) < 0) {
    perror("Fehler beim unmappen");
    return 0;
  }

  /* remove SHM object */
  if (shm_unlink(SHARED_MEMORY_NAME) < 0) {
    perror("Fehler beim entfernen des SHM Objektes");
    return 0;
  }
}
