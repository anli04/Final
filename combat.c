#include "rpg.h"

#define KEY 2473842

int main(){
  int victory = 0;
  int sem;
  sem = semget(KEY, 1, 0);
  errcheck("getting semaphore");
  struct sembuf sb;
  sb.sem_num = 0;
  // Pipe over a struct character OR take in as argument




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
