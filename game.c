#include "rpg.h"

union semun {
  int              val;    /* Value for SETVAL */
  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
  unsigned short  *array;  /* Array for GETALL, SETALL */
  struct seminfo  *__buf;  /* Buffer for IPC_INFO
                              (Linux-specific) */
};

int readInt(FILE * c);
void iteminfo(struct item * object, int id, struct stats s);
void save(struct character player);

int main(){
  srand(time(NULL));
  struct character player;
  player.NAME = malloc(sizeof(char) * 26);
  char skillnames[5][30];
  char * itemDict[6] = {"unarmed", "unarmored", "helmless", "Knife", "Leather Armor", "Hat"};
  char * skillDict[11] = {"Strike", "Double Strike", "Defend", "Heal", "Leech Life", "Rage", "Quadruple Strike", "Frighten", "Seeking Bolt", "Fireball", "Disintegrate"};
  struct item object;
  object.NAME = malloc(sizeof(char) * 30);
  struct skill move;
  move.NAME = malloc(sizeof(char) * 30);
  move.EXA = malloc(sizeof(char) * 16);
  int statarray[5];
  int input = 0;
  FILE * c;
  union semun su;
  su.val = 1;
  char choices[100]; // note that this number will inhibit inventory size
  printf("Welcome to [game name]!\n");
  printf("Make selections by typing the number corresponding to your choice.\n");
  int del = 1;;
  while(del){
    printf("1) Create Character\n2) Select Character\n3) Delete Character\n");
    strcpy(choices, "1;2;3");
    input = choose(choices);
    int boolean = 1;
    while (boolean){
      DIR * pcs = opendir("characters");
      boolean = 0;
      int input1;
      if (input != 0) input1 = input;
      char cn[30];
      char fn[40];
      int i = 1;
      int fd;
      switch (input1){ // Character creation/selection/deletion
        case 1: // Create character file
          printf("Character name (max 25 alphanumerical letters):\n");
          while (i){
            fgets(cn, 26, stdin);
            *strchr(cn, '\n') = 0;
            sprintf(fn, "%s%s", CPATH, cn);
            fd = open(fn, O_WRONLY | O_CREAT | O_EXCL, 0644);
            if (errno){
              printf("Character already exists.\n");
              errno = 0;
            }
            else i = 0;
          }
          int i = 0;
          for (; i < 5; i++) write(fd, "1\n", strlen("1\n"));
          write(fd, "0\n", strlen("0\n"));
          write(fd, "1\n", strlen("1\n"));
          write(fd, "2\n", strlen("2\n"));
          write(fd, "0;-1;-1;-1;-1\n", strlen("0;-1;-1;-1;-1\n"));
          write(fd, "-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1\n", strlen("-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1\n"));
          write(fd, "-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1\n", strlen("-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1\n"));
          errcheck("creating character file defaults");
          close(fd);
          c = fopen(fn, "r");
          errcheck("opening character file");
          strcpy(player.NAME, cn);
          del = 0;
          break;
        default: // Select or delete character file
          if (input1 == 2) printf("Select a character:\n\n");
          else printf("Select a character to delete:\n\n");
          struct dirent * pc;
          int ccount = 1;
          char names[25][30];
          char choices[52]; // max number of characters is 25.
          strcpy(choices, "0;\0");
          printf("0) Go Back\n\n");
          char choice[4];
          pc = readdir(pcs);
          while (pc){
            if (pc->d_name[0] != '.'){
              printf("%d) %s\n", ccount, pc->d_name);
              strcpy(names[ccount], pc->d_name);
              sprintf(choice, "%d;", ccount);
              strcat(choices, choice);
              ccount++;
            }
            pc = readdir(pcs);
          }
          choices[strlen(choices) - 1] = '\0';
          input = choose(choices);
          if (input == 0){
            closedir(pcs);
            system("clear");
            break;
          }
          sprintf(choices, "%s%s", CPATH, names[input]); // reusing choices
          if (input1 == 3){
            remove(choices);
            errcheck("deleting file");
            boolean = 1;
            closedir(pcs);
          }
          else if (input1 == 2){
            strcpy(player.NAME, names[input]);
            c = fopen(choices, "r");
            errcheck("opening character file");
            del = 0;
            closedir(pcs);
          }
          break;
      }
    }
  }
  printf("Loading character...\n"); // update character struct
  player.stats.STR = readInt(c);
  statarray[0] = player.stats.STR;
  player.stats.DEX = readInt(c);
  statarray[1] = player.stats.DEX;
  player.stats.END = readInt(c);
  statarray[2] = player.stats.END;
  player.stats.INT = readInt(c);
  statarray[3] = player.stats.INT;
  player.stats.LUK = readInt(c);
  statarray[4] = player.stats.LUK;
  player.equipped.wep = readInt(c);
  player.equipped.armor = readInt(c);
  player.equipped.helm = readInt(c);
  char data[100];
  fgets(data, sizeof(data), c);
  *strchr(data, '\n') = 0;
  char ** args = parse_args(data, ";");
  int i = 0;
  for (; i < 5; i++) {
    sscanf(args[i], "%d", &player.skills[i]);
    strcpy(skillnames[i], skillDict[player.skills[i]]);
  }
  free(args);
  fgets(data, sizeof(data), c);
  *strchr(data, '\n') = 0;
  args = parse_args(data, ";");
  for (i = 0; i < 15; i++) sscanf(args[i], "%d", &player.inventory.invI[i]);
  free(args);
  fgets(data, sizeof(data), c);
  *strchr(data, '\n') = 0;
  args = parse_args(data, ";");
  for (i = 0; i < 15; i++) sscanf(args[i], "%d", &player.inventory.invS[i]);
  free(args);
  fclose(c);
  sleep(1);
  system("clear");
  while (1){
    printf("Select an option:\n");
    printf("1) Character Info\n");
    printf("2) Training\n");
    printf("3) Inventory\n");
    printf("4) Skills\n");
    printf("5) Random Encounter\n");
    printf("6) PvP\n");
    printf("7) Save\n");
    printf("8) Exit Game\n");
    printf("\n");
    strcpy(choices, "1;2;3;4;5;6;7;8");
    input = choose(choices);
    system("clear");
    switch (input){
      case 1: //Display character info
        printf("%s\n\n", player.NAME);
        printf("STR: %d\nDEX: %d\nEND: %d\nINT: %d\nLUK: %d\n", player.stats.STR, player.stats.DEX, player.stats.END, player.stats.INT, player.stats.LUK);
        printf("\nEquipment:\nWeapon: %s\nArmor: %s\nHelm: %s\n", itemDict[player.equipped.wep], itemDict[player.equipped.armor], itemDict[player.equipped.helm]);
        printf("\nSkills:\n");
        int j = 0;
        for (; j < sizeof(player.skills) / sizeof(int); j++){
          if (player.skills[j] != -1) printf("%d. %s\n", j, skillnames[j]);
          else printf("%d.\n", j);
        }
        printf("\n");
        printf("0) Return to game\n");
        strcpy(choices, "0");
        input = choose(choices);
        break;
      case 2: // Training
        // Training




        break;
      case 3: // Inventory (items)
        while (1){
          int index = 0;
          int n;
          char choices[32]; // max number storage is 15.
          strcpy(choices, "0;\0");
          printf("0) Go Back\n");
          char choice[4];
          for (; index < sizeof(player.inventory.invI); index++){
            if (player.inventory.invI[index] == -1) break;
            printf("%d) %s\n", index + 1, itemDict[player.inventory.invI[index]]);
            sprintf(choice, "%d;", index + 1);
            strcat(choices, choice);
          }
          choices[strlen(choices) - 1] = '\0';
          input = choose(choices);
          if (input == 0) break;
          system("clear");
          iteminfo(&object, player.inventory.invI[input - 1], player.stats);
          printf("%s: %s\n","Name", object.NAME);
          printf("%s: %c\n","Type", object.type);
          printf("%s: %lf\n","Hit Chance Modifier", object.HIT);
          printf("%s: %lf\n","Damage Modifier", object.DMG);
          printf("%s: %lf\n","Damage Variance", object.VAR);
          printf("%s: %lf\n","Damage Reduction", object.DMGRED);
          printf("%s: %lf\n","Dodge Chance", object.DODGE);
          printf("\n");
          printf("%s: \n", "Stat Bonuses (STR, DEX, END, INT, LUK)");
          for(n = 0; n < 5; n++) {
              printf("%d, ", object.STAT[n]);
          }
          printf("\n");
          printf("%s: \n", "Stat Requirements (STR, DEX, END, INT, LUK)");
          for(n = 0; n < 5; n++) {
              printf("%d, ", object.REQ[n]);
          }
          int input2 = input;
          printf("\n\n1) Equip\n");
          printf("2) Go Back\n");
          printf("3) Sell\n");
          strcpy(choices, "1;2;3");
          input = choose(choices);
          int boolean = 1;
          switch(input) {
            case 1:
              for (n = 0; n < 5; n++){
                if (object.REQ[n] > statarray[n]) boolean = 0;
              }
              if (boolean == 0){
                printf("You do not meet the requirements\n");
                break;
              }
              if (object.type == 'W') player.equipped.wep = object.ID;
              else if (object.type == 'A') player.equipped.armor = object.ID;
              else if (object.type == 'H') player.equipped.helm = object.ID;
              printf("Item equipped\n");
              sleep(1);
            case 2:
              printf("Going Back...\n");
              break;
            case 3:
              n = player.inventory.invI[input2];
              for (; n < 14; n++){
                player.inventory.invI[n] = player.inventory.invI[n + 1];
              }
              player.inventory.invI[15] = -1;
              printf("Item Sold.\n");
              break;
          }
          system("clear");
        }
        break;
      case 4: // manage skills
        while (1){
          int index = 0;
          int n;
          int exit = 0;
          char choices[32]; // max number storage is 15.
          strcpy(choices, "0;\0");
          printf("0) Go Back\n");
          char choice[4];
          for (; index < sizeof(player.inventory.invS); index++){
            if (player.inventory.invS[index] == -1) break;
            printf("%d) %s\n", index + 1, skillDict[player.inventory.invS[index]]);
            sprintf(choice, "%d;", index + 1);
            strcat(choices, choice);
          }
          choices[strlen(choices) - 1] = '\0';
          input = choose(choices);
          if (input == 0) break;
          skillinfo(&move, player.inventory.invS[input - 1], player.stats);
          printf("%s: %s\n","Name", move.NAME);
          printf("%s: %lf\n","Hit Chance Modifier", move.HITMOD);
          printf("%s: %lf\n","Damage Modifier", move.DMGMOD);
          printf("%s: %lf\n","Damage Variance", move.VARMOD);
          printf("%s: %lf\n","Hit Chance Buff", move.HITBUFF);
          printf("%s: %lf\n","Damage Buff", move.DMGBUFF);
          printf("%s: %lf\n","Damage Reduction Buff", move.REDPLUS);
          printf("%s: %lf\n","Dodge Chance Buff", move.DODGEPLUS);
          printf("%s: %d\n","Buff Duration (if any)", move.TURNS);
          printf("%s: %d\n","Skill Cooldown", move.CD);
          for (n = 0; n < strlen(move.EXA); n++){
            char code = move.EXA[n];
            if (code == '0') break;
            switch (code){
              case '\n': break;
              case 'A':
                n++;
                printf("Makes %d attacks\n", move.EXA[n]);
                break;
              case 'Q': printf("- Can be used from the beginning of combat\n");
                break;
              case 'D': printf("- Applies Debuffs to opponent rather than buffing self\n");
                break;
              case 'h': printf("- Heals instead of dealing damage\n");
                break;
              case 'V': printf("- Heals for damage dealt\n");
                break;
              case 'H': printf("- Deals half damage if dodged\n");
                break;
              case 'F': printf("- Damage cannot be reduced\n");
                break;
              case 'P': printf("- Damage cannot be dodged or reduced\n");
                break;
              default: printf("ERROR Unknown\n");
                break;
            }
          }
          int input2 = input;
          printf("\n\n1) Use instead of...\n");
          printf("2) Go Back\n");
          printf("3) Forget Skill\n");
          strcpy(choices, "1;2;3");
          input = choose(choices);
          switch(input) {
            case 1:
              for (n = 1; n < 5; n++){
                if (player.skills[n] = -1) printf("%d) None\n", n);
                else printf("%d) %s\n", n, skillDict[player.skills[n]]);
              }
              strcpy(choices, "1;2;3;4");
              input = choose(choices);
              player.skills[input] = player.inventory.invS[input2];
              strcpy(skillnames[input], skillDict[player.skills[input]]);
              break;
            case 2:
              printf("Going Back...\n");
              system("clear");
              break;
            case 3:
              n = player.inventory.invS[input2];
              for (; n < 14; n++){
                player.inventory.invS[n] = player.inventory.invS[n + 1];
              }
              player.inventory.invS[15] = -1;
              printf("Skill forgotten.\n");
              break;
          }
          system("clear");
        }
        break;
      case 5:
        save(player);
        printf("Preparing for combat...\n");
        mkfifo("CombatToCombat", 0666);
        int sem;
        sem = semget(KEY, 1, IPC_CREAT | 0644);
        errcheck("creating semaphore");
        semctl(sem, 0, SETVAL, su);
        errcheck("setting semaphore");
        char * coin;
        char * coin2;
        if (rand_double() < 0.5){
          coin2 = "0";
          coin = "1";
        }
        else{
          coin = "0";
          coin2 = "1";
        }
        sleep(2);
        pid_t pidU = fork(); // player
        printf("%d\n", pidU);
        if (pidU > 0) { // main game process
          /*pid_t pidC = fork(); // cpu
          if (pidC <= 0){
            int enc = (int)(rand_double() * 2); //unweighted random encounters.
            char encs[50];
            sprintf(encs, "%s%d", EPATH, enc);
            FILE * fenc = fopen(encs, "r");
            fgets(encs, sizeof(encs), fenc);
            *strchr(encs, '\n') = 0;
            fclose(fenc);
            printf("You encounter a(n) %s!\n", encs);
            sprintf(encs, "%d", enc);
            execlp("./combat", "./combat", encs, coin2, "1", NULL);
            errcheck("starting combat for cpu");
            return -1;
          }*/
          int status;
          wait(&status);
          sleep(1);
          //kill(pidC, SIGKILL);
          kill(pidU, SIGKILL);
          if (!WIFEXITED(status)){
            printf("%d", WTERMSIG(status));
            printf("You flee the encounter.\n");
            // anything for fleeing here.
            sleep(1);
          }
          else if (WEXITSTATUS(status) == 1){
            printf("You win!\n");
            sleep(1);
            if (rand_double() < solve("L/250+0.2", 0, player.stats)){ // 20% loot chance + Luck/2.5 %
              int loot = 0;
              if (rand_double() < 0.3){ // 30% for skill
                loot = (int)(0.999999 + rand_double() * 10); // number of skills not including default.
                int j = 0;
                for (; j < sizeof(player.inventory.invI); j++){
                  if (player.inventory.invI[j] == -1) break;
                }
                if (j == sizeof(player.inventory.invI)){
                  printf("Your inventory is full.\n");
                }
                else{
                  player.inventory.invI[j] = loot;
                  iteminfo(&object, loot, player.stats);
                  printf("You looted a %s!\n", object.NAME);
                }
              }
              else{
                loot = (int)(2.999999 + rand_double() * 3); // number of equipment not including default.
                int j = 0;
                for (; j < sizeof(player.inventory.invS); j++){
                  if (player.inventory.invS[j] == -1) break;
                }
                if (j == sizeof(player.inventory.invS)){
                  printf("You know too many skills.\n");
                }
                else{
                  player.inventory.invS[j] = loot;
                  skillinfo(&move, loot, player.stats);
                  printf("You learned %s!\n", move.NAME);
                }
              }
            }
            else{
              printf("You do not find any loot.");
            }
          }
          else{
            // Anything for losing here.
          }
          sleep(2);
        }
        else{
          save(player);
          execlp("./combat", "./combat", player.NAME, coin, NULL);
          errcheck("starting combat for player");
          return -1;
        }
        unlink("CombatToCombat");
        semctl(sem, IPC_RMID, 0);
        errcheck("removing semaphore");
        break;
      case 6:
        //Networking & PvP






        break;
      case 7: //save
        save(player);
        printf("Progress saved!\n");
        sleep(1);
        break;
      case 8: // exit
        save(player);
        free(player.NAME);
        free(object.NAME);
        free(move.NAME);
        free(move.EXA);
        return 0;
      default: printf("ERROR IN GAME\n");
    }
    system("clear");
  }
  return 0;
}

