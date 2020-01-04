#include "rpg.h"

int input(char * choices); //collect input and check to make sure the selection is valid

int main(){
  srand(time(NULL));
  struct character player;
  int input = 0;
  printf("Welcome to [game name]\n");
  printf("Make selections by typing the number corresponding to your choice\n");
  printf("1) Create Character\n2) Select Character\n");
  input = select("1;2");
  printf("%d\n", input);
  return 0;
}
