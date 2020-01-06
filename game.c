#include "rpg.h"

int main(){
  srand(time(NULL));
  struct character player;
  int input = 0;
  FILE * c;
  char choices[100]; // note that this number will inhibit inventory size
  printf("Welcome to [game name]\n");
  printf("Make selections by typing the number corresponding to your choice\n");
  printf("1) Create Character\n2) Select Character\n3)Delete Character\n");
  strcpy(choices, "1;2;3");
  input = choose(choices);
  switch (input){ // Character creation/selection/deletion
    case 1: // Create character file
      printf("Enter a character name (max 24 alphanumerical characters):\n")
      char n[26];
      int x = 1;
      int fd;
      while (x){
        fgets(n, 26, stdin);
        *strchr(n, '\n') = 0;
        fd = open(n, O_CREAT | O_EXCL, 0644);
        if (errno) printf("Character already exists\n");
        else x = 0;
      }
      char buf[1024];
      int i = 0;
      for (; i < 5, i++){
        strcpy(buf, "1\n");
        write(fd, buf, strlen(buf));
      }
      int i = 0;
      for (; i < 3, i++){
        strcpy(buf, "0\n");
        write(fd, buf, strlen(buf));
      }
      strcpy(buf, "0;-1;-1;-1;-1\n");
      write(fd, buf, strlen(buf));
      strcpy(buf, "-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1\n");
      write(fd, buf, strlen(buf));
      strcpy(buf, "-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1;-1\n");
      write(fd, buf, strlen(buf));
      close(fd);
      c = fopen(n, "w");
      break;
    case 2: // Select character file
      printf("Select a character:\n");
      /* Insert character select code. Selection 0 is back




      */
      break;
    case 3: // Delete character file(s)
      printf("Select a character to delete:\n");
      /* Insert character select code to delete. Selection 0 is back




      */
      break;
    default:
      printf("Error");
  }
  printf("Loading character...");
  //Insert char struct update stuff by reading from FILE * c


  while (1){
    printf("");
    strcpy(choices, "1;2;3;4;5;6;7");
    input = choose(choices);
    switch (input){
      case 1: //Character info
      /* more cases



      */
      case 7: // exit
        // Be sure to have the sighandler stuff somewhere for saving

        fclose(c);
        return 0;
      default: printf("Error");
    }
  }
  return 0;
}
