#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SIZE (10000 + 1) * 6

int *to_array(char *str, int *n){
  *n = atoi( strsep(&str, "\n") );
  int *arr = calloc(*n, sizeof(int));

  for (int j = 0; j < *n; j ++){
    arr[j] = atoi( strsep(&str, "\n") );
  }
  return arr;
}

int get_avg(int *arr, int n){
  int sum = 0;
  for (int i = 0; i < n; i ++){
    sum += arr[i];
  }
  return sum / n;
}

void to_resid(int *arr, int n, int avg){
  for (int j = 0; j < n; j ++){
    arr[j] -= avg;
  }
}

int count_moves(int *arr, int n, int avg){
  int ctr = 0;
  to_resid(arr, n, avg);
  int closest;
  for (int i = 0; i < n; i ++){
    if (arr[i] > 0){
      for (int j = 0; j < n; j ++){
        if (!arr[i])
          break;
        if (arr[j] < 0){
          if (arr[i] + arr[j] > 0){
            ctr -= arr[j];
            arr[i] += arr[j];
            arr[j] = 0;
          }
          else {
            ctr += arr[i];
            arr[j] += arr[i];
            arr[i] = 0;
          }
        }
      }
    }

  }
  return ctr;
}

int main(){

  int in = open("haybales.in", O_RDONLY);
  char *str = malloc( SIZE );
  read(in, str, SIZE);
  close(in);
  int n;
  int *arr = to_array(str, &n);

  int avg = get_avg(arr, n);

  int ctr = count_moves(arr, n, avg);
  // printf("%d\n", ctr);
  // for (int i = 0; i < n; i ++)
  //   printf("%d\n", arr[i]);
  int out = open("haybales.out", O_CREAT | O_WRONLY, 0644);
  char num[SIZE];
  sprintf(num, "%d\n", ctr);
  write(out, num, strlen(num));
  close(out);

  return 0;
}
