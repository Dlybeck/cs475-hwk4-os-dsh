#define MAXBUF 256  // max number of characteres allowed on command line
#define MAX_PATH 32768

// TODO: Function declarations go below
void example(int*); // delete before submission

void countArgs(int*, int*, char*);

char** processArgs(char*);

void freeArgs(char*, char**);

void checkExit(char*, char**);

void checkCWD(char*, char**);

