#include <iostream>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

using namespace std;

#define STR_SIZE 256
#define FILE_SIZE 1024

int main(int argc, char const *argv[]) {

  // cout << argc << endl;
  if (argc != 2){
    cout << "invalid input" << endl;
    return 1;
  }

  char *prompt = new char[STR_SIZE];
  strcpy(prompt, argv[1]);

  if (!fork()){
    execlp("mkdir", "mkdir", prompt, NULL);
  }

  int status;
  wait(&status);

  int fd = open("template.first", O_RDONLY);
  char *buf = new char[FILE_SIZE];
  read(fd, buf, FILE_SIZE);
  close(fd);
  buf[strlen(buf) - 1] = 0;
  strcat(buf, "\"");
  strcat(buf, prompt);
  strcat(buf, "\"");
  strcat(buf, "\n");

  fd = open("template.second", O_RDONLY);
  char *buff = new char[FILE_SIZE];
  read(fd, buff, FILE_SIZE);
  close(fd);
  strcat(buf, buff);

  chdir(prompt);

  char *file_cpp = new char[STR_SIZE];
  strcpy(file_cpp, prompt);
  strcat(file_cpp, ".cpp");

  fd = open(file_cpp, O_CREAT | O_WRONLY, 0644);
  write(fd, buf, strlen(buf));
  close(fd);
  // execlp("cp", "cp", "template.cpp", file_cpp, NULL);

  if (!fork()){
    char *file_in = new char[STR_SIZE];
    strcpy(file_in, prompt);
    strcat(file_in, ".in");
    execlp("touch", "touch", file_in, NULL);
  }

  return 0;
}
