#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int game() {
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
    printf("\n%s",f1);

    fgets(temp,32,stdin);
    if(strcmp(temp,"]\n") == 0) {
      reps++;
    }
    else {
      break;
    }
    system("clear");
    printf("\n%s",f2);
    fgets(temp,32,stdin);
    if(strcmp(temp,"]\n") == 0) {
      reps++;
    }
    else {
      break;
    }


  }


}

int main(){
  game();
}
