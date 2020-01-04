#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <signal.h>

struct character{
  char * NAME;
  int STR; //capitalized, but liable to change
  int DEX;
  int END;
  int INT;
  int LUK;
  int wep; //equipped weapon
  int armor; //equipped armor
  int helm; //equipped helm
  int * skills; //equipped skills, up to 5. skills[0] is always Strike
  int * invI; // item inventory
  int * invS; // skill inventory
};

struct item{
  int ID;
  int type; //wep, helm, armor. W, H, A respectively.
  char * NAME;
  double HIT; // hit chance modifier. modifiers are multiplicative
  double DMG; // average damage or modifier
  double VAR; // damage variance or modifier
  double DMGRED; // damage reduction. e.g. 0.1 = reduce by 10% (additive)
  double DODGE; // dodge chance (additive)
  int * STAT; // stat adjustments
  char * REQ; // stat requirement to equip
};

struct skill{
  int ID;
  char * NAME;
  double HIT; // hit chance modifier
  double DMGMOD; // damage modifier
  double VARMOD; //variance modifier
  double REDPLUS; // additional damage reduction
  double DODGEPLUS; // additional dodge chance
  int TURNS; // number of turns it lasts. 1 ends on your next turn. 0 for no effects
  int CD; // turn cooldown
  char * EXA; // additional changes to be interpreted. 0 if nothing
};

double rand_double(); // returns a value from 0 to 1.
void errcheck(char * m); //error checking
int choose(char * choices); // handles player input
