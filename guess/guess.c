#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SIZE 9999999

struct animal{
  char *name;
  int num_chars;
  char **chars;
};

struct animal **to_array(char *str, int *n){
  *n = atoi( strsep(&str, "\n") );
  struct animal **arr = calloc(*n, sizeof(struct animal *));
  char *line;
  int i, j;
  for (i = 0; i < *n; i ++){
    arr[i] = malloc(sizeof(struct animal));
    line = strsep(&str, "\n");
    arr[i]->name = strsep(&line, " ");
    arr[i]->num_chars = atoi( strsep(&line, " ") );
    arr[i]->chars = calloc(arr[i]->num_chars, sizeof(char *));
    for (j = 0; j < arr[i]->num_chars; j ++){
      arr[i]->chars[j] = strsep(&line, " ");
    }
  }
  return arr;
}

void update(struct animal **arr, int n, char *piece, int *sim){
  // int exists;
  int i, j;
  for (i = 0; i < n; i ++){
    // exists = 0;
    for (j = 0; j < arr[i]->num_chars; j ++){
      if (!strcmp(arr[i]->chars[j], piece)){
        sim[i] ++;
        break;
      }
    }
  }
}

int max_sim(int *sim, int n, int target){
  int max = 0;
  int i;
  for (i = 0; i < n; i ++){
    if (i != target && sim[i] > max)
      max = sim[i];
  }
  return max;
}

int max_yes(struct animal **arr, int n){
  int max = 0;
  int ctr;
  int *sim;
  int i, j;
  for (i = 0; i < n; i ++){
    // ctr = 0;
    sim = calloc(n, sizeof(int));
    for (j = 0; j < arr[i]->num_chars; j ++){
      update(arr, n, arr[i]->chars[j], sim);
      // ctr ++;
    }
    ctr = max_sim(sim, n, i) + 1;
    if (ctr > max)
      max = ctr;
    free(sim);
  }
  return max;
}

int main(){

  int in = open("guess.in", O_RDONLY);
  char *str = malloc( SIZE );
  if (read(in, str, SIZE) == -1)
    return 1;
  close(in);
  int n;
  struct animal **arr = to_array(str, &n);

  int max = max_yes(arr, n);
  // printf("%d\n", max);
  int out = open("guess.out", O_CREAT | O_WRONLY, 0644);
  char num[256];
  sprintf(num, "%d\n", max);
  write(out, num, strlen(num));
    // return 1;
  close(out);

  return 0;
}
