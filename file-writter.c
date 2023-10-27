#include <stdio.h>
#include <stdlib.h>
char *filename = "log.txt";
char *content = "Remember to update the log file!";
FILE *log_file;

int write_log_file();

void file_init(char *INITfilename, char *INITcontent){
  filename = INITfilename;
  content = INITcontent;
  write_log_file();
}

//Initializes log file to be used
int write_log_file(){
  log_file = fopen(filename, "w");
  fprintf(log_file, "%s\n", content);
  fclose(log_file);
  log_file = fopen(filename,"a");
  return 1;
}

//appends to log file
int append_log(char* content){
  fprintf(log_file, "%s", content);
  return 1;
}

int end_log(){
  fclose(log_file);
  return 1;
}
