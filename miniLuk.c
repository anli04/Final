#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "rpg.h"

int lootbox(struct stats * stats) {
  char buf[16];
  system("clear");
  while(strcmp(buf,"r\n") != 0) {
    system("clear");
    printf("\n------------------------------------------------------\n");
    printf("Welcome to Luck Trial!");
    printf("\n------------------------------------------------------\n");
    printf("INSTRUCTIONS:\n");
    printf("Give up 1 STR, DEX, INT, and END to try your LUK! Type \'r\' and enter to roll!\n");
    fgets(buf,16,stdin);
  }
  if(stats->STR >= 1 && stats->DEX >= 1 && stats->INT >= 1 && stats->END >= 1) {
    stats->STR -= 1;
    stats->DEX -= 1;
    stats->INT -= 1;
    stats->END -= 1;

    int r = 0;
    int l = 0;
    int i = 0;
    int d = 1000;
    for(;i<200;i++) {
      d += d/40;
      system("clear");
      r = (int)rand()%100000;
      if(r<5000) {
        l = (int)rand()%20;
      }
      else if(r < 50000) {
        l =  (int)rand()%8;
      }
      else {
        l = (int)rand()%6;
      }
      printf("\n\n\n--------\t%d\t--------\n\n\n",l);
      usleep(d);
    }
    sleep(1);
    system("clear");
    printf("\n\n\nCongratulations! You got %d luk!\n",l);
    sleep(1);

    return l;
  }
  else {
    system("clear");
    printf("You don't have enough to roll.\n");
  }

}


int main() {
  srand(time(NULL));
  struct stats stats;
  stats.STR = 10;
  stats.DEX = 10;
  stats.END = 10;
  stats.INT = 10;
  lootbox(&stats);
}
