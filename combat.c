#include "rpg.h"

#define KEY 2473842

int main(int argc, char *argv[]){ // second is file, third is 0 or 1, 1 starts. Fourth is if cpu controlled
  if (argc == 4);
  int victory = 0; // win or lose. 1 or 0
  int sem;
  sem = semget(KEY, 1, 0);
  errcheck("getting semaphore");
  struct sembuf sb;
  sb.sem_num = 0;
  int input;
  char NAME[25];
  int HPMAX;
  int hp;
  double HIT;
  double DMG;
  double VAR;
  double DMGRED;
  double DODGE;
  int skills[5];
  char * skillnames[5];
  int skillCD[5];
  double buffs[4]; // hitmod, dmgmod, dmgred add, dodge add.
  int bufftime[4]; // respective to buffs, how long it last.
  int i = 0; // for for loops
  for (; i < 4; i++){
    buffs[i] = 0;
    bufftime[i] = 0;
  }
  struct turn * update;
  struct skill * move;
  move.NAME = malloc(sizeof(char) * 30);
  move.EXA = malloc(sizeof(char) * 10);
  struct stats stat;
  FILE * f; // for all the fopens.
  char temp[512; // for temporary string holding for functions
  if (argc != 3){ // == 3 for non cpu

    // do the proper dirent stuff

    f = fopen(argv[1], "r");
    fgets(NAME, sizeof(NAME), f);
    sscanf(fgets(temp, 512, f), "%d\n", hp);
    double hpmod;
    sscanf(fgets(temp, 512, f), "%lf\n", hpmod);
    hp *= (rand_double() * 2 - 1) * hpmod + 1;
    HPMAX = hp;
    sscanf(fgets(temp, 512, f), "%lf\n", HIT);
    sscanf(fgets(temp, 512, f), "%lf\n", DMG);
    sscanf(fgets(temp, 512, f), "%lf\n", VAR);
    sscanf(fgets(temp, 512, f), "%lf\n", DMGRED);
    sscanf(fgets(temp, 512, f), "%lf\n", DODGE);
    for (i = 0; i < 5; i++) sscanf(fgets(temp, 512, f), "%d\n", skills[i]);
    for (i = 0; i < 5; i++) {
      if (skills[i] >= 0){
        *strchr(fgets(temp, 512, f), 0, player.stats, '\n') = 0;
        skillnames[i] = temp;
      }
    }
    stat.STR = 50; // for the sake of skills
    stat.DEX = 50;
    stat.END = 50;
    stat.INT = 50;
    stat.LUK = 50;
  }
  else{

    // do the proper dirent stuff

    strcpy(NAME, argv[1]);
    struct equipped eq;
    f = fopen(argv[1], "r");
    sscanf(fgets(temp, 5, f), "%d\n", stat.STR);
    sscanf(fgets(temp, 5, f), "%d\n", stat.DEX);
    sscanf(fgets(temp, 5, f), "%d\n", stat.END);
    sscanf(fgets(temp, 5, f), "%d\n", stat.INT);
    sscanf(fgets(temp, 5, f), "%d\n", stat.LUK);
    sscanf(fgets(temp, 5, f), "%d\n", eq.wep);
    sscanf(fgets(temp, 5, f), "%d\n", eq.armor);
    sscanf(fgets(temp, 5, f), "%d\n", eq.helm);
    fclose();
    hp = stat.END * 5;
    HPMAX = hp;
    sprintf(temp, )
    f = fopen(eq.wep, )
  }
  fclose(f);
  int fd; //pipe
  int input = 0;
  for (i = 0; i < 5; i++){ // set skill CDs.
    if (skills[i] >= 0){

      // do the dirent stuff

      skillinfo(move, skills[i], stat);
      if (strchr(move.EXA, 'Q')) skillCD[i] = move.CD;
    }
  }
  while (1){
    sb.sem_op = -1;
    if (argc == 4) printf("Awaiting opponent...");
    semop(sem, &sb, 1);
    errcheck("getting semaphore");
    if (strcmp(argv[2], "0") == 0){
      fd = open("CombatToCombat", O_RDONLY);
      read(fd, update, sizeof(update));
      close(fd);
    }
    else {
      update = (turn *) malloc(sizeof(turn));
      update->action = malloc(sizeof(char) * 512);
      update->dmg = 0;
      update->heal = 0;
      for (i = 0; i < 4; i++) {
        update->debuff[i] = 0;
        update->t[i] = 0;
      }
      update->exa = malloc(sizeof(char) * 10);
      update->end = 0;
      strcpy(argv[2], "0");
    }
    if (update->end){
      if (argc == 4) printf(update->action);
      printf("\n");
      victory = 1;
      break;
    }
    if (argc == 4) printf(update->action); // what happened
    strcpy(update->action, ""); //overwrite action
    if (update->dmg){
      if (d > min(DODGE + buffs[3], 0.7)){
        if (strchr(update->exa, 'F') || strchr(update->exa,'P')){
          if (argc == 4) printf("You took %d irreducible damage.\n", update->dmg); // damage taken
          hp -= update.dmg;
        }
        else{
          if (argc == 4) printf("You took %d damage.\n", (int)(update->dmg * (1. - min(DMGRED + buffs[2], 0.85)))); // damage taken
          hp = hp - (int)(update->dmg * (1. - min(DMGRED + buffs[2], 0.85)));
        }
        if (argc == 4) printf("Current hp: %d.\n", hp);
      }
      else{
        if (strchr(update->exa,'H')){
          if (argc == 4) printf("You dodged the attack, but still took half damage\n");
          if (argc == 4) printf("You took %d damage.\n", (int)((update->dmg * (1. - min(DMGRED + buffs[2], 0.85))) / 2));
          hp = hp - (int)((update->dmg * (1. - min(DMGRED + buffs[2], 0.85))) / 2);
          if (argc == 4) printf("Current hp: %d.\n", hp);
          strcat(update->action, "Your opponent dodged the last attack!\n");
        }
        else if (strchr(update->exa,'P')){
          if (argc == 4) printf("You are unable to dodge or reduce the damage from the attack\n");
          if (argc == 4) printf("You took %d irreducible damage.\n", update->dmg;
          hp -= update->dmg;
          if (argc == 4) printf("Current hp: %d.\n", hp);
          strcat(update->action, "Your opponent could not dodge the last attack!\n");
        }
        else{
          if (argc == 4) printf("You dodged the attack!\n");
          strcat(update->action, "Your opponent dodged the last attack!\n");
        }
      }
    }
    update->dmg = 0;
    if (update->heal && argc == 4){
      printf("Your opponent healed for %d.\n", update->heal);
      update->heal = 0;
    }
    if (hp <= 0){ // dead or alve
      if (argc == 4) printf("You died.\n");
      printf("\n");
      strcpy(update->action, "Your opponent died\n"); //note it overwrites dodge
      update->end = 1;
    }
    else {
      for (i = 0; i < 4; i++){ //debuff handling
        if (update->debuff[i]){
          buffs[i] = -update->debuff[i];
          bufftime[i] = update->t[i];
          if (argc == 4) printf("Your opponent has decreased your ");
          switch (i){
            case 0: if (argc == 4) printf("Hit Chance");
              break;
            case 1: if (argc == 4) printf("Outgoing Damage");
              break;
            case 2: if (argc == 4) printf("Damage Reduction");
              break;
            case 3: if (argc == 4) printf("Dodge Chance");
              break;
          }
          if (argc == 4) printf(" by %lf%% for %d turns.\n", update->debuff[i] * 100, update->t[i]);
        }
        update->debuff[i] = 0;
        update->t[i] = 0;
      }
      strcpy(update->exa, "");
      printf("\n"); // start of interactable turn.
      if (argc == 4) printf("Current hp: %d.\n", hp);
      if (argc == 4) printf("Your turn:\n");
      int boolean = 0;
      if (argc == 4) {
        char choices[10];
        choices[0] = '\0';
        char choice[3];
        for (i = 0; i < 5; i++){
          if (skills[i] != -1){

            // get the skill name for printf

            printf("%d) %s\n", i, );
            sprintf(choice, "%d;", i);
            strcat(choices, choice);
          }
        }
        choices[strlen(choices) - 1] = '\0';
        while (boolean){
          input = choose(choices);
          if (skillCD[input] > 0) printf("Skill is recharging.\n");
          else boolean = 1;
        }
      }
      else{ // cpu decision
        while (boolean){
          input = (int) (rand_double() * 5);
          if (skills[input] != -1 && skillCD[input] == 0) boolean = 1;
        }
      }
      skillinfo(move, skills[input], stat);
      strcat(update->action, "Your opponent used ");
      strcat(update->action, move.NAME);
      strcat(update->action, ".\n");
      if (argc == 4) printf("You used %s.\n", move.NAME);
      if (move.HIT > 0.0001){ // in case of 0, 0.0, 10^-# etc. shenanigans.
        strcat(update->action, "Your opponent attacks!\n");
        if (argc == 4) printf("You attack.\n");
        if (rand_double() < HIT * move.HITMOD * buffs[0]){
          update->dmg = (int)(DMG * move.DMGMOD * buffs[1] * (1 + VAR * move.VARMOD * (rand_double() * 2 - 1)));
          if (argc == 4) printf("You dealt %d damage!\n", update->dmg);
          if (strchr(move.EXA, "V")){
            update->heal = update->dmg;
            hp = min(HPMAX, hp + update->heal);
            if (argc == 4) printf("You healed for %d.\n", update->heal);
          }
        }
        else{
          if (argc == 4) printf("You missed!\n");
          strcat(update->action, "Your opponent missed!\n");
        }
      }
      if (strchr(move.EXA, "A")){
        int attacks;
        sscanf(*(strchr(move.EXA, "A") + 1), "%d", attacks);
        attacks--;
        int dtemp;
        for (; attacks > 0; attacks--){
          if (argc == 4) printf("You attack.\n");
          strcat(update->action, "Your opponent attacks again!\n");
          if (rand_double() < HIT * move.HITMOD * buffs[0]){
            dtemp = (int)(DMG * move.DMGMOD * buffs[1] * (1 + VAR * move.VARMOD * (rand_double() * 2 - 1)));
            update->dmg += dtemp;
            if (argc == 4) printf("You dealt %d damage!\n", dtemp);
            if (strchr(move.EXA, "V")){
              hp = min(HPMAX, hp + update->dmg - update->heal);
              if (argc == 4) printf("You healed for %d.\n", update->dmg - update->heal);
              update->heal += update->dmg;
            }
          }
          else{
            if (argc == 4) printf("You missed!\n");
            strcat(update->action, "Your opponent missed!\n");
          }
        }
      }
      if (strchr(move.EXA, "h")){
        update->heal = (int)(DMG * move.DMGMOD * (1 + VAR * move.VARMOD * (rand_double() * 2 - 1)));
        hp = min(HPMAX, hp + update->heal);
        if (argc == 4) printf("You healed for %d.\n", update->heal);
      }
      if (move.HITBUFF){
        if (strchr(move.EXA, "D")){
          update.debuff[0] = move.HITBUFF;
          update.t[0] = move.TURNS;
          if (argc == 4) printf("You reduced your opponent's Hit Chance!\n");
        }
        else{
          buffs[0] = move.HITBUFF;
          bufftime[0] = move.TURNS + 1;
          strcat(update.action, "Your opponent increased their Hit Chance!\n");
          if (argc == 4) printf("You increased your Hit Chance!\n");
        }
      }
      if (move.DMGBUFF){
        if (strchr(move.EXA, "D")){
          update.debuff[1] = move.DMGBUFF;
          update.t[1] = move.TURNS;
          if (argc == 4) printf("You reduced your opponent's Outgoing Damage!\n");
        }
        else{
          buffs[1] = move.HITBUFF;
          bufftime[1] = move.TURNS + 1;
          strcat(update.action, "Your opponent increased their Outgoing Damage!\n");
          if (argc == 4) printf("You increased your Outgoing Damage!\n");
        }
      }
      if (move.REDPLUS){
        if (strchr(move.EXA, "D")){
          update.debuff[2] = move.REDPLUS;
          update.t[2] = move.TURNS;
          if (argc == 4) printf("You reduced your opponent's Damage Resistance!\n");
        }
        else{
          buffs[2] = move.REDPLUS;
          bufftime[2] = move.TURNS + 1;
          strcat(update.action, "Your opponent increased their Damage Resistance!\n");
          if (argc == 4) printf("You increased your Damage Resistance!\n");
        }
      }
      if (move.DODGEPLUS){
        if (strchr(move.EXA, "D")){
          update.debuff[3] = move.DODGEPLUS;
          update.t[3] = move.TURNS;
          if (argc == 4) printf("You reduced your opponent's Dodge Chance!\n");
        }
        else{
          buffs[3] = move.DODGEPLUS;
          bufftime[3] = move.TURNS + 1;
          strcat(update.action, "Your opponent increased their Dodge Chance!\n");
          if (argc == 4) printf("You increased your Dodge Chance!\n");
        }
      }
      printf("\n");
      for (i = 0; i < 4; i++){ //resolve buffs/debuffs at end of turn
        if (bufftime[i] > 0){
          bufftime[i]--;
          if (!bufftime[i]){
            if (argc == 4) printf("Your ");
            switch (i){
              case 0: if (argc == 4) printf("Hit Chance");
                break;
              case 1: if (argc == 4) printf("Outgoing Damage");
                break;
              case 2: if (argc == 4) printf("Damage Reduction");
                break;
              case 3: if (argc == 4) printf("Dodge Chance");
                break;
            }
            if (argc == 4) printf(" has returned to normal.\n");
            buffs[i] = 0;
          }
        }
      }
      for (i = 0; i < 5; i++){ // resolve skill CD at end of turn
        if (skillCD[i] > 0){
          skillCD[i]--;
          if (!skillCD[i]){

            //get name of skill


            if (argc == 4) printf(" has recharged.\n");
          }
        }
      }
    }
    // pipe out string of what you did, for opponent
    fd = open("CombatToCombat", O_WRONLY);
    write(fd, update, sizeof(update));
    close(fd);
    sb.sem_op = 1;
    semop(sem, &sb, 1);
    errcheck("releasing semaphore");
    if (update->end) break;
  }
  free(update->action);
  free(move.NAME);
  free(move.EXA);
  return victory;
}
