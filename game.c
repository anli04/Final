#include "rpg.h"

int readInt(FILE * c);
void iteminfo(struct item object, int id);

int main(){
  srand(time(NULL));
  struct character player;
  player.NAME = malloc(sizeof(char) * 25);
  struct item object;
  object.NAME = malloc(sizeof(char) * 25);
  int input = 0;
  FILE * c;
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
        fd = optem.NAME;en(n, O_WRONLY | O_CREAT | O_EXCL, 0644);
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

  // Fix this



  /*player.stats.STR = readInt(c);
  player.stats.DEX = readInt(c);
  player.stats.END = readInt(c);
  player.stats.INT = readInt(c);
  player.stats.LUK = readInt(c);
  player.equipped.wep = readInt(c);
  player.equipped.armor = readInt(c);
  player.equipped.helm = readInt(c);
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
  fclose(c);*/

  while (1){
    printf("1) Character Info\n");
    printf("2) Training\n");
    printf("3) Inventory\n");
    printf("4) Skills\n");
    printf("5) Random Encounter\n");
    printf("6) PvP\n");
    printf("7) Exit Game\n");
    strcpy(choices, "1;2;3;4;5;6;7");
    input = choose(choices);
    switch (input){
      case 1: //Display character info
        printf("%s\n", player.NAME);
        printf("STR: %d\nDEX: %d\nEND: %d\nINT: %d\nLUK: %d\n", player.stats.STR, player.stats.DEX, player.stats.END, player.stats.INT, player.stats.LUK);
        printf("\nEquipment:\nWeapon: %s\nArmor: %s\nHelm: %s\n", player.equipped.wep, player.equipped.armor, player.equipped.helm);
        // more cases



      case 5:
        printf("")
        int f =




      // more cases


      case 7: // exit
        // Be sure to have the sighandler stuff somewhere for saving


        return 0;
      default: printf("Error");
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

void iteminfo(struct item object, int id, struct character player){
  char buf[32];
  sprintf(buf, "%d", id);
  FILE * f = fopen(buf, "r");
  object.ID = id;
  fgets(buf, sizeof(buf), f);
  sscanf(buf, "%d", object.type);
  fgets(item.NAME, sizeof(item.NAME), f);
  fgets(buf, sizeof(buf), f);
  double HIT = solve(buf, 0, player.stats);
  fgets(buf, sizeof(buf), f);
  double DMG = solve(buf, 0, player.stats);
  double VAR; // damage variance or modifier
  double DMGRED; // damage reduction. e.g. 0.1 = reduce by 10% (additive)
  double DODGE; // dodge chance (additive)
  int * STAT; // stat adjustments
  int * REQ; // stat requirement to equip
  fclose(f);
}
