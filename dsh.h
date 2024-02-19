#define MAXBUF 256  // max number of characteres allowed on command line
#define MAX_PATH 32768

int mode1(char**);

int mode2(char**);

int checkCD(char**);

void countArgs(int*, int*, char*);

char** split(char*);

void checkExit(char*, char**);

int checkCWD(char*, char**);

void freeArgs(char*, char**);

int getArgCount();

