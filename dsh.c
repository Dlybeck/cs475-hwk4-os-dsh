/*
 * dsh.c
 *
 *  Created on: Aug 2, 2013
 *      Author: chiu
 */
#include "dsh.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <errno.h>
#include <err.h>
#include <sys/stat.h>
#include <string.h>


// TODO: Your function definitions below (declarations in dsh.h)

/**
 * This is just an example. Delete this before 
 * submission.
 */
void example(int* x) {
    //*x = thisIsGlobal;
} 

void countArgs(int* args, int* maxLen, char* string){
    char* currentChar = string;
    int len = -1;

    while(*currentChar != '\0'){
        if(*currentChar == ' '){
            len = 0;
            if(*(currentChar+1) != ' ') {
                *args = *args + 1;
            }
        }
        else{
            len = len + 1;
            if(len > *maxLen) *maxLen = len;
        }
        currentChar++;
    }
}

void processArgs (char* string){
    int argCount = 1;
    int len = 0;
    char** args = NULL;
    char* argStart = string; //should be equal to the start of every arg
    char* currentArg = string; //character being looked at
    int argLen = 0;

    countArgs(&argCount, &len, string);
    printf("Number of arguments is %d\n", argCount);
    printf("Longest word is %d long", len);

    


}

