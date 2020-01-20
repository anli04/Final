#include "rpg.h"


int lifting() {
  char * f1 = "       ___\n      (   )\n       ‾|‾\n     /‾‾|‾‾\\\n❚█═════════════█❚\n        |\n       / \\\n      /   \\";
  char * f2 = "       ___\n      (   )\n❚█═════════════█❚\n     \\  |  /\n      ‾‾|‾‾\n        |\n       / \\\n      /   \\";
  char* clear[1];
  clear[0] = malloc(sizeof(char)*16);
  strcpy(clear[0],"clear");
  char temp[32];
  char t;
  int reps = 0;
  
  while(1) {
    system("clear");
    printf("\n------------------------------------------------------\n");
    printf("Welcome to Strength Trial!");
    printf("\n------------------------------------------------------\n");
    printf("INSTRUCTIONS:\n");
    printf("\nPress a key and click Enter to do a rep. Click Enter to finish.\n%s\nReps: %d\n",f1,reps);

    fgets(temp,32,stdin);
    if(strcmp(temp,"\n") == 0) {
      break;
    }
    else {
      reps++;
    }
    system("clear");
    printf("\n------------------------------------------------------\n");
    printf("Welcome to Strength Trial!");
    printf("\n------------------------------------------------------\n");
    printf("INSTRUCTIONS:\n");
    printf("\nPress a key and click Enter to do a rep. Click Enter to finish.\n%s\nReps: %d\n",f2,reps);
    fgets(temp,32,stdin);
    if(strcmp(temp,"\n") == 0) {
      break;
    }
    else {
      reps++;
    }


  }

  return reps;


}
