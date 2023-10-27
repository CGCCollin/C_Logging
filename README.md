The purpose of this library to provide a basic set of logging functions for designing simple programs or even more complex ones like game engines.
The logging engine will provide 6 main levels to describe logs:
1. TRACE
2. DEBUG
3. INFO
4. WARN
5. ERROR
6. FATAL
Log leves are ordered from least to most severe and are intended to simplify diagnosis of errors and retrieval of information
when designing programs.
Version: v0.1 provides the following features:
1. Time stamped logs: Logs will be time stamped in user supplied time zones.
2. Enum based log levels: These will determine the severity of logs.
3. Service name: option to name the service being executed.
4. User String: option to input a string detailing the log.
5. Console written: all logs printed to stderr.
6. appended file: rewritten on every session.

To use the library:
1. Include: #include "log-structure.h"
2. Define:
extern void create_and_push();
extern void start();
extern int end_log(); 

where-ever you wish to use the logging feature

3. Use the 'start' function to begin the logging cycle
4. Use 'create_and_push' to create logs and push them to the queue
5. Terminate with 'end_log'

A sample app is provided which can be created using:
`gcc -o test.exe file-writter.c log-structure.c log-structure.h testapp.c`