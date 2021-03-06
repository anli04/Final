#include "rpg.h"

double rand_double(){ // returns a double between 0 and 1
  return (double) rand() / (double) RAND_MAX;
}

double min(double n, double m){
  if (n < m) return n;
  return m;
}

double max(double n, double m){
  if (n > m) return n;
  return m;
}

void errcheck(char * m){
  if (errno){
    printf("Error %s: %d - %s\n", m, errno, strerror(errno));
    errno = 0;
  }
}

int choose(char * choices){
  char input[5]; // should be over the maximum chars needed to check for extra characters
  char * args[26]; //note max inv space will be this num - 1
  int i = 0;
  while (choices){
    args[i] = strsep(&choices, ";");
    i++;
  }
  args[i] = NULL;
  while (1){
    i = 0;
    fgets(input, 5, stdin);
    errcheck("with input");
    input[4] = 0;
    if (strchr(input, '\n')) *strchr(input, '\n') = 0;
    while(args[i]){
      if (!strcmp(input, args[i])){
        int ans = 0;
        sscanf(args[i], "%d", &ans);
        return ans;
      }
      i++;
    }
    printf("Selection not recognized\n");
  }
  printf("ERROR\n");
  return -1;
}


char ** parse_args(char * line, char * s) {
    char * copy = strdup(line);
    char ** args = malloc(sizeof(char)*1024);
    int i = 0;
    char * iter;
    while((iter = strsep(&copy,s)) != NULL) {
        args[i] = malloc(sizeof(char)*32);
        strcpy(args[i],iter);
        i++;
    }
    return args;
}

int size_array(char * line) {
  int i = 0;
  int occ = 0;
  while(line[i] != '\0') {
    if(line[i] == ';') {
      occ++;
    }
    i++;
  }
  return occ;
}

double nextNum(char * f, int idx, struct stats s){ // For use in solve, mainly.
  char num[20];
  num[0] = '\0';
  double n;
  while (f[idx]){
    if (strchr("0123456789.-", f[idx])) strncat(num, &f[idx], 1);
    else if (strchr("S", f[idx])) return s.STR;
    else if (strchr("D", f[idx])) return s.DEX;
    else if (strchr("E", f[idx])) return s.END;
    else if (strchr("I", f[idx])) return s.INT;
    else if (strchr("L", f[idx])) return s.LUK;
    else{
      if (num[0] == '\0') strcpy(num, "0");
      sscanf(num, "%lf", &n);
      return n;
    }
    idx++;
  }
  if (num[0] == '\0') strcpy(num, "0");
  sscanf(num, "%lf", &n);
  return n;
}
double solve(char * f, int idx, struct stats s){
  double ans = nextNum(f, idx, s);
  double n;
  char op = '\0';
  while (f[idx]){
    n = 0;
    op = '\0';
    if (ans == 0) op = '+';
    char * p = strchr("+_*/^", f[idx]);
    if (p){
      op = *p;
      idx++;
    }
    switch(f[idx]){
      case 'l':
        n = log(solve(f, idx + 2, s));
        while (f[idx] != ')') idx++;
        break;
      case 's':
        n = sin(solve(f, idx + 2, s));
        while (f[idx] != ')') idx++;
        break;
      case ')':
        return ans;
        break;
      case '(':
        idx++;
        n = solve(f, idx, s);
        int counter = 1;
        while (counter > 0){
          switch (f[idx]){
            case '(': counter++; break;
            case ')': counter--; break;
          }
          idx++;
        }
        idx--;
        break;
      default:
        n = nextNum(f, idx, s);
        break;
    }
    switch(op){
      case '+': ans += n; break;
      case '_': ans -= n; break;
      case '*': ans *= n; break;
      case '/': ans /= n; break;
      case '^': ans = pow(ans, n); break;
    }
    idx++;
  }
  return ans;
}

void skillinfo(struct skill * move, int id, struct stats s){
  char buf[128];
  sprintf(buf, "%s%d", SPATH, id);
  FILE * f = fopen(buf, "r");
  move->ID = id;
  *strchr(fgets(buf, sizeof(buf), f), '\n') = 0;
  strcpy(move->NAME, buf);
  *strchr(fgets(buf, sizeof(buf), f), '\n') = 0;
  move->HITMOD = solve(buf, 0, s);
  *strchr(fgets(buf, sizeof(buf), f), '\n') = 0;
  move->DMGMOD = solve(buf, 0, s);
  sscanf(fgets(buf, sizeof(buf), f), "%lf\n", &move->VARMOD);
  *strchr(fgets(buf, sizeof(buf), f), '\n') = 0;
  move->HITBUFF = solve(buf, 0, s);
  *strchr(fgets(buf, sizeof(buf), f), '\n') = 0;
  move->DMGBUFF = solve(buf, 0, s);
  *strchr(fgets(buf, sizeof(buf), f), '\n') = 0;
  move->REDPLUS = solve(buf, 0, s);
  *strchr(fgets(buf, sizeof(buf), f), '\n') = 0;
  move->DODGEPLUS = solve(buf, 0, s);
  sscanf(fgets(buf, sizeof(buf), f), "%d\n", &move->TURNS);
  sscanf(fgets(buf, sizeof(buf), f), "%d\n", &move->CD);
  *strchr(fgets(buf, sizeof(buf), f), '\n') = 0;
  strcpy(move->EXA, buf);
  fclose(f);
}
