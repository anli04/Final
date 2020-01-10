#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


enum { MAXL = 100000, MAXC = 50 };
int typeracer() {
    srand(time(NULL));
    char (*lines)[MAXC] = NULL; /* pointer to array of type char [MAXC] */
    int i, x, n = 0, score = 0, count = 0;
    FILE *fd = fopen("words", "r");
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
    printf("\n---------------------------main---------------------------\n");
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
    printf("Speed: %d WPM", wpm);
    free (lines);
    free(l);   /* free allocated memory */
    return 0;
}


int numbers() {
  int r = 0;
  float d = 0;
  while(1) {
    r = rand()%10000000;
    d = ((float)r)/100;
    printf("%f ",d);




  }





}



int main() {
  srand(time(NULL));
  numbers();
}
