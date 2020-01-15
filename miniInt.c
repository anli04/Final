#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "rpg.h"



char ** parse_args(char * line, char * s) {
    char * copy = strdup(line);
    char ** args = malloc(sizeof(char)*1024);
    int i = 0;
    char * iter;
    while((iter = strsep(&copy,s)) != NULL) {
        args[i] = malloc(sizeof(char)*32);
        strcpy(args[i],iter);
        i++;
    }
    return args;
}

int size_array(char ** arr) {
  int i = 0;
  while(arr[i]) {
    i++;
  }
  return i;
}


int wordGame() {
  system("clear");
  char * lines[256];
  FILE *f = fopen("words.txt","r");
  char buf[256];
  int i = 0;
  while(fgets(buf,256,f) != NULL) {
    lines[i] = malloc(sizeof(char)*256);
    buf[strlen(buf)-1] = '\0';
    strcpy(lines[i],buf);
    i++;
  }


  int r = 0;
  int r_w = 0;
  int r_w2 = 0;
  int s = 0;
  char ** line;
  while(strcmp(buf,"q\n") != 0) {
    system("clear");
    r = (int)rand()%i;
    line = parse_args(lines[r],";");
    s = size_array(line);
    r_w = (int)rand()%s;
    r_w2 = (int)rand()%s;
    while(r_w2 == r_w) {
      r_w2 = (int)rand()%s;
    }


    printf("Name a word that starts with '%c%c' and ends with '%c', and is synonymous with %s\n",line[r_w2][0],line[r_w2][1],line[r_w2][strlen(line[r_w2])-1],line[r_w]);
    fgets(buf,256,stdin);

    if(strcmp(buf,"q\n") != 0) {
      system("clear");
      printf("Name a word that starts with '%c%c' and ends with '%c', and is synonymous with %s\n",line[r_w2][0],line[r_w2][1],line[r_w2][strlen(line[r_w2])-1],line[r_w]);
      buf[strlen(buf)-1] = '\0';
      printf("%s ",buf);
      if(strcmp(buf,line[r_w2]) == 0) {
        printf("✔\n");
      }
      else {
        printf("✗\n");
        printf("The correct answer was: %s\n",line[r_w2]);
      }
    }

    sleep(1);

  }




}

int main() {
  srand(time(NULL));
  wordGame();

}
