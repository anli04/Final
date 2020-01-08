#include "rpg.h"

double rand_double(){
  return (double) rand() / (double) RAND_MAX;
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


char ** parse_args(char * line,char * s) {
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

double nextNum(char * f, int idx, struct character player){ // For use in solve, mainly.
  char num[10];
  num[0] = '0';
  num[1] = '\0';
  double n;
  while (f[idx]){
    if (strchr("0123456789.", f[idx])) strncat(num, &f[idx], 1);
    else if (strchr("S", f[idx])) return player.STR;
    else if (strchr("D", f[idx])) return player.DEX;
    else if (strchr("E", f[idx])) return player.END;
    else if (strchr("I", f[idx])) return player.INT;
    else if (strchr("L", f[idx])) return player.LUK;
    else{
      sscanf(num, "%lf", &n);
      return n;
    }
    idx++;
  }
  sscanf(num, "%lf", &n);
  return n;
}
double solve(char * f, int idx, struct character player){
  double ans = nextNum(f, idx, player);
  double n;
  char op = '\0';
  while (f[idx]){
    n = 0;
    op = '\0';
    if (idx == 0 && ans == 0) op = '+';
    char * p = strchr("+-*/^", f[idx]);
    if (p){
      op = *p;
      idx++;
    }
    switch(f[idx]){
      case 'l':
        n = log(solve(f, idx + 2, player));
        while (f[idx] != ')') idx++;
        break;
      case ')':
        return ans;
        break;
      case '(':
        idx++;
        n = solve(f, idx, player);
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
        n = nextNum(f, idx, player);
        break;
    }
    switch(op){
      case '+': ans += n; break;
      case '-': ans -= n; break;
      case '*': ans *= n; break;
      case '/': ans /= n; break;
      case '^': ans = pow(ans, n); break;
    }
    idx++;
  }
  return ans;
}
