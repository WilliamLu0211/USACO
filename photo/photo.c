#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SIZE 2 * (20000 * 5 + 1)

int **to_array(char *str, int *n){
  *n = atoi( strsep(&str, "\n") );
  int **arr = calloc(5, sizeof(int *));

  for (int i = 0; i < 5; i ++){
    arr[i] = calloc(*n, sizeof(int));
    for (int j = 0; j < *n; j ++){
      arr[i][j] = atoi( strsep(&str, "\n") );
    }
  }
  return arr;
}

void move(int *arr, int start, int end){
  int temp = arr[start];
  if (start > end){
    for (int i = start; i > end; i --){
      arr[i] = arr[i - 1];
    }
  }
  else {
    for (int i = start; i < end; i ++){
      arr[i] = arr[i + 1];
    }
  }
  arr[end] = temp;
}

int equals(int *a0, int *a1, int n){
  for (int i = 0; i < n; i ++){
    if (a0[i] != a1[i])
      return 0;
  }
  return 1;
}

int check_result(int **arr, int n, int r){

  for (int i = 0; i < n; i ++){
    for (int j = 0; j < n; j ++){
      move(arr[r], i, j);
      if (!r){
        if (check_result(arr, n, r + 1))
          return 1;
      }
      else if (r == 4) {
        if (equals(arr[r], arr[r - 1], n))
          return 1;
      }
      else {
        if (equals(arr[r], arr[r - 1], n) && check_result(arr, n, r + 1))
          return 1;
      }
      move(arr[r], j, i);
    }
  }
  return 0;
}

int main(){

  int in = open("photo.in", O_RDONLY);
  char *str = malloc( SIZE );
  read(in, str, SIZE);
  close(in);
  int n;
  int **arr = to_array(str, &n);

  if (check_result(arr, n, 0)){
    int out = open("photo.out", O_CREAT | O_WRONLY, 0644);
    char num[3];
    for (int i = 0; i < n; i ++){
      sprintf(num, "%d\n", arr[0][i]);
      write(out, num, 2);
    }
    close(out);
  }
  else {
    printf("no result found\n");
  }
  return 0;
}
