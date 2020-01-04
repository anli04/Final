#include "rpg.h"

int main(){
  srand(time(NULL));
  struct character player;
  int input = 0;
  printf("Welcome to [game name]\n");
  printf("Make selections by typing the number corresponding to your choice\n");
  printf("1) Create Character\n2) Select Character\n");
  input = choose("1;2");
  printf("%d\n", input);
  return 0;
}
