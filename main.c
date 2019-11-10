#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main() {

  int rand_file = open("/dev/random",O_RDONLY);
  int * rand_array[10];

  int i=0;
  unsigned int rand;
  printf("Generating random numbers:\n");
  for (i=0;i<10;i++) {
    read(rand_file, rand_array+i, sizeof(rand));
    printf("\tRandom %d: %u\n", i, rand_array[i]);
  }

  // int myFile = open("/dev/random", O_RDONLY);
  // unsigned int rand;
  // unsigned int randomNum = read(myFile, &rand, sizeof(rand)) ;
  // printf(" %u ", rand);

}
