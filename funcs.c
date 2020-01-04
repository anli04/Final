#include "rpg.h"

double rand_double(){
  return (double) rand() / (double) RAND_MAX;
}

void errcheck(char * m){
  if (errno){
    printf("Error %s: %d - %s\n", m, errno, strerror(errno));
    errno = 0;
  }
}

int choose(char * choices){
  char selections[100]; // note that this number will inhibit inventory size
  strcpy(selections, choices);
  char input[5]; // should be over the maximum chars needed to check for extra characters
  char * args[26]; //note inv space will be this num - 1
  int i = 0;
  while (selections){
    args[i] = strsep(&selections, ";");
    i++;
  }
  args[i] = NULL;
  while (1){
    i = 0;
    fgets(input, 5, stdin);
    errcheck("with input");
    *strchr(input, '\n') = 0;
    while(args[i]){
      if (!strcmp(input, args[i])){
        int ans = 0;
        sscanf(args[i], "%d", &ans);
        return ans;
      }
    }
    printf("Selection not recognized\n");
  }
  printf("ERROR\n");
  return -1;
}