int readInt(FILE * c){ // Up to four digits
  int x;
  char buf[5];
  fgets(buf, 5, c);
  *strchr(buf, '\n') = 0;
  sscanf(buf, "%d", &x);
  return x;
}

void iteminfo(struct item * object, int id, struct stats s){
  char buf[40];
  sprintf(buf, "%s%d", IPATH, id);
  FILE * f = fopen(buf, "r");
  object->ID = id;
  fgets(object->NAME, sizeof(object->NAME), f);
  sscanf(fgets(buf, sizeof(buf), f), "%c\n", &object->type);
  *strchr(fgets(buf, sizeof(buf), f), '\n') = 0;
  object->HIT = solve(buf, 0, s);
  *strchr(fgets(buf, sizeof(buf), f), '\n') = 0;
  object->DMG = solve(buf, 0, s);
  sscanf(fgets(buf, sizeof(buf), f), "%lf\n", &object->VAR);
  *strchr(fgets(buf, sizeof(buf), f), '\n') = 0;
  object->DMGRED = solve(buf, 0, s);
  *strchr(fgets(buf, sizeof(buf), f), '\n') = 0;
  object->DODGE = solve(buf, 0, s);
  fgets(buf, sizeof(buf), f);
  *strchr(buf, '\n') = 0;
  char ** args = parse_args(buf, ";");
  int i;
  for (i = 0; i < 5; i++) sscanf(args[i], "%d", &object->STAT[i]);
  free(args);
  fgets(buf, sizeof(buf), f);
  *strchr(buf, '\n') = 0;
  args = parse_args(buf, ";");
  for (i = 0; i < 5; i++) sscanf(args[i], "%d", &object->REQ[i]);
  free(args);
  fclose(f);
}
void save(struct character player){
  char buf[59];
  sprintf(buf, "%s%s", CPATH, player.NAME);
  FILE * f = fopen(buf, "w");
  fprintf(f, "%d\n", player.stats.STR);
  fprintf(f, "%d\n", player.stats.DEX);
  fprintf(f, "%d\n", player.stats.END);
  fprintf(f, "%d\n", player.stats.INT);
  fprintf(f, "%d\n", player.stats.LUK);
  fprintf(f, "%d\n", player.equipped.wep);
  fprintf(f, "%d\n", player.equipped.armor);
  fprintf(f, "%d\n", player.equipped.helm);
  int i = 1;
  fprintf(f, "%d", player.skills[0]);
  for (; i < sizeof(player.skills) / sizeof(int); i++) fprintf(f, ";%d", player.skills[i]);
  fprintf(f, "\n");
  fprintf(f, "%d", player.inventory.invI[0]);
  for (i = 1; i < sizeof(player.inventory.invI) / sizeof(int); i++) fprintf(f, ";%d", player.inventory.invI[i]);
  fprintf(f, "\n");
  fprintf(f, "%d", player.inventory.invS[0]);
  for (i = 1; i < sizeof(player.inventory.invS) / sizeof(int); i++) fprintf(f, ";%d", player.inventory.invS[i]);
  fprintf(f, "\n");
  fclose(f);
}
