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

void getArgLength(int* len, char* arg){

}

void processArgs (char* string){
    int argCount = 1;
    int len = 0;
    char** args;
    char* argStart = string; //should be equal to the start of every arg
    char* currentArg = string; //character being looked at

    countArgs(&argCount, &len, string);
    printf("Number of arguments is %d\n", argCount);
    printf("Longest word is %d long\n", len);

    args = (char**)malloc(sizeof(char*) * argCount); //Do I need to account for \0?
    
    for (int i = 0; i < len; i++) {
        args[i] = (char*) malloc(len * sizeof(char));
    }

    //add each argument to args individually
    for(int i = 0; i < argCount;  i++){
        //Run once for each word
        while(*string == ' ') string = string + 1; //make sure next while loop starts on the first character
        printf("First character is '%c'\n", *string);
        int argLen = 0;
        while(*(string+argLen) != ' ' && *(string+argLen) != '\0' && *(string+argLen) != '\n'){ //using argLen instead of incrementing string to keep string at the start for adding to args[]
            argLen = argLen + 1; //reset every word
        }
        strncpy(args[i], string, argLen); //add the argument to arfs
        
        printf("%s\n", args[i]);

        string = string + argLen; //move on to the next word
    }


    for (int i = 0; i < argCount; i++) {
        free(args[i]);
    }
    free(args);
}