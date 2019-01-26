#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

#define PROMPT "measurement"

#define STR_SIZE 64
#define SIZE 999999

struct cow {
  int measurement = 0;
  bool onWall = true;
};


int getMax(struct cow *cows){
  int max = 0;
  for (int i = 0; i < SIZE; i ++){
    if (cows[i].measurement > max)
      max = cows[i].measurement;
  }
  return max;
}

void clear(struct cow *cows){
  for (int i = 0; i < SIZE; i ++)
    cows[i].onWall = false;
}

int main() {

  char fileIn[STR_SIZE] = PROMPT;
  strcat(fileIn, ".in");
  char fileOut[STR_SIZE] = PROMPT;
  strcat(fileOut, ".out");

  ifstream fin(fileIn);
  ofstream fout(fileOut);

  int n, init;
  fin >> n >> init;
  int day, max = 0, ctr = 0;
  int **data = new int*[SIZE];
  for (int i = 0; i < n; i ++){
    fin >> day;
    // cout << day << endl;
    data[day] = new int[2];
    fin >> data[day][0];
    fin >> data[day][1];
  }
  // int *wall = new int[SIZE];
  struct cow *cows = new struct cow[SIZE];
  struct cow *c;
  for (int i = 0; i < SIZE; i ++){
    if (data[i]){
      c = cows + data[i][0];
      c->measurement += data[i][1];
      cout << c->measurement;
      if (c->onWall && c->measurement < max){
        max = getMax(cows);
        if (max > c->measurement){
          c->onWall = false;
          ctr ++;
        }
        // cout << max << endl;
      }
      else if (c->measurement > max){
        clear(cows);
        c->onWall = true;
        max = c->measurement;
        ctr ++;
      }
      else if (!c->onWall && c->measurement == max){
        c->onWall = true;
        ctr ++;
      }
      cout << max << endl;
    }
  }

  fout << ctr;

  return 0;
}
