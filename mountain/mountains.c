#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SIZE 999999

int **to_array(char *str, int *n){
  *n = atoi( strsep(&str, "\n") );
  int **arr = calloc(*n, sizeof(int *));
  char *piece;
  int i, j;
  for (i = 0; i < *n; i ++){
    arr[i] = calloc(2, sizeof(int));
    piece = strsep(&str, "\n");
    arr[i][0] = atoi(strsep(&piece, " "));
    arr[i][1] = atoi(piece);
  }
  return arr;
}

int obscured(int **arr, int i, int j){
  return arr[i][1] - arr[j][1] >= abs(arr[i][0] - arr[j][0]);
}

int calculate(int **arr, int n){
  int i, j;
  int *gone = calloc(n, sizeof(int));
  for (i = 0; i < n; i ++){
    for (j = 0; j < n; j ++){
      if (i != j && obscured(arr, i, j) && !gone[j])
        gone[j] = 1;
    }
  }
  int total = 0;
  for (i = 0; i < n; i ++)
    total += !gone[i];
  return total;
}

int main(){

  int in = open("mountains.in", O_RDONLY);
  char *str = malloc( SIZE );
  read(in, str, SIZE);
  close(in);
  int n;
  int **arr = to_array(str, &n);

  int max = calculate(arr, n);

  int out = open("mountains.out", O_CREAT | O_WRONLY, 0644);
  char num[SIZE];
  sprintf(num, "%d\n", max);
  write(out, num, strlen(num));
    // return 1;
  close(out);

  return 0;
}
