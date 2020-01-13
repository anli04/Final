#include "rpg.h"

union semun {
  int              val;    /* Value for SETVAL */
  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
  unsigned short  *array;  /* Array for GETALL, SETALL */
  struct seminfo  *__buf;  /* Buffer for IPC_INFO
                              (Linux-specific) */
};

int readInt(FILE * c);
void iteminfo(struct item object, int id, struct stats s);
void save(struct character player);

int main(){
  srand(time(NULL));
  struct character player;
  player.NAME = malloc(sizeof(char) * 25);
  char * skillnames[sizeof(player.skills)];
  char * invInames[sizeof(player.inventory.invI)];
  char * invSnames[sizeof(player.inventory.invS)];
  struct item object;
  object.NAME = malloc(sizeof(char) * 25);
  struct skill move;
  move.NAME = malloc(sizeof(char) * 25);
  int input = 0;
  FILE * c;
  union semun su;
  su.val = 1;
  char choices[100]; // note that this number will inhibit inventory size
  printf("Welcome to [game name]!\n");
  printf("Make selections by typing the number corresponding to your choice.\n");
  printf("1) Create Character\n2) Select Character\n3) Delete Character\n");
  strcpy(choices, "1;2;3");
  input = choose(choices);
  switch (input){ // Character creation/selection/deletion
    case 1: // Create character file


      //add dirent stuff to move character to proper place


      printf("Enter a character name (max 24 alphanumerical characters):\n");
      char n[26];
      int x = 1;
      int fd;
      while (x){
        fgets(n, 26, stdin);
        *strchr(n, '\n') = 0;
        fd = open(n, O_WRONLY | O_CREAT | O_EXCL, 0644);
        if (errno){
          printf("Character already exists.\n");
          errno = 0;
        }
        else x = 0;
      }
      int i = 0;
      for (; i < 5; i++) write(fd, "1\n", strlen("1\n"));
      i = 0;
      for (; i < 3; i++) write(fd, "0\n", strlen("0\n"));
      write(fd, "0;-1;-1;-1;-1\n", strlen("0;-1;-1;-1;-1\n"));
      write(fd, "-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1\n", strlen("-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1\n"));
      write(fd, "-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1\n", strlen("-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1\n"));
      errcheck("creating character file defaults");
      close(fd);
      c = fopen(n, "r");
      errcheck("opening character file");
      strcpy(player.NAME, n);
      break;
    /*case 2: // Select character file
      printf("Select a character:\n");
      // Insert character select code. Selection 0 is back
      break;
    case 3: // Delete character file(s)
      printf("Select a character to delete:\n");
      // Insert character select code to delete. Selection 0 is back
      break;*/
    default: printf("Error");
      break;
  }
  printf("Loading character...\n"); // update character struct
  player.stats.STR = readInt(c);
  player.stats.DEX = readInt(c);
  player.stats.END = readInt(c);
  player.stats.INT = readInt(c);
  player.stats.LUK = readInt(c);
  player.equipped.wep = readInt(c);
  player.equipped.armor = readInt(c);
  player.equipped.helm = readInt(c);
  // Fix this


  printf("checkpoint2\n");
  fgets(player.skills, 1024, c);
  printf("checkpoint3\n");
  *strchr(player.skills, '\n') = 0;
  printf("checkpoint4\n");
  fgets(player.inventory.invI, 1024, c);
  printf("checkpoint5\n");
  *strchr(player.inventory.invI, '\n') = 0;
  printf("checkpoint6\n");
  fgets(player.inventory.invS, 1024, c);
  printf("checkpoint7\n");
  *strchr(player.inventory.invS, '\n') = 0;
  printf("checkpoint8\n");


  // set skillnames and itemnames



  fclose(c);

  while (1){
    printf("1) Character Info\n");
    printf("2) Training\n");
    printf("3) Inventory\n");
    printf("4) Skills\n");
    printf("5) Random Encounter\n");
    printf("6) PvP\n");
    printf("7) Save\n")
    printf("7) Exit Game\n");
    strcpy(choices, "1;2;3;4;5;6;7;8");
    input = choose(choices);
    switch (input){
      case 1: //Display character info
        printf("%s\n", player.NAME);
        printf("STR: %d\nDEX: %d\nEND: %d\nINT: %d\nLUK: %d\n", player.stats.STR, player.stats.DEX, player.stats.END, player.stats.INT, player.stats.LUK);
        printf("\nEquipment:\nWeapon: %s\nArmor: %s\nHelm: %s\n", player.equipped.wep, player.equipped.armor, player.equipped.helm);
        printf("\nSkills:\n");
        int j = 0;
        for (; j < sizeof(player.skills); j++){
          printf("%d. %s\n", j, skillnames[j]);
        }
        break;
      case 2: // Training
        // Training




        break;
      case 3: // Inventory (manage both)
        int index;
        // fd = fopen();
        // for (index = 0; x < )





        break;
      case 4: // select skills for use





        break;
      case 5:
        save(player);
        printf("Preparing for combat...\n");
        mkfifo("CombatToCombat", 0666);
        int sem;
        sem = semget(KEY, 1, IPC_CREAT | 0644);
        errcheck("creating semaphore");
        printf("Semaphore created\n");
        semctl(sem, 0, SETVAL, su);
        errcheck("setting semaphore");
        char coin;
        char coin2;
        if (rand_double() < 0.5){
          coin2 = '0';
          coin = '1';
        }
        else{
          coin = '0';
          coin2 = '1';
        }
        pid_t pidU = fork(); // player
        if (pidU > 0) { // main game process
          pid_t pidC = fork(); // cpu
          if (pidC <= 0){
            int enc = (int)(rand_double() * 2); //unweighted random encounters.
            char encs[50];
            sprintf(encs, "%s%d", EPATH, enc);
            int fenc = fopen(encs, "r");
            fgets(encs, sizeof(encs), fenc);
            fclose(fenc);
            printf("You encounter a %s!\n", encs);
            execlp("combat", "combat", enc, coin2, 1);
            errcheck("starting combat for cpu");
            return -1;
          }
          int status;
          wait(&status);
          sleep(1);
          if (!WIFEXITED(status)){
            kill(pidC, SIGKILL);
            printf("You flee the encounter.\n");
            // anything for fleeing here.
            sleep(1);
          }
          else if (WEXITSTATUS(status) == 1){
            printf("You win!\n");
            sleep(1);
            if (rand_double() < solve("L/250+0.2", 0, player.stats){ // 20% loot chance + Luck/2.5 %
              int loot = 0;
              if (rand_double() < 0.3){ // 30% for skill
                loot = (int)(0.999999 + rand_double() * 10); // number of skills not including default.
                int j = 0;
                for (; j < sizeof(inventory.invI); j++){
                  if (inventory.invI[j] == -1) break;
                }
                if (j == sizeof(inventory.invI)){
                  printf("Your inventory is full.\n");
                }
                else{
                  inventory.invI[j] = loot;
                  iteminfo(object, loot, player.stats);
                  printf("You looted a %s!\n", object.NAME);
                }
              }
              else{
                loot = (int)(2.999999 + rand_double() * 3); // number of equipment not including default.
                int j = 0;
                for (; j < sizeof(inventory.invS); j++){
                  if (inventory.invS[j] == -1) break;
                }
                if (j == sizeof(inventory.invS)){
                  printf("You know too many skills.\n");
                }
                else{
                  inventory.invS[j] = loot;
                  skillinfo(move, loot, player.stats);
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
          sleep(1);
        }
        else{
          execlp("combat", "combat", player.NAME, coin);
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
      case 8: // exit
        save(player);
        free(player.NAME);
        free(object.NAME);
        free(move.NAME);
        return 0;
      default: printf("ERROR IN GAME\n");
    }
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

void iteminfo(struct item object, int id, struct stats s){
  char buf[32];
  sprintf(buf, "%d", id);

  // Do the dirent Stuff

  FILE * f = fopen(buf, "r");
  object.ID = id;
  fgets(object.NAME, sizeof(object.NAME), f);
  sscanf(fgets(buf, sizeof(buf), f), "%d\n", object.type);
  *strchr(fgets(buf, sizeof(buf), f), '\n') = 0;
  object.HIT = solve(buf, 0, s);
  *strchr(fgets(buf, sizeof(buf), f), '\n') = 0;
  object.DMG = solve(buf, 0, s);
  sscanf(fgets(buf, sizeof(buf), f), "%lf\n", object.VAR);
  *strchr(fgets(buf, sizeof(buf), f), '\n') = 0;
  object.DMGRED = solve(buf, 0, s);
  *strchr(fgets(buf, sizeof(buf), f), '\n') = 0;
  object.DODGE = solve(buf, 0, s);
  char * token;

  int l[5];
  // Do this parsing.
  int count = 0;
  fgets(buf, sizeof(buf), f);
  char * rest = buf;
  while (token = strtok_r(rest, ";", &rest)) {
      int len = strlen(token);
      if(token[len-1] == '\n') token[len-1] = 0;
      sscanf(token, "%d", &l[count]);
      count++;
  }
  object.STAT = l;
  // int i;
  // for (i = 0; i < 5; i++) {
  //     printf("%d\n", object.STAT[i]);
  // }
  count = 0;
  fgets(buf, sizeof(buf), f);
  rest = buf;
  while (token = strtok_r(rest, ";", &rest)) {
      int len = strlen(token);
      if(token[len-1] == '\n') token[len-1] = 0;
      sscanf(token, "%d", &l[count]);
      count++;
  }
  object.REQ = l;
  // for (i = 0; i < 5; i++) {
  //     printf("%d\n", object.REQ[i]);
  // }
  fclose(f);
}
void save(struct character player){
  FILE * f = fopen(player.NAME, "w");
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
  for (; i < sizeof(player.skills); i++) fprintf(f, ";%d", player.skills[i]);
  fprintf(f, "\n");
  fprintf(f, "%d", player.inventory.invI[0]);
  for (i = 1; i < sizeof(player.inventory.invI); i++) fprintf(f, ";%d", player.inventory.invI[i]);
  fprintf(f, "\n");
  fprintf(f, "%d", player.inventory.invS[0]);
  for (i = 1; i < sizeof(player.inventory.invS); i++) fprintf(f, ";%d", player.inventory.invS[i]);
  fprintf(f, "\n");
  fclose(f);
}
