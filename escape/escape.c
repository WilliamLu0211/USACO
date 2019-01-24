#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SIZE 210

int *to_digits(int x){
  int *arr = calloc(9, sizeof(int));
  int i = 0;
  while (x){
    arr[i] = x % 10;
    x /= 10;
    i ++;
  }
  return arr;
}

int **to_array(char *str, int *n){
  *n = atoi( strsep(&str, "\n") );
  int **arr = calloc(*n, sizeof(int *));

  for (int j = 0; j < *n; j ++){
    arr[j] = to_digits( atoi( strsep(&str, "\n") ) );
  }
  return arr;
}

int can_add(int **arr, int *sum, int n, int ctr, int start){
  if (!ctr)
    return 1;
  int proceed;
  for (int i = start; i < n; i ++){
    proceed = 1;
    for (int j = 0; j < 9; j ++){
      sum[j] += arr[i][j];
      if (sum[j] >= 10){
        for (int k = 0; k <= j; k ++){
          sum[k] -= arr[i][k];
        }
        proceed = 0;
        break;
      }
    }
    if (proceed && can_add(arr, sum, n, ctr - 1, i + 1))
      return 1;
    if (proceed)
      for (int k = 0; k < 9; k ++){
        sum[k] -= arr[i][k];
      }
  }
  return 0;
}

int fits(int **arr, int n, int max){
  int *sum = calloc(9, sizeof(int));
  return can_add(arr, sum, n, max, 0);
}

int max_count(int **arr, int n){
  int max = 1;
  for (int i = 2; i <= n; i ++){
    if (fits(arr, n, i))
      max = i;
  }
  return max;
}

int main(){

  int in = open("escape.in", O_RDONLY);
  char *str = malloc( SIZE );
  read(in, str, SIZE);
  close(in);
  int n;
  int **arr = to_array(str, &n);

  for (int i = 0; i < n; i ++){
    for (int j = 0; j < 9; j ++)
      printf("[%d]", arr[i][j]);
    printf("\n");
  }

  int max = max_count(arr, n);
  // printf("%d\n", ctr);
  // for (int i = 0; i < n; i ++)
  //   printf("%d\n", arr[i]);
  int out = open("escape.out", O_CREAT | O_WRONLY, 0644);
  char num[SIZE];
  sprintf(num, "%d\n", max);
  write(out, num, strlen(num));
  close(out);

  return 0;
}
