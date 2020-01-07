#include "rpg.h"

int readInt(FILE * c);
void readArray(FILE * c, char *** copy);

int main(){
  srand(time(NULL));
  struct character player;
  int input = 0;
  char buf[1024]; // for string and file stuff
  int temp; // for random int needs
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
      c = fopen(n, "w");
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
  printf("Loading character..."); // update character struct
  fgets(buf, 26, c);
  *strchr(buf, '\n') = 0;
  strcpy(player.NAME, buf);
  player.STR = readInt(c);
  player.DEX = readInt(c);
  player.END = readInt(c);
  player.INT = readInt(c);
  player.LUK = readInt(c);
  player.wep = readInt(c);
  player.armor = readInt(c);
  player.helm = readInt(c);
  readArray(c, &player.skills);
  readArray(c, &player.invI);
  readArray(c, &player.invS);
  /*while (1){
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
      // more cases







      case 7: // exit
        // Be sure to have the sighandler stuff somewhere for saving

        fclose(c);
        return 0;
      default: printf("Error");
    }
  }*/
  printf("%s, %d %d %d %d %d, %d %d %d\n", player.NAME, player.STR, player.DEX, player.END, player.INT, player.LUK, player.wep, player.armor, player.helm);
  int test = 0;
  for (; test < 5; test++) printf("%s\n", player.skills[test]);
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

void readArray(FILE * c, char *** copy){ // Up to four digits, 15 items
  char buf[70];
  fgets(buf, 70, c);
  *strchr(buf, '\n') = 0;
  char * temp = buf;
  int i = 0;
  while (buf){
    *copy[i] = strsep(&temp, ";");
    i++;
  }
}
