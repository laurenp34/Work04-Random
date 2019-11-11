#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

void print_array(int * array) {
  int i=1;
  for (i=1;i<=10;i++) {
      printf("\t%d: %u\n", i, array[i-1]); //thank you Kiran for pointing out that my array was 1-indexed before!
  }
}

int main() {

  //open dev/random
  int rand_file = open("/dev/random",O_RDONLY);
  if (rand_file == -1) printf("Error: %s", strerror(errno));

  //create first array
  int rand_array[10];

  unsigned int rand;

  printf("Generating random numbers:\n");

  //read from dev/random into rand_array without loop
  rand = read(rand_file, rand_array, 10 * sizeof(int));
  if (rand == -1) printf("Errno %d: %s\n", errno, strerror(errno));
  else printf("read from dev/random successfully\n");

  // printf("\tRandom %d: %u\n", i, rand_array[i]);

  // for (i=0;i<10;i++) {
  //   rand = read(rand_file, rand_array+i, sizeof(rand));
  //
  //   if (rand == -1) printf("Errno %d: %s\n", errno, strerror(errno));
  //
  //   printf("\tRandom %d: %u\n", i, rand_array[i]);
  // }
  printf("\nClosing dev/random\n");
  rand = close(rand_file);
  if (rand == -1) printf("Errno %d: %s\n", errno, strerror(errno));
  else printf("closed dev/random successfully\n");

  print_array(rand_array);

  printf("\nWriting numbers to randnos...\n\n");

  printf("Opening randnos\n");
  int f2 = open("randnos",(O_CREAT|O_WRONLY),0644); //for some reason O_RDWR gave permission denied
  if (f2 == -1) printf("Errno %d: %s\n", errno, strerror(errno));
  else printf("wrote to randnos successfully\n");

  //char test[13] = "Good morning";
  printf("\nWriting to randnos\n");
  int err = write(f2, rand_array, 10 * sizeof(int));
  if (err == -1) printf("WRITING ERROR Errno %d: %s\n", errno, strerror(errno));
  else printf("Wrote successfully to f2\n");

  printf("\nClosing randnos\n");
  int er = close(f2);
  if (er == -1) printf("Errno %d: %s\n", errno, strerror(errno));
  else printf("closed f2 successfully\n");


  // //testing writing to f2

  //
  // close(f2);
  //
  printf("\nOpening randnos to read\n");
  f2 = open("randnos", O_RDONLY);
  if (f2 == -1) printf("OPENING ERROR Errno %d: %s\n", errno, strerror(errno));
  else printf("opened f2 successfully\n");
  //
  // //read from dev/random into rand_array without loop
  // char * out;
  // rand = read(f2, out, sizeof(test));
  // if (rand == -1) printf("READING ERROR Errno %d: %s\n", errno, strerror(errno));
  // else printf("Read from f2\n");
  //
  // printf("%s\n",out);


  //write to new file f2
  // printf("\nWriting to f2\n");
  // int err = write(f2, rand_array, 10 * sizeof(int));
  // if (err == -1) printf("Errno %d: %s\n", errno, strerror(errno));
  // else printf("wrote to f2 successfully\n");

  printf("\nReading numbers from file...\n");
  int rand_array2[10];
  rand = read(f2, rand_array2, 10 * sizeof(int));
  if (rand != 10 * sizeof(int)) printf("error: only %d bytes read. Errno %d: %s\n", rand, errno, strerror(errno));
  else printf("read from randnos successfully\n");

  close(f2);

  //print rand_array2
  printf("\nVerication that written vales were the same:\n");
  print_array(rand_array2);


}
