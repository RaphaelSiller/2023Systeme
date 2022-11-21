#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

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
  if (argc < 4) {
    errno = 1;
    perror("Zu wenig Argumente übergeben\n");
    return -1;
  }

  // printf("argv[1] = %s\n", argv[1]);
  
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
  if (strcmp(argv[1], "-e") == 0) {
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
  
  if (strcmp(argv[1], "-v") == 0) {
    printf("Es wird Nachricht %s mit Generator %s verschluesselt\n", argv[2],
           argv[3]);
    verschluesseln(msg, gen);
  } else if (strcmp(argv[1], "-e") == 0) {
    printf("Es wird Nachricht %s mit Generator %s entschluesselt. Pruefsumme "
           "sollte %s sein\n",
           argv[2], argv[3], argv[4]);
    entschluesseln(msg, gen, checksum);
  } else {
    perror("Modus muss entweder '-v' oder '-e' sein");
    return -1;
  }
}

void verschluesseln(long msg, long gen) {
  if (gen > msg) {
    perror("generator kann nicht groesser als Nachricht sein");
    exit(1);
  }
  printf("Checksum = %li\n", msg % gen);
}

void entschluesseln(long msg, long gen, long checksum) {
  if (checksum >= gen) {
    perror("Checksum muss kleiner als Generator sein");
    exit(1);
  }
  // printf("%i\n", polynomial_long_division(msg, gen));
  if (/*msg % gen == checksum*/  polynomial_long_division(msg-checksum, gen) == 0) {
    printf("Checksum wurde richtig errechnet\n");
  } else {
    printf("Checksum wurde falsch errechnet\n");
    printf("msg = %li\ngen = %li\nuebergebene checksum = %li\n", msg, gen, checksum);
    printf("Checksum sollte %i sein\n", polynomial_long_division(msg-checksum, gen));
  }
}

int polynomial_long_division(int dividend, int divisor) {
  printf("\tdividend = %i\tdivisor = %i\n", dividend, divisor);
        // check dividend == 0
        if(dividend == 0)
            return 0;
        
        // check overflow case
        if(dividend == INT_MIN && divisor == -1)
            return INT_MAX;
        
        // get abs values of operands, taking care of the overflow case
        unsigned int dividendAbs = intAbs(dividend);
        unsigned int divisorAbs = intAbs(divisor);

        // get most significant bit of the operands
        char dividendAbs_msb = mostSignBit(dividendAbs);
        char divisorAbs_msb = mostSignBit(divisorAbs);

        int res = 0;
        // at this point, we basically do long division algorithm
        // ie the way it is taught in elementary school, but only with
        // binary nums instead of decimal
        for(int i = dividendAbs_msb - divisorAbs_msb; i >= 0; i--)
        {
            unsigned int divisorAbs_shift = divisorAbs << i; 
            if(divisorAbs_shift <= dividendAbs)
            {   
                dividendAbs -= divisorAbs_shift;
                res |= 1 << i;
            }   
        }
        
        // check overflow case
        if(res == INT_MIN)
            return INT_MIN;
        // return result, taking into account the sign of the operands
        // if one was negative, add - sign to the result, which in terms
        // of second complement representaion used for negative numbers
        // simply means - convert result to second complement
        else
            return (dividend ^ divisor) < 0 ? ~res + 1 : res;
    }

    unsigned int intAbs(int num)
    {
        if(num == INT_MIN)
            return (unsigned int)INT_MAX + 1;
        else
            return abs(num);   
    }
    //
    char mostSignBit(unsigned int num)
    {
        int num_msb = 31;
        while(!(num & (1 << num_msb)))
            --num_msb;  
        
        return num_msb;
    }