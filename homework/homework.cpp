#include <iostream>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

#define PROMPT "homework"
#define STR_SIZE 256
#define FILE_SIZE 9999999

int *parse(char *str, int *n){
  *n = stoi( strsep(&str, "\n") );
  int *arr = new int[*n];
  for (int i = 0; i < *n; i ++){
    arr[i] = stoi( strsep(&str, " ") );
  }
  return arr;
}

int *toScores(int *arr, int n, int *ctr){
  double score;
  int *maxIndex = new int[n];
  *ctr = 0;
  double sum;
  int min;
  double max = 0;
  for (int i = 1; i < n - 1; i ++){
    sum = 0;
    min = arr[i];
    for (int j = i; j < n; j ++){
      sum += arr[j];
      if (arr[j] < min)
        min = arr[j];
    }
    score = (sum - min) / (n - i - 1);
    if (score > max){
      max = score;
      maxIndex[0] = i;
      *ctr = 1;
    }
    else if (score == max){
      maxIndex[*ctr] = i;
      *ctr ++;
    }
  }
  return maxIndex;
}

// double getMax(double *scores, int n){
//   double max = scores[1];
//   for (int i = 1; i < n - 1; i ++){
//     if (scores[i] > max)
//       max = scores[i];
//   }
//   return max;
// }

int main() {

  char fileIn[STR_SIZE] = PROMPT;
  strcat(fileIn, ".in");
  int in = open(fileIn, O_RDONLY);
  char input[FILE_SIZE];
  read(in, input, FILE_SIZE);
  close(in);

  int n;
  int *arr = parse(input, &n);

  // cout << n << endl;
  int ctr;
  int *maxes = toScores(arr, n, &ctr);

  char output[FILE_SIZE];
  output[0] = 0;
  char *dummy = output;
  for (int i = 0; i < ctr; i ++){
    dummy += sprintf(dummy, "%d\n", maxes[i]);
  }

  char fileOut[STR_SIZE] = PROMPT;
  strcat(fileOut, ".out");
  int out = open(fileOut, O_CREAT | O_WRONLY, 0644);
  write(out, output, strlen(output));
  close(out);

  return 0;
}
