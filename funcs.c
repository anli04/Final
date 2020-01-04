#include "rpg.h"

double rand_double(){ // returns a value from 0 to 1.
  return (double) rand() / (double) RAND_MAX;
}

void errcheck(char * m){ //error checking
  if (errno){
    printf("Error %s: %d - %s\n", m, errno, strerror(errno));
    errno = 0;

  }
}

int choose(char * choices){
  char input[5]; // should be over the maximum chars needed to check for extra characters
  char ** args;
  int i = 0;
  while (choices){
    args[i] = strsep(&choices, ";");
    i++;
  }
  int count = i - 1;
  while (1){
    i = 0;
    fgets(input, 5, stdin);
    *strchr(input, '\n') = 0;
    for (; i < count; i++){
      if (!strcmp(input, args[i])){
        int ans = 0;
        sscanf(args[i], "%d", ans);
        return ans;
      }
    }
  }
  printf("ERROR\n");
  return -1;
}
