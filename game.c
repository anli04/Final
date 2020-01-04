#include "rpg.h"

int main(){
  srand(time(NULL));
  struct character player;
  int input = 0;
  char choices[100]; // note that this number will inhibit inventory size
  printf("Welcome to [game name]\n");
  printf("Make selections by typing the number corresponding to your choice\n");
  printf("1) Create Character\n2) Select Character\n");
  strcpy(choices, "1;2");
  input = choose(choices);
  printf("%d\n", input);
  return 0;
}
