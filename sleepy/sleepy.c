#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SIZE 99999

int *to_array(char *str, int *n){
  *n = atoi( strsep(&str, "\n") );

  int *arr = calloc(*n, sizeof(int));
  int i;
  for (i = 0; i < *n; i ++){
    arr[i] = atoi( strsep(&str, " ") );
  }
  return arr;
}

int is_sorted(int *arr, int n){
  int i;
  for (i = 0; i < n - 1; i ++){
    if (arr[i + 1] - arr[i] != 1)
      return 0;
  }
  return 1;
}

void move(int *arr, int end){
  int temp = arr[0];
  int i;
  for (i = 0; i < end; i ++){
    arr[i] = arr[i + 1];
  }
  arr[end] = temp;
}

int sort(int *arr, int n){
  int ctr = 0;
  int i;
  int pos_sorted = n - 1;
  for (i = n - 1; i > 0; i --){
    if (arr[i] > arr[i - 1]){
      pos_sorted = i - 1;
    }
    else
      break;
  }
  while (!is_sorted(arr, n)){
    for (i = n - 1; i >= pos_sorted; i --){
      if (arr[0] > arr[i])
        break;
    }
    pos_sorted --;
    move(arr, i);
    // for (int i = 0; i < n; i ++)
    //   printf("%d ", arr[i]);
    // printf("\n");
    ctr ++;
  }
  return ctr;
}

int main(){

  int in = open("sleepy.in", O_RDONLY);
  char *str = malloc( SIZE );
  if (read(in, str, SIZE) == -1)
    return 1;
  close(in);
  int n;
  int *arr = to_array(str, &n);

  int ctr = sort(arr, n);


  int out = open("sleepy.out", O_CREAT | O_WRONLY, 0644);
  char num[SIZE];
  sprintf(num, "%d\n", ctr);
  if (write(out, num, strlen(num)) == -1)
    return 1;
  close(out);

  return 0;
}
