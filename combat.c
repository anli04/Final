#include "rpg.h"

#define KEY 2473842

int main(int argc, char *argv[]){
  int victory = 0; // win or lose. 1 or 0
  int sem;
  sem = semget(KEY, 1, 0);
  errcheck("getting semaphore");
  struct sembuf sb;
  sb.sem_num = 0;
  char NAME[25];
  int hp;
  double HIT;
  double DMG;
  double VAR;
  double DMGRED;
  double DODGE;
  int skills[4];
  char * skillnames[5];
  double buffs[4]; // hitmod, dmgmod, dmgred add, dodge add.
  double bufftime[4]; // respective to buffs, how long it last.
  int i;
  for (; i < 4; i++){
    buffs[i] = 0;
    bufftime[i] = 0;
  }
  struct turn update;
  update.action = malloc(sizeof(char) * 256);
  FILE * f = fopen(argv[1], "r");
  char temp[256];
  if (argc > 2){
    fgets(NAME, sizeof(NAME), f);
    sscanf(fgets(temp, 256, f), "%d", hp);
    double hpmod;
    sscanf(fgets(temp, 256, f), "%lf", hpmod);
    hp *= (rand_double() * 2 - 1) * hpmod + 1;
    sscanf(fgets(temp, 256, f), "%lf", HIT);
    sscanf(fgets(temp, 256, f), "%lf", DMG);
    sscanf(fgets(temp, 256, f), "%lf", VAR);
    sscanf(fgets(temp, 256, f), "%lf", DMGRED);
    sscanf(fgets(temp, 256, f), "%lf", DODGE);
    sscanf(fgets(temp, 256, f), "%lf", DODGE);
    for (i = 0; i < 4; i++) sscanf(fgets(temp, 256, f), "%d", skills[i]);
    for (i = 0; i < 4; i++) sscanf(fgets(temp, 256, f), "%d", skills[i]);
  }
  else{

    // player stuff
  }
  fclose(f);
  struct turn t;
  mkfifo("CombatToCombat", 0666);
  char in[500];
  char out[500];
  char arr[10][50];
  int fd;

  //Note: merge the following stuff below

  while (1) {
    fd = open("CombatToCombat", O_RDONLY);
    read(fd, in, sizeof(in));
    close(fd);
    fd = open("CombatToCombat", O_WRONLY);
    fgets(out, 500, stdin);
    write(fd, out, strlen(out)+1);
    close(fd);
  }


  int input = 0;
  while (1){
    sb.sem_op = -1;
    printf("Awaiting opponent...");
    semop(sem, &sb, 1);
    errcheck("getting semaphore");
    // pipe in string of what opponent did





    // pipe out string of what you did, for opponent
    sb.sem_op = 1;
    semop(sem, &sb, 1);
    errcheck("releasing semaphore");
  }
  return victory;
}
