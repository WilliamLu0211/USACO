#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SIZE 1024

int **to_array(char *str, int *n){
  *n = atoi( strsep(&str, "\n") );
  int **arr = calloc(*n, sizeof(int *));
  char *piece;
  int i, j;
  for (i = 0; i < *n; i ++){
    arr[i] = calloc(3, sizeof(int));
    piece = strsep(&str, "\n");
    for (j = 0; j < 3; j ++){
      arr[i][j] = atoi( strsep(&piece, " ") );
    }
  }
  return arr;
}

void swap(int *shells, int a, int b){
  int temp = shells[a];
  shells[a] = shells[b];
  shells[b] = temp;
}

int get_max(int **arr, int n){
  int *shells;
  int max = 0;
  int ctr, start, i;
  for (start = 0; start < 3; start ++){
    ctr = 0;
    shells = calloc(3, sizeof(int));
    shells[start] = 1;
    for (i = 0; i < n; i ++){
      swap(shells, arr[i][0] - 1, arr[i][1] - 1);
      if (shells[arr[i][2] - 1])
        ctr ++;
    }
    if (ctr > max)
      max = ctr;
  }
  return max;
}

int main(){

  int in = open("shell.in", O_RDONLY);
  char *str = malloc( SIZE );
  if (read(in, str, SIZE) == -1)
    return 1;
  close(in);

  int n;
  int **arr = to_array(str, &n);

  int max = get_max(arr, n);
  // printf("%d\n", ctr);
  // for (int i = 0; i < n; i ++)
  //   printf("%d\n", arr[i]);
  int out = open("shell.out", O_CREAT | O_WRONLY, 0644);
  char num[SIZE];
  sprintf(num, "%d\n", max);
  if (write(out, num, strlen(num)) == -1)
    return 1;
  close(out);

  return 0;
}
