#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SIZE 9999

struct field{
  int type;
  int num_paths;
  struct field **paths;
};

struct field **to_array(char *str, int *n){
  *n = atoi( strsep(&str, "\n") );
  struct field **arr = calloc(*n, sizeof(struct field *));
  char *piece;
  int i;
  for (i = 0; i < *n; i ++){
    arr[i] = malloc(sizeof(struct field));
    arr[i]->type = 0;
    arr[i]->num_paths = 0;
    arr[i]->paths = calloc(*n - 1, sizeof(struct field *));
  }
  int left, right;
  for (i = 0; i < *n - 1; i ++){
    piece = strsep(&str, "\n");
    left = atoi(strsep(&piece, " ")) - 1;
    right = atoi(piece) - 1;
    arr[left]->paths[arr[left]->num_paths] = arr[right];
    arr[right]->paths[arr[right]->num_paths] = arr[left];
    arr[left]->num_paths ++;
    arr[right]->num_paths ++;
  }
  return arr;
}

// int filled(struct field **arr, int n){
//   int i;
//   for (i = 0; i < n; i ++){
//     if (!arr[i]->type)
//       return 0;
//   }
//   return 1;
// }

int nearby(struct field *f, int t){
  int i;
  if (f->type == t)
    return 1;
  for (i = 0; i < f->num_paths; i ++){
    if (f->paths[i]->type == t)
      return 1;
  }
  return 0;
}

int empty(struct field *f){
  int i;
  for (i = 0; i < f->num_paths; i ++){
    if (f->paths[i]->type == 0)
      return i;
  }
  return -1;
}

int assign(struct field *f, int t, int types){
  // if (f->type != 0)
  //   return 0;
  int i, j, k;
  f->type = t;
  int assigned;
  for (i = 0; i < f->num_paths; i ++){
    if (f->paths[i]->type == 0){
      assigned = 0;
      for (j = 1; j <= types; j ++){
        if (!nearby(f, j) && assign(f->paths[i], j, types)){
          assigned = 1;
          break;
        }
      }
      if (!assigned){
        f->type = 0;
        return 0;
      }
    }
  }
  return 1;
}

int main(){

  int in = open("planting.in", O_RDONLY);
  char *str = malloc( SIZE );
  read(in, str, SIZE);
  close(in);
  int n;
  struct field **arr = to_array(str, &n);

  int max = 1;
  while (!assign(arr[0], 1, max)){
    max ++;
  }
  // for (int i = 0; i < n; i ++){
  //   printf("%d\n", arr[i]->type);
  // }
  // printf("%d\n", max);
  int out = open("planting.out", O_CREAT | O_WRONLY, 0644);
  char num[256];
  sprintf(num, "%d\n", max);
  write(out, num, strlen(num));
    // return 1;
  close(out);

  return 0;
}
