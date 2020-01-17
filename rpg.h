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
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <signal.h>
#include <math.h>

#define KEY 2473843
#define CPATH "characters/"
#define IPATH "items/"
#define SPATH "skills/"
#define EPATH "encounters/"

struct stats{
  int STR; //capitalized, but liable to change
  int DEX;
  int END;
  int INT;
  int LUK;
};

struct inventory{
  int invI[15]; // item inventory. Current max: 15.
  int invS[15]; // skill inventory. Current max: 15.
};

struct equipped{
  int wep; //equipped weapon
  int armor; //equipped armor
  int helm; //equipped helm
};

struct character{
  char * NAME;
  struct stats stats;
  struct equipped equipped;
  int skills[5]; //equipped skills, up to 5. skills[0] is always Strike.
  struct inventory inventory;
};


struct item{
  int ID;
  char * NAME;
  char type; //wep, helm, armor. W, H, A respectively.
  double HIT; // hit chance modifier. modifiers and variance are multiplicative
  double DMG; // average damage or modifier
  double VAR; // damage variance or modifier
  double DMGRED; // damage reduction. e.g. 0.1 = reduce by 10% (additive)
  double DODGE; // dodge chance (additive)
  int STAT[5]; // stat adjustments
  int REQ[5]; // stat requirement to equip
};

struct skill{
  int ID;
  char * NAME;
  double HITMOD; // hit chance modifier
  double DMGMOD; // damage modifier
  double VARMOD; //variance modifier
  double HITBUFF; // hit chance buff
  double DMGBUFF; // damage buff
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
  double debuff[4]; // code for debuffs
  int t[4]; // number of turns debuff lasts.
  // buffs info is not transmitted.
  char * exa; // extra info from skill used
  int end;
};

double rand_double(); // returns a value from 0 to 1.
double min(double n, double m); // returns smallest of two doubles
void errcheck(char * m); //error checking
int choose(char * choices); // handles player input
char ** parse_args(char * line, char * s);
int size_array(char ** arr);
double nextNum(char * f, int idx, struct stats s); // mainly for use in solve
double solve(char * f, int idx, struct stats s); // see info for info
void skillinfo(struct skill * move, int id, struct stats s); // get skill info
