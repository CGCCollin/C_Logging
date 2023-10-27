
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "log-structure.h"
//externally defined functions
extern void file_init();
extern int append_log();

const int LOG_SIZE_LIMIT = 10000;
const int SOURCE_SIZE_LIMIT = 100;
const int LEVEL_SIZE_LIMIT = 10;
//Constants for determining functions of logging utility.
int record_to_file;
int record_to_console;

int *precord_to_file = &record_to_file;
int *precord_to_console = &record_to_console;
char *time_zone = "default";

//creates a new log, provided log level, source, and message are within restircted lengths.
//if invalid, returns null log.
struct log init_log(int level, char *source, char *message){
  struct log new_log;
  if(level < FATAL || level > TRACE){
    fprintf(stderr, "Invalid log level: %d", level);
    new_log.level = 1;
    new_log.source = "CGC_LOGGING";
    new_log.message = "Invalid log level";
    time(&new_log.timestamp);
    return new_log;
  }
  if(sizeof(source)/sizeof(char) > SOURCE_SIZE_LIMIT){
    fprintf(stderr, "Source string too long: %s", source);
    new_log.level = 1;
    new_log.source = "CGC_LOGGING";
    new_log.message = "Source string too long";
    new_log.timestamp = time(NULL);
    return new_log;
  }
  if(sizeof(message)/sizeof(char) > LOG_SIZE_LIMIT){
    fprintf(stderr, "Message string too long: %s", message);
    new_log.level = 1;
    new_log.source = "CGC_LOGGING";
    new_log.message = "Message string too long";
    new_log.timestamp = time(NULL);
    return new_log;
  }
  //above conditions check the validity of the log. Should any fail, an error log will be returned by the function.

  new_log.level = level;
  new_log.source = source;
  new_log.message = message;
  new_log.timestamp = time(NULL);
  return new_log;
}
//converts enum level to string for printing.
char * log_level_string(int level){
  switch(level){
    case FATAL:
      return "FATAL";
    break;
    case ERROR:
      return "ERROR";
    break;
    case WARN:
      return "WARN";
    break;
    case INFO:
      return "INFO";
    case DEBUG:
      return "DEBUG";
    break;
    case TRACE:
      return "TRACE";
    break;
    default:
      return "UNKNOWN";
    break;
  }
}
 
//TODO: implement function that accounts for timezone.
char *timestamp_to_human_readable(time_t timestamp){
  struct tm *timeInfo;
  timeInfo = gmtime(&timestamp);
  char* temp = ("%s",asctime(timeInfo));
  temp[strlen(temp)-1] = '\0';
  return temp;
}

//Converts log to a string for printing.
char *log_string(struct log log){
  //timestamp, level, source, message
  char *log_string_created = malloc(sizeof(char)*(LOG_SIZE_LIMIT + SOURCE_SIZE_LIMIT + (int)ceil(log10(time(NULL))) + LEVEL_SIZE_LIMIT));
  if(time_zone[0] == '\0'){
    char* temp = log_level_string(log.level);
    sprintf(log_string_created, "[%lu] [%s] [%s] %s\n", log.timestamp, temp, log.source, log.message);
    free(temp);

    return log_string_created;
  }

  else{
    sprintf(log_string_created, "[%s] [%s] [%s] %s\n", timestamp_to_human_readable(log.timestamp), log_level_string(log.level), log.source, log.message);
    return log_string_created;
  }

  return NULL;
}

//records log in console, and appends to file.
int process(struct log log_to_process){  
    char * temp = log_string(log_to_process);
    if(record_to_console){
      fprintf(stdout, ("%s",temp));
    }

    if(record_to_file){
      if(append_log(temp)){
        return 1;
      }
      else{
        fprintf(stderr,"ERROR: could not append to log file.\n");
      }
    }
    free(temp);
    return 1;
}

//sends log to engine for processing.
void push(struct log to_push){
  process(to_push);
}

//initializes log, and sends it to engine for processing.
void create_and_push(int level, char *source, char *message){
  push(init_log(level, source, message));
}

//initalizes the logging utility.
void start(char *file_name, char *init_message, int rec_to_file, int rec_to_console, char *tz){
  if (!rec_to_file && !rec_to_console){
    fprintf(stderr, "ERROR: no logging destination specified.\n");
    exit(1);
  }
  time_zone = tz;
  if(time_zone[0] != '\0'){
    _putenv(("TZ=%s",time_zone));
    printf("Timezone set to %s\n", time_zone);
    tzset();
  }
  else{
    time_zone = "";
  }
  *precord_to_console = rec_to_console;
  *precord_to_file = rec_to_file;
  char *buffer = malloc(sizeof(char)*(1000));
  sprintf(buffer, "[%lu] %s", time(NULL), init_message);
  file_init(file_name, buffer);
  free(buffer);
}

