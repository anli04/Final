#include "rpg.h"

#define KEY 2473842

int main(int argc, char *argv[]){
  int victory = 0; // win or lose. 1 or 0
  int sem;
  sem = semget(KEY, 1, 0);
  errcheck("getting semaphore");
  struct sembuf sb;
  sb.sem_num = 0;
  // Pipe over a struct character OR take in as argument
  struct turn t;
  mkfifo("CombatToCombat", 0666);
  char in[500];
  char out[500];
  char arr[10][50];
  int fd;
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
