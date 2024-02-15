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

void freeArgs(char** args){
    free(args); //free the entire variable
}

char** processArgs (char* string){
    printf("Read in %s", string);
    int argCount = 1;
    int len = 0;
    char** args;

    countArgs(&argCount, &len, string);

    //printf("Number of arguments is %d\n", argCount);
    //printf("Longest word is %d long\n", len);

    len = len + 1; //Account for the \0
    args = (char**)malloc(sizeof(char*) * argCount); //Do I need to account for \0?

    for (int i = 0; i < len; i++) {
        args[i] = (char*) malloc(len * sizeof(char));
    }

    //add each argument to args individually
    for(int i = 0; i < argCount;  i++){
        printf("On run %d ", i + 1);
        //Run once for each word
        while(*string == ' ') string = string + 1; //make sure next while loop starts on the first character
        //printf("First character is '%c'\n", *string);

        int argLen = 0; ; //reset every word
        //Find the length of each individual word
        //using argLen instead of incrementing string to keep string at the start for adding to args[]
        while(*(string+argLen) != ' ' && *(string+argLen) != '\0' && *(string+argLen) != '\n'){ 
            argLen = argLen + 1;
        }
        strncpy(args[i], string, argLen); //add the argument to args
        
        int j = 0;
        while(args[i][j] != '\0'){
            printf("'%c' ", args[i][j]);
            j++;
        }
        printf("\n");

        string = string + argLen; //move on to the next word
    }

    for(int i = 0; i < argCount;  i++){
        printf("'%s' ", args[i]);
    }

    printf("\n");
    return args;
}