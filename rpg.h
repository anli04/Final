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
#include <math.h>

#define KEY 2473842

struct character{
  char * NAME;
  struct stats stats;
  struct inventory inventory;
  struct equipped equipped;
  int * skills; //equipped skills, up to 5. skills[0] is always Strike.
};

struct stats{
  int STR; //capitalized, but liable to change
  int DEX;
  int END;
  int INT;
  int LUK;
};

struct inventory{
  int * invI; // item inventory. Current max: 15.
  int * invS; // skill inventory. Current max: 15.
};

struct equipped{
  int wep; //equipped weapon
  int armor; //equipped armor
  int helm; //equipped helm
};


struct item{
  int ID;
  char * NAME;
  int type; //wep, helm, armor. W, H, A respectively.
  double HIT; // hit chance modifier. modifiers and variance are multiplicative
  double DMG; // average damage or modifier
  double VAR; // damage variance or modifier
  double DMGRED; // damage reduction. e.g. 0.1 = reduce by 10% (additive)
  double DODGE; // dodge chance (additive)
  int * STAT; // stat adjustments
  int * REQ; // stat requirement to equip
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

/* Encounter file:
name
average hp
hp variance // around round hp up when determining the int.
hit chance
average damage
damage variance
damage reduction
dodge chance
skill id
skill id
skill id
skill id
associated name 1
associated name 2
associated name 3
associated name 4
*/

struct turn{ // transmit this info through combat.
  int dmg; // hp change to enemy. + means damage
  int heal; // hp change to self. - means damage
  char * action; // description the opponent will see of what happened.
  char debuff; // code for debuffs
  int t; // number of turns debuff lasts.
  // buffs info is not transmitted.
};

double rand_double(); // returns a value from 0 to 1.
void errcheck(char * m); //error checking
int choose(char * choices); // handles player input
double nextNum(char * f, int idx, struct stats s); // mainly for use in solve
double solve(char * f, int idx, struct stats s); // see info for info
