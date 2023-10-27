#include <time.h>
//Defines log levels ordered by severity from least to most severe.
enum log_level {
  FATAL = 0,
  ERROR = 1,
  WARN = 2,
  INFO = 3,
  DEBUG = 4,
  TRACE = 5
};
// store timestamp as unix epoch, we then process it at print time.
struct log{
  int level;
  char *message;
  char *source;
  time_t timestamp;
};


