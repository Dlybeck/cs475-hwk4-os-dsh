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

void countArgs(int* args, char* string){
    char* currentChar = string;

    while(*currentChar != '\0'){
        if(*currentChar == ' '){
            if(*(currentChar+1) != ' ') {
                *args = *args + 1;
            }
        }
        currentChar++;
    }

}

void processArgs (char* string){
    int argCount = 1;
    char** args = NULL;
    char* argStart = string; //should be equal to the start of every arg
    char* currentArg = string; //character being looked at
    int argLen = 0;

    countArgs(&argCount, string);
    printf("Number of arguments is %d\n", argCount);

    /*while(*currentArg!='\n' && *currentArg!='\0'){
        if(currentArg == ' '){
            currentArg++;
            argStart = currentArg;
            argLen = 0;
        }
        else{
            
        }
    }*/


}

