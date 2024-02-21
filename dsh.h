#define MAXBUF 256  // max number of characteres allowed on command line
#define MAX_PATH 32768

void createProcess(char**, char*, int);

int checkForWait(char**);

void mode1(char**);

void mode2(char**, char*);

int checkCD(char**);

void countArgs(int*, int*, char*);

char** split(char*);

void checkExit(char*, char**);

int checkCWD(char*, char**);

void freeArgs(char*, char**);

int getArgCount();

