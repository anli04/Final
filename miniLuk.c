#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "rpg.h"

int lootbox(struct stats * stats) {
  system("clear");
  if(stats->STR >= 1 && stats->DEX >= 1 && stats->INT >= 1 && stats->END >= 1) {
    stats->STR -= 1;
    stats->DEX -= 1;
    stats->INT -= 1;
    stats->END -= 1;

    int r = 0;
    int l = 0;
    int i = 0;
    for(;i<50;i++) {
      //system("clear");
      r = (int)rand()%100000;
      if(r<5000) {
        l = (int)rand()%15;
      }
      else if(r < 50000) {
        l =  (int)rand()%6;
      }
      else {
        l = (int)rand()%3;
      }
      printf("%d",l);
      usleep(100000);
    }
    printf("\n");


    stats->LUK += l;
  }

}


int main() {
  srand(time(NULL));
  struct stats stats;
  stats.STR = 1;
  stats.DEX = 1;
  stats.END = 1;
  stats.INT = 1;
  lootbox(&stats);
}
