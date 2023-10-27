#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "log-structure.h"

unsigned long now = 0;
unsigned long last_time;
int i = 0;

extern void create_and_push();
extern void start();
extern int end_log(); 

int main(){
  last_time = time(NULL);
  start("logfile.txt","hello",1,1,"LOCAL");
  int i = 0;
  char message[100];
  for(i = 0; i < 1000; i++){
    sprintf(message,"test log %d",i);
    create_and_push(DEBUG, "CGC", message);
  }
  end_log();
  return 0;
}
