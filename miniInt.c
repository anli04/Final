#include "rpg.h"





int wordGame() {
  system("clear");
  char * lines[256];
  FILE *f = fopen("synonyms","r");
  char buf[256];
  int i = 0;
  int score = 0;
  while(fgets(buf,256,f) != NULL) {
    lines[i] = malloc(sizeof(char)*256);
    buf[strlen(buf)-1] = '\0';
    strcpy(lines[i],buf);
    i++;
  }


  int r = 0;
  int r_w = 0;
  int r_w2 = 0;
  int s = 0;
  char ** line;
  while(strcmp(buf,"q\n") != 0) {
    system("clear");
    r = (int)rand()%i;
    line = parse_args(lines[r],";");
    s = size_array(lines[r]);
    r_w = (int)rand()%s;
    r_w2 = (int)rand()%s;
    while(r_w2 == r_w) {
      r_w2 = (int)rand()%s;
    }

    printf("\n------------------------------------------------------\n");
    printf("Welcome to Word Trial!");
    printf("\n------------------------------------------------------\n");
    printf("INSTRUCTIONS:\n");
    printf("Answer the prompt in lowercase letters. Type \'q\' to quit the game.\n\n");
    printf("Name a word that starts with '%c%c' and ends with '%c', and is synonymous with %s.\n",line[r_w2][0],line[r_w2][1],line[r_w2][strlen(line[r_w2])-1],line[r_w]);
    fgets(buf,256,stdin);

    if(strcmp(buf,"q\n") != 0) {
      system("clear");
      printf("\n------------------------------------------------------\n");
      printf("Welcome to Intelligence Trial!");
      printf("\n------------------------------------------------------\n");
      printf("INSTRUCTIONS:\n");
      printf("Answer the prompt in lowercase letters. Type \'q\' to quit the game.\n\n");
      printf("Name a word that starts with '%c%c' and ends with '%c', and is synonymous with %s.\n",line[r_w2][0],line[r_w2][1],line[r_w2][strlen(line[r_w2])-1],line[r_w]);
      buf[strlen(buf)-1] = '\0';
      printf("%s ",buf);
      if(strcmp(buf,line[r_w2]) == 0) {
        printf("✔\n");
        score++;
      }
      else {
        printf("✗\n");
        printf("The correct answer was: %s\n",line[r_w2]);
      }
    }

    sleep(1);

  }

  printf("Final Score: %d\n",score);
  return score;


}


int mathGame() {
  system("clear");
  int n = 0;
  int n2 = 0;
  int op = 0;
  int answer = 0;
  int score = 0;
  char buf[256];

  while(strcmp(buf,"q\n") != 0) {
    system("clear");
    n = (int)rand()%20;
    n2 = (int)rand()%10 + 1;
    answer = 0;
    op = (int)rand()%5;
    char temp[64];

    if(op == 0) {
      sprintf(temp,"%d + %d = ",n,n2);
      answer = n+n2;
    }
    else if(op == 1) {
      sprintf(temp,"%d - %d = ",n,n2);
      answer = n-n2;
    }
    else if(op == 2) {
      sprintf(temp,"%d x %d = ",n,n2);
      answer = n*n2;
    }
    else if(op == 3) {
      sprintf(temp,"%d / %d = ",n,n2);
      answer = n/n2;
    }
    else if(op == 4) {
      sprintf(temp,"%d ^ %d = ",n,n2);
      int a = 1;
      for(int i = 0;i<n2;i++){
        a*=n;
      }
      answer = a;
    }
    printf("\n------------------------------------------------------\n");
    printf("Welcome to Math Trial!");
    printf("\n------------------------------------------------------\n");
    printf("INSTRUCTIONS:\n");
    printf("Type in the correct answer to the problem and hit Enter to submit. Type \'q\' to quit.\n");
    printf("%s",temp);

    fgets(buf,256,stdin);
    if(strcmp(buf,"q\n") != 0) {
      char temp2[64];
      system("clear");
      buf[strlen(buf)-1] = '\0';
      printf("%s%s ",temp,buf);

      sprintf(temp2,"%d",answer);

      if(strcmp(buf,temp2) == 0) {
        printf("✔\n");
        score+=answer;
      }
      else {
        printf("✗\n");
        printf("The correct answer was: %d\n",answer);
      }



    }

    sleep(1);

  }

  printf("Final Score: %d\n",score);
  return score;


}
