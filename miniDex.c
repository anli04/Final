#include "rpg.h"


int typeracer() {
    enum { MAXL = 100000, MAXC = 50 };
    char (*lines)[MAXC] = NULL; /* pointer to array of type char [MAXC] */
    int i, x, n = 0, score = 0, count = 0;
    FILE *fd = fopen("/usr/share/dict/words", "r");
    if (!fd) {  /* valdiate file open for reading */
        fprintf (stderr, "error: file open failed '%s'.\n", "words");
        return 1;
    }
    if (!(lines = malloc (MAXL * sizeof *lines))) { /* allocate MAXL arrays */
        fprintf (stderr, "error: virtual memory exhausted 'lines'.decimal to 2 places\n");
        return 1;
    }
    while (n < MAXL && fgets (lines[n], MAXC, fd)) { /* read each line */
        char *p = lines[n];                  /* assign pointer */
        for (; *p && *p != '\n'; p++) {}     /* find 1st '\n'  */
        *p = 0, n++;                         /* nul-termiante  */
    }
    fclose(fd);   /* close file if not stdin */
    /* print lines */
    // for (i = 0; i < n; i++) printf (" line[%2d] : '%s'\n", i + 1, lines[i]);
    char rSamp[60][50];
    for (x = 0; x < 60; x++) {
      strcpy(rSamp[x], lines[rand() % 99154]);
    }
    printf("\n------------------------------------------------------\n");
    printf("Welcome to Type Trial!");
    printf("\n------------------------------------------------------\n");
    printf("INSTRUCTIONS:\n");
    printf("Type the sample of 60 words asmain fast and as accurately as you can exactly as you see them.\n");
    printf("Separate your words with a space and hit ENTER only when you are finished.\n\n");
    printf("Press ENTER to start...\n");
    fflush(stdout);
    char detect[1000];
    fgets(detect, sizeof(detect), stdin);
    time_t start = time(NULL);
    printf("\n------------------------------------------------------\n");
    printf("SAMPLE");
    printf("\n------------------------------------------------------\n");
    for (x = 0; x < 60; x++) {
      printf("%s ", rSamp[x]);
    }
    printf("\n------------------------------------------------------\n\n");
    fflush(stdout);
    char buf[1000];
    fgets(buf, sizeof(buf), stdin);
    time_t end = time(NULL);
    double d = difftime(end, start);
    printf("\n------------------------------------------------------\n");
    printf("RESULTS");
    printf("\n------------------------------------------------------\n\n");
    printf("Time Taken: %f seconds\n", d);
    char (*l)[MAXC] = NULL;
    if (!(l = malloc (MAXL * sizeof *l))) { /* allocate MAXL arrays */
        fprintf (stderr, "error: virtual memory exhausted 'lines'.\n");
        return 1;
    }
    char * token;
    char * rest = buf;
    while (token = strtok_r(rest, " ", &rest)) {
      int len = strlen(token);
      if(token[len-1] == '\n') token[len-1] = 0;
      strcpy(l[count], token);
      count++;
    }
    // for (x = 0; x < 60; x++) {
    //   printf("%s l\n", l[x]);
    // }
    for (x = 0; x < 60; x++) {
      if (strcmp(rSamp[x], l[x]) == 0) score++;
    }
    printf("Score: %d/60\n", score);
    int wpm = score * 60 / d;
    printf("Speed: %d WPM\n", wpm);

    sleep(3);
    free (lines);
    free(l);   /* free allocated memory */
    return score;
}


int numbers() {
  system("clear");
  printf("\n------------------------------------------------------\n");
  printf("Welcome to Type Trial - Numbers!");
  printf("\n------------------------------------------------------\n");
  printf("INSTRUCTIONS:\n");
  printf("Type the sample of numbers as fast and as accurately as you can exactly as you see them.\n");
  printf("Hit ENTER to check each number. Type \'q\' when you are finished.\n\n");
  printf("Press ENTER to start...\n");
  fflush(stdout);
  char detect[1000];
  fgets(detect, sizeof(detect), stdin);
  int score = 0;
  int r = 0;
  char n[16];
  char * d;
  char full[16];
  char input[16];
  char history[4096];
  d = malloc(sizeof(char)*16);
  while(strcmp(input,"q\n") != 0) {
    r = rand()%10000000;
    sprintf(n,"%d",r);
    *(n+strlen(n)-2) = '\0';

    sprintf(d,"%d",r);
    d += strlen(d)-2;

    strcpy(full,n);
    strcat(full,".");
    strcat(full,d);

    printf("%s\t\t",full);
    if(strlen(full)<8) {
      printf("\t");
    }

    fgets(input,16,stdin);

    strcat(history,full);
    strcat(history,"\t\t");
    if(strlen(full)<8) {
      strcat(history,"\t");
    }
    strcat(history,input);
    history[strlen(history)-1] = '\0';

    if(strcmp(input,"q\n") != 0) {
      if(strcmp(input,full) == 10) {
        score += 1;
        strcat(history," ✔");
      }
      else {
        strcat(history," ✗");
      }
    }

    strcat(history,"\n");
    system("clear");
    printf("\n------------------------------------------------------\n");
    printf("Welcome to Type Trial - Numbers!");
    printf("\n------------------------------------------------------\n");
    printf("INSTRUCTIONS:\n");
    printf("Type the sample of numbers as fast and as accurately as you can exactly as you see them.\n");
    printf("%s",history);



  }

  printf("\nFinal Score: %d\n",score);
  sleep(3);
  return score;





}
