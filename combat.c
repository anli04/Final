#include "rpg.h"

char * readline(int fd);

int main(int argc, char *argv[]){ // second is file, third is 0 or 1, 1 starts. Fourth is if cpu controlled
  struct sembuf sb;
  sb.sem_op = -1;
  int sem;
  sem = semget(KEY, 2, 0);
  errcheck("getting semaphore");
  int fdr; // for read pipe
  int fdw; // for write pipe
  if (strcmp(argv[2], "0") == 0){ //get the major semaphore (going second)
    sb.sem_num = 1;
    fdr = open("CtoC1", O_RDONLY);
    fdw = open("CtoC2", O_WRONLY);
  }
  else{ //get the minor semaphore (going first)
    sb.sem_num = 0;
    fdw = open("CtoC1", O_WRONLY);
    fdr = open("CtoC2", O_RDONLY);
  }
  semop(sem, &sb, 1);
  sleep(1); // help ensure that the sems are set up between the two
  int victory = 0; // win or lose. 1 or 0
  int input;
  char NAME[40];
  int HPMAX;
  int hp;
  double HIT;
  double DMG;
  double VAR;
  double DMGRED;
  double DODGE;
  int skills[5];
  char skillnames[5][50];
  int skillCD[5];
  double buffs[4]; // hitmod, dmgmod, dmgred add, dodge add.
  int bufftime[4]; // respective to buffs, how long it last.
  int i = 0; // for for loops
  for (; i < 4; i++){
    buffs[i] = 0;
    bufftime[i] = 0;
  }
  struct turn update;
  update.action = malloc(sizeof(char) * 1024);
  update.exa = malloc(sizeof(char) * 10);
  strcpy(update.action, "\0");
  update.dmg = 0;
  update.heal = 0;
  for (i = 0; i < 4; i++) {
    update.debuff[i] = 0;
    update.t[i] = 0;
  }
  strcpy(update.exa, "\0");
  update.end = 0;
  struct skill move;
  move.NAME = malloc(sizeof(char) * 30);
  move.EXA = malloc(sizeof(char) * 10);
  struct stats stat;
  FILE * f; // for all the fopens.
  char temp[1024]; // for temporary string holding for functions
  if (argc == 4){ // cpu encounter
    sprintf(temp, "%s%s", EPATH, argv[1]);
    f = fopen(temp, "r");
    fgets(NAME, sizeof(NAME), f);
    sscanf(fgets(temp, sizeof(temp), f), "%d\n", &hp);
    double hpmod;
    sscanf(fgets(temp, sizeof(temp), f), "%lf\n", &hpmod);
    hp *= (rand_double() * 2 - 1) * hpmod + 1;
    HPMAX = hp;
    sscanf(fgets(temp, sizeof(temp), f), "%lf\n", &HIT);
    sscanf(fgets(temp, sizeof(temp), f), "%lf\n", &DMG);
    sscanf(fgets(temp, sizeof(temp), f), "%lf\n", &VAR);
    sscanf(fgets(temp, sizeof(temp), f), "%lf\n", &DMGRED);
    sscanf(fgets(temp, sizeof(temp), f), "%lf\n", &DODGE);
    for (i = 0; i < 5; i++) sscanf(fgets(temp, sizeof(temp), f), "%d\n", &skills[i]);
    for (i = 0; i < 5; i++) {
      if (skills[i] >= 0){
        *strchr(fgets(temp, sizeof(temp), f), '\n') = 0;
        strcpy(skillnames[i], temp);
      }
    }
    stat.STR = 50; // for the sake of skills
    stat.DEX = 50;
    stat.END = 50;
    stat.INT = 50;
    stat.LUK = 50;
    fclose(f);
  }
  else{
    sprintf(temp, "%s%s", CPATH, argv[1]);
    f = fopen(temp, "r");
    strcpy(NAME, argv[1]);
    struct equipped eq;
    sscanf(fgets(temp, sizeof(temp), f), "%d\n", &stat.STR);
    sscanf(fgets(temp, sizeof(temp), f), "%d\n", &stat.DEX);
    sscanf(fgets(temp, sizeof(temp), f), "%d\n", &stat.END);
    sscanf(fgets(temp, sizeof(temp), f), "%d\n", &stat.INT);
    sscanf(fgets(temp, sizeof(temp), f), "%d\n", &stat.LUK);
    sscanf(fgets(temp, sizeof(temp), f), "%d\n", &eq.wep);
    sscanf(fgets(temp, sizeof(temp), f), "%d\n", &eq.armor);
    sscanf(fgets(temp, sizeof(temp), f), "%d\n", &eq.helm);
    fgets(temp, sizeof(temp), f);
    *strchr(temp, '\n') = 0;
    char ** list = parse_args(temp, ";");
    for (i = 0; i < 5; i++){
      sscanf(list[i], "%d", &skills[i]);
      if(skills[i] != -1){
        skillinfo(&move, skills[i], stat);
        strcpy(skillnames[i], move.NAME);
      }
      else strcpy(skillnames[i], "\0");
    }
    free(list);
    fclose(f);
    hp = stat.END * 5;
    HPMAX = hp;
    sprintf(temp, "%s%d", IPATH, eq.wep);
    f = fopen(temp, "r");
    fgets(temp, sizeof(temp), f);
    fgets(temp, sizeof(temp), f);
    HIT = solve(fgets(temp, sizeof(temp), f), 0, stat);
    DMG = solve(fgets(temp, sizeof(temp), f), 0, stat);
    sscanf(fgets(temp, sizeof(temp), f), "%lf", &VAR);
    DMGRED = solve(fgets(temp, sizeof(temp), f), 0, stat);
    DODGE = solve(fgets(temp, sizeof(temp), f), 0, stat);
    fclose(f);
    double tempvar;
    sprintf(temp, "%s%d", IPATH, eq.armor);
    f = fopen(temp, "r");
    fgets(temp, sizeof(temp), f);
    fgets(temp, sizeof(temp), f);
    HIT *= solve(fgets(temp, sizeof(temp), f), 0, stat);
    DMG *= solve(fgets(temp, sizeof(temp), f), 0, stat);
    sscanf(fgets(temp, sizeof(temp), f), "%lf", &tempvar);
    VAR *= tempvar;
    DMGRED += solve(fgets(temp, sizeof(temp), f), 0, stat);
    DODGE += solve(fgets(temp, sizeof(temp), f), 0, stat);
    fclose(f);
    sprintf(temp, "%s%d", IPATH, eq.helm);
    f = fopen(temp, "r");
    fgets(temp, sizeof(temp), f);
    fgets(temp, sizeof(temp), f);
    HIT *= solve(fgets(temp, sizeof(temp), f), 0, stat);
    DMG *= solve(fgets(temp, sizeof(temp), f), 0, stat);
    sscanf(fgets(temp, sizeof(temp), f), "%lf", &tempvar);
    VAR *= tempvar;
    DMGRED += solve(fgets(temp, sizeof(temp), f), 0, stat);
    DODGE += solve(fgets(temp, sizeof(temp), f), 0, stat);
    fclose(f);
  }
  input = 0;
  for (i = 0; i < 5; i++){ // set skill CDs.
    if (skills[i] != -1){
      skillinfo(&move, skills[i], stat);
      if (strchr(move.EXA, 'Q')) skillCD[i] = 0;
      else skillCD[i] = move.CD;
    }
  }
  while (1){
    printf("loop\n");
    if (argc == 3) printf("Awaiting opponent...\n");
    if (sb.sem_num == 1){ // if holding major
      sb.sem_op = 1;
      semop(sem, &sb, 1);
      errcheck("releasing major semaphore");
      sb.sem_num = 0;
      sb.sem_op = -1;
      semop(sem, &sb, 1);
      errcheck("getting minor semaphore");
    }
    if (sb.sem_num == 0){ // if holding minor
      sb.sem_num = 1;
      sb.sem_op = -1;
      semop(sem, &sb, 1);
      errcheck("getting major semaphore");
      sb.sem_num = 0;
      sb.sem_op = 1;
      semop(sem, &sb, 1);
      errcheck("releasing minor semaphore");
      sb.sem_num = 1; // set for next loop
    }
    if (update.end){ // for the last to exit
      printf("\n");
      victory = 1;
      semop(sem, &sb, 1);
      errcheck("releasing major semaphore");
      break;
    }
    if (strcmp(argv[2], "0") == 0){
      char * line;
      line = readline(fdr);
      sscanf(line, "%d\n", &update.dmg);
      free(line);
      line = readline(fdr);
      sscanf(line, "%d\n", &update.heal);
      free(line);
      strcpy(update.action, "\0");
      line = readline(fdr);
      while (strchr(line, '|') == 0){
        strcat(update.action, line);
        free(line);
        line = readline(fdr);
      }
      free(line);
      for (i = 0; i < 4; i++){
        line = readline(fdr);
        sscanf(line, "%lf\n", &update.debuff[i]);
        free(line);
      }
      for (i = 0; i < 4; i++){
        line = readline(fdr);
        sscanf(line, "%d\n", &update.t[i]);
        free(line);
      }
      line = readline(fdr);
      strcpy(update.exa, line);
      free(line);
    }
    else { // going first does not read from pipe
      strcpy(argv[2], "0");
    }
    if (argc == 3) printf("%s", update.action); // what happened
    if (update.end){
      printf("\n");
      victory = 1;
      semop(sem, &sb, 1);
      errcheck("releasing major semaphore");
      break;
    }
    strcpy(update.action, "\0"); //overwrite action
    sleep(1);
    if (update.dmg){
      if (rand_double() > min(DODGE + buffs[3], 0.7)){
        if (strchr(update.exa, 'F') || strchr(update.exa,'P')){
          if (argc == 3) printf("You took %d irreducible damage.\n", update.dmg); // damage taken
          hp -= update.dmg;
        }
        else{
          if (argc == 3) printf("You took %d damage.\n", (int)(update.dmg * (1. - min(DMGRED + buffs[2], 0.85)))); // damage taken
          hp = hp - (int)(update.dmg * (1. - min(DMGRED + buffs[2], 0.85)));
        }
        if (argc == 3) printf("Current hp: %d.\n", hp);
      }
      else{
        if (strchr(update.exa,'H')){
          if (argc == 3) printf("You dodged the attack, but still took half damage\n");
          if (argc == 3) printf("You took %d damage.\n", (int)((update.dmg * (1. - min(DMGRED + buffs[2], 0.85))) / 2));
          hp = hp - (int)((update.dmg * (1. - min(DMGRED + buffs[2], 0.85))) / 2);
          if (argc == 3) printf("Current hp: %d.\n", hp);
          strcat(update.action, "Your opponent dodged the last attack!\n");
        }
        else if (strchr(update.exa,'P')){
          if (argc == 3) printf("You are unable to dodge or reduce the damage from the attack\n");
          if (argc == 3) printf("You took %d irreducible damage.\n", update.dmg);
          hp -= update.dmg;
          if (argc == 3) printf("Current hp: %d.\n", hp);
          strcat(update.action, "Your opponent could not dodge the last attack!\n");
        }
        else{
          if (argc == 3) printf("You dodged the attack!\n");
          strcat(update.action, "Your opponent dodged the last attack!\n");
        }
      }
      sleep(1);
    }
    update.dmg = 0;
    if (update.heal && argc == 3){
      printf("Your opponent healed for %d.\n", update.heal);
      sleep(1);
    }
    update.heal = 0;
    if (hp <= 0){ // dead or alve
      if (argc == 3) printf("You died.\n");
      printf("\n");
      strcpy(update.action, "Your opponent died\n"); //note it overwrites dodge
      update.end = 1;
      sleep(1);
    }
    else {
      for (i = 0; i < 4; i++){ //debuff handling
        if (update.debuff[i]){
          buffs[i] = -update.debuff[i];
          bufftime[i] = update.t[i];
          if (argc == 3) printf("Your opponent has decreased your ");
          switch (i){
            case 0: if (argc == 3) printf("Hit Chance");
              break;
            case 1: if (argc == 3) printf("Outgoing Damage");
              break;
            case 2: if (argc == 3) printf("Damage Reduction");
              break;
            case 3: if (argc == 3) printf("Dodge Chance");
              break;
          }
          if (argc == 3) {
            printf(" by %lf%% for %d turns.\n", update.debuff[i] * 100, update.t[i]);
            sleep(1);
          }
        }
        update.debuff[i] = 0;
        update.t[i] = 0;
      }
      strcpy(update.exa, "\0");
      printf("\n"); // start of interactable turn.
      if (argc == 3) printf("Current hp: %d.\n", hp);
      if (argc == 3) printf("Your turn:\n");
      int boolean = 0;
      if (argc == 3) {
        char choices[10];
        choices[0] = '\0';
        char choice[3];
        for (i = 0; i < 5; i++){
          if (skills[i] != -1){
            printf("%d) %s\n", i, skillnames[i]);
            sprintf(choice, "%d;", i);
            strcat(choices, choice);
          }
        }
        choices[strlen(choices) - 1] = '\0';
        while (!boolean){
          input = choose(choices);
          if (skillCD[input] > 0) printf("Skill is recharging.\n");
          else boolean = 1;
        }
      }
      else{ // cpu decision
        while (!boolean){
          input = (int) (rand_double() * 5);
          if (skills[input] != -1 && skillCD[input] == 0) boolean = 1;
        }
      }
      skillinfo(&move, skills[input], stat);
      strcat(update.action, "Your opponent used ");
      strcat(update.action, skillnames[input]);
      strcat(update.action, ".\n");
      strcpy(update.exa, move.EXA);
      if (argc == 3) printf("You used %s.\n", skillnames[input]);
      if (move.HITMOD > 0.0001){ // in case of 0, 0.0, 10^-# etc. shenanigans.
        strcat(update.action, "Your opponent attacks!\n");
        if (argc == 3) printf("You attack.\n");
        if (rand_double() > HIT * move.HITMOD * (1 + buffs[0])){
          update.dmg = (int)(DMG * move.DMGMOD * (1 + buffs[1]) * (1 + VAR * move.VARMOD * (rand_double() * 2 - 1)));
          if (argc == 3) printf("You dealt %d damage!\n", update.dmg);
          if (strchr(move.EXA, 'V')){
            update.heal = update.dmg;
            hp = min(HPMAX, hp + update.heal);
            if (argc == 3) printf("You healed for %d.\n", update.heal);
          }
        }
        else{
          if (argc == 3) printf("You missed!\n");
          strcat(update.action, "Your opponent missed!\n");
        }
      }
      printf("EXA check1\n");
      if (strchr(move.EXA, 'A')){
        int attacks;
        sscanf(strchr(move.EXA, 'A') + 1, "%d", &attacks);
        attacks--;
        int dtemp;
        for (; attacks > 0; attacks--){
          if (argc == 3) printf("You attack.\n");
          strcat(update.action, "Your opponent attacks again!\n");
          if (rand_double() < HIT * move.HITMOD * (1 + buffs[0])){
            dtemp = (int)(DMG * move.DMGMOD * (1 + buffs[1]) * (1 + VAR * move.VARMOD * (rand_double() * 2 - 1)));
            update.dmg += dtemp;
            if (argc == 3) printf("You dealt %d damage!\n", dtemp);
            if (strchr(move.EXA, 'V')){
              hp = min(HPMAX, hp + update.dmg - update.heal);
              if (argc == 3) printf("You healed for %d.\n", update.dmg - update.heal);
              update.heal += update.dmg;
            }
          }
          else{
            if (argc == 3) printf("You missed!\n");
            strcat(update.action, "Your opponent missed!\n");
          }
        }
      }
      printf("EXA check2\n");
      if (strchr(move.EXA, 'H')){
        update.heal = (int)(DMG * move.DMGMOD * (1 + VAR * move.VARMOD * (rand_double() * 2 - 1)));
        hp = min(HPMAX, hp + update.heal);
        if (argc == 3) printf("You healed for %d.\n", update.heal);
      }
      printf("buff check1\n");
      if (move.HITBUFF){
        if (strchr(move.EXA, 'D')){
          update.debuff[0] = move.HITBUFF;
          update.t[0] = move.TURNS;
          if (argc == 3) printf("You reduced your opponent's Hit Chance!\n");
        }
        else{
          buffs[0] = move.HITBUFF;
          bufftime[0] = move.TURNS + 1;
          strcat(update.action, "Your opponent increased their Hit Chance!\n");
          if (argc == 3) printf("You increased your Hit Chance!\n");
        }
      }
      printf("buff check2\n");
      if (move.DMGBUFF){
        if (strchr(move.EXA, 'D')){
          update.debuff[1] = move.DMGBUFF;
          update.t[1] = move.TURNS;
          if (argc == 3) printf("You reduced your opponent's Outgoing Damage!\n");
        }
        else{
          buffs[1] = move.DMGBUFF;
          bufftime[1] = move.TURNS + 1;
          strcat(update.action, "Your opponent increased their Outgoing Damage!\n");
          if (argc == 3) printf("You increased your Outgoing Damage!\n");
        }
      }
      printf("buff check3\n");
      if (move.REDPLUS){
        if (strchr(move.EXA, 'D')){
          update.debuff[2] = move.REDPLUS;
          update.t[2] = move.TURNS;
          if (argc == 3) printf("You reduced your opponent's Damage Resistance!\n");
        }
        else{
          buffs[2] = move.REDPLUS;
          bufftime[2] = move.TURNS + 1;
          strcat(update.action, "Your opponent increased their Damage Resistance!\n");
          if (argc == 3) printf("You increased your Damage Resistance!\n");
        }
      }
      printf("buff check4\n");
      if (move.DODGEPLUS){
        if (strchr(move.EXA, 'D')){
          update.debuff[3] = move.DODGEPLUS;
          update.t[3] = move.TURNS;
          if (argc == 3) printf("You reduced your opponent's Dodge Chance!\n");
        }
        else{
          buffs[3] = move.DODGEPLUS;
          bufftime[3] = move.TURNS + 1;
          strcat(update.action, "Your opponent increased their Dodge Chance!\n");
          if (argc == 3) printf("You increased your Dodge Chance!\n");
        }
      }
      printf("\n");
      printf("bufftime check\n");
      for (i = 0; i < 4; i++){ //resolve buffs/debuffs at end of turn
        if (bufftime[i] > 0){
          bufftime[i]--;
          if (!bufftime[i]){
            if (argc == 3) printf("Your ");
            switch (i){
              case 0: if (argc == 3) printf("Hit Chance");
                break;
              case 1: if (argc == 3) printf("Outgoing Damage");
                break;
              case 2: if (argc == 3) printf("Damage Reduction");
                break;
              case 3: if (argc == 3) printf("Dodge Chance");
                break;
            }
            if (argc == 3) {
              printf(" has returned to normal.\n");
              sleep(1);
            }
            buffs[i] = 0;
          }
        }
      }
      printf("skilltime check1\n");
      for (i = 0; i < 5; i++){ // resolve skill CD at end of turn
        if (skillCD[i] > 0){
          skillCD[i]--;
          if (!skillCD[i]){
            printf("%s", skillnames[i]);
            if (argc == 3) {
              printf(" has recharged.\n");
              sleep(1);
            }
          }
        }
      }
    }
    // pipe out string of what you did, for opponent
    printf("pipe check1\n");
    printf("pipe check2\n");
    errcheck("opening pipe");
    sprintf(temp, "%d\n", update.dmg);
    write(fdw, temp, strlen(temp));
    sprintf(temp, "%d\n", update.heal);
    write(fdw, temp, strlen(temp));
    write(fdw, update.action, strlen(update.action));
    write(fdw, "|\n", strlen("|\n")); // end of action
    for (i = 0; i < 4; i++){
      sprintf(temp, "%lf\n", update.debuff[i]);
      write(fdw, temp, strlen(temp));
    }
    for (i = 0; i < 4; i++){
      sprintf(temp, "%d\n", update.t[i]);
      write(fdw, temp, strlen(temp));
    }
    sprintf(temp, "%s\n", update.exa);
    write(fdw, temp, strlen(temp));
    sprintf(temp, "%d\n", update.end);
    write(fdw, temp, strlen(temp));
    errcheck("something");
  }
  free(update.action);
  free(update.exa);
  free(move.NAME);
  free(move.EXA);
  close(fdr);
  close(fdw);
  return victory;
}

char * readline(int fd){
  char * line = malloc(sizeof(char) * 1024);
  char buf[3];
  int i = 0;
  while(1){
    if (!read(fd, buf, 1)) break;
    line[0] = buf[0];
    if (line[i] == '\n') break;
  }
  return line;
}
