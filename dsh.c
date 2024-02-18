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

void checkExit(char* cmdline, char** args){
    if(strcmp(args[0], "exit") == 0){
        freeArgs(cmdline, args);
        exit(0);
	}
}

void checkCWD(char** args){
    if(strcmp(args[0], "cwd") == 0){
        char cwd[32768]; //Max path size?
        printf("%s\n", getcwd(cwd, sizeof(cwd)));
	}
}

void countArgs(int* args, int* maxLen, char* string){
    char* currentChar = string;
    int len = -1;

    while(*currentChar != '\0' && *currentChar != '\n'){
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

char** processArgs (char* string){
    printf("Read in %s", string);
    int argCount = 1;
    int len = 0;
    char** args;

    countArgs(&argCount, &len, string);

    //printf("Number of arguments is %d\n", argCount);
    //printf("Longest word is %d long\n", len);

    args = (char**)malloc(sizeof(char*) * argCount); //Do I need to account for \0?

    // make room for \0
    len = len + 1; 

    for (int i = 0; i < argCount; i++) {
        args[i] = (char*) malloc((len + 1) * sizeof(char)); //IDK why +1 since already added before, but it fixes errors

        //add each argument to args individually
        while(*string == ' ') string = string + 1; //make sure next while loop starts on the first character

        int argLen = 0;
        // Find the length of each individual word
        while(*(string+argLen) != ' ' && *(string+argLen) != '\0' && *(string+argLen) != '\n'){ 
            argLen = argLen + 1;
        }

        //argLen already accounts for null terminator (When used as index)
        strncpy(args[i], string, argLen);\

        args[i][argLen] = '\0'; //Add the null-terminator

        /*int j = 0;
        while(args[i][j] != '\0'){
            printf("'%c' ", args[i][j]);
            j++;
        }
        printf("\n");*/

        string = string + argLen; //move on to the next word
    }

    for(int i = 0; i < argCount;  i++){
        printf("'%s' ", args[i]);
    }

    printf("\n");
    return args;
}

void freeArgs(char* cmdline, char** args){
    int argCount = 1;
    int argLen = 0;
    countArgs(&argCount, &argLen, cmdline);
    //printf("There are %d arguments\n", argCount);
    for(int i = 0; i < argCount; i++){
        free(args[i]);
    }
    free(args);
}
