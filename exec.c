#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

static void sig_childactive(int sig) {
  if(sig == SIGINT || sig == SIGTSTP)
    return;
}
int main() {
  while(1) {
    printf("? ");
    char command[256];
    fgets(command, 256, stdin);
    char *after = command;
    char *words[128];
    int i = 0;
    while (i < 128) {
      words[i] = 0;
      i++;
    }
    i = 0;
    while (after) {
      //    printf("After: %s, ", after);
      words[i] = strsep(&after, " \n\t");
      //    printf("words[i]: %s\n", words[i]);
      i++;
    }
    words[i - 1] = 0;  // removing empty string at the end
    if(!fork()) 
      return execvp(words[0], words);
    else {
      
      int *i = (int *)malloc(sizeof(int));
      signal(SIGINT, sig_childactive);
      signal(SIGTSTP, sig_childactive);
      wait(i);
      signal(SIGINT, SIG_DFL);
      signal(SIGTSTP, SIG_DFL);
    }
  }
}
