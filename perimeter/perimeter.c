#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SIZE 9999999

int **to_array(char *str, int *n){
  *n = atoi( strsep(&str, "\n") ) + 2;
  int **arr = calloc(*n, sizeof(int *));
  char *piece;
  int i, j;
  arr[0] = calloc(*n, sizeof(int));
  arr[*n - 1] = calloc(*n, sizeof(int));
  for (i = 1; i < *n - 1; i ++){
    arr[i] = calloc(*n, sizeof(int));
    piece = strsep(&str, "\n");
    for (j = 1; j < *n - 1; j ++){
      if (!strncmp(piece, "#", 1))
        arr[i][j] = 1;
      else
        arr[i][j] = 0;
      piece ++;
    }
  }
  return arr;
}

// void print_arr(int **arr, int n){
//   for (int i = 0; i < n; i ++){
//     for (int j = 0; j < n; j ++){
//       printf("%d ", arr[i][j]);
//     }
//     printf("\n");
//   }
// }

// void restore(int **arr, int n){
//   int i, j;
//   for (i = 0; i < n; i ++){
//     for (j = 0; j < n; j ++){
//
//       if (arr[i][j] == -1)
//         arr[i][j] = 1;
//     }
//   }
// }

int solve(int **arr, int r, int c, int *area, int *perimeter){
  if (arr[r][c] <= 0)
    return 0;
  (*area) ++;
  arr[r][c] = -1;
  if (!solve(arr, r+1, c, area, perimeter) && !arr[r+1][c])
    (*perimeter) ++;
  if (!solve(arr, r-1, c, area, perimeter) && !arr[r-1][c])
    (*perimeter) ++;
  if (!solve(arr, r, c+1, area, perimeter) && !arr[r][c+1])
    (*perimeter) ++;
  if (!solve(arr, r, c-1, area, perimeter) && !arr[r][c-1])
    (*perimeter) ++;
  return 1;
}

int calculate(int **arr, int n, int *perimeter){
  int max_area = 0;
  int min_perimeter = 9999999;
  int a, p;
  int i, j;
  for (i = 1; i < n - 1; i ++){
    for (j = 1; j < n - 1; j ++){
      if (arr[i][j]){
        a = 0;
        p = 0;
        solve(arr, i, j, &a, &p);
        // restore(arr, n);
        if (a > max_area){
          min_perimeter = p;
          max_area = a;
        }
        else if (a == max_area && p < min_perimeter){
          min_perimeter = p;
        }
      }
    }
  }
  *perimeter = min_perimeter;
  return max_area;
}

int main(){

  int in = open("perimeter.in", O_RDONLY);
  char *str = malloc( SIZE );
  read(in, str, SIZE);
  close(in);
  int n;
  int **arr = to_array(str, &n);

  int perimeter;
  int area = calculate(arr, n, &perimeter);
  // for (int i = 0; i < n; i ++){
  //   printf("%d\n", arr[i]->type);
  // }
  // printf("%d\n", max);
  int out = open("perimeter.out", O_CREAT | O_WRONLY, 0644);
  char num[256];
  sprintf(num, "%d %d\n", area, perimeter);
  write(out, num, strlen(num));
    // return 1;
  close(out);

  return 0;
}
