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

int argCount;

void createProcess(char** args, char* path, int background) {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        execv(path, args); //will always execute the new process
        exit(1);
    } else {
        // Parent process
        if (background == 0) {
            // Wait for the correct process (I don't understand why I have to use this but it fixed my errors)
            waitpid(pid, NULL, 0);
        }
    }
}



int checkForWait(char** args){
    if(args[argCount-1][0] == '&'){
        printf("There is a trailing &\n");
        args[argCount-1][0] = '\0';
        args[argCount-1] = NULL;
        argCount = argCount - 1;
        return 1;
    }
    else return 0;
}

void mode1(char** args){
    // Find the end of the path argument and check for &
    int background = checkForWait(args);
    
    // Check if it's executable
    if (access(args[0], F_OK | X_OK) == 0) {
        // Separate path from arguments
        char *path = (char*)malloc(strlen(args[0]) + 1);
        strcpy(path, args[0]);

        createProcess(args, path, background);

        free(path);
    } 
    else {
        printf("ERROR: %s not found!\n", args[0]);
    }
}

void mode2(char** args, char* cwd){
    int done = 0;
    done += checkCWD(cwd, args);
    done += checkCD(args);

    if(done > 0) return;

    // Find the end of the path argument and check for &
    int background = checkForWait(args);

    char string[102]; //:/opt/local/bin:/opt/local/sbin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/opt/X11/bin:/usr/texbin is 101 characters long
    strcpy(string, ":/opt/local/bin:/opt/local/sbin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/opt/X11/bin:/usr/texbin");
    string[101] = '\0';

    char* nextPath = (char*)malloc(sizeof(char) * (16 + 1 + 100 + 1)); //16 for the longest location above, 1 for /, 100 for argument (idk how long), 1 for \0

    //Find each location to check
    char* location = strtok(string, ":");
    int ran = 0;
    while(location != NULL && ran == 0){
        strcpy(nextPath, location);
        strcat(nextPath, "/");
        strcat(nextPath, args[0]);

        // Check if it's executable
        if (access(nextPath, F_OK | X_OK) == 0) {
            createProcess(args, nextPath, background);
            ran = 1; //the file was ran!
        }
        location = strtok(NULL, ":");
    }
    if(ran == 0) printf("ERROR: %s not found!\n", args[0]);

    free(nextPath);

}

int checkCD(char** args){
    if(strcmp(args[0], "cd") == 0 && getArgCount(args) > 1){
        if (chdir(args[1]) != 0) 
            printf("%s is not a valid directory\n", args[1]); 
        return 1;
    }
    return 0;
}

void checkExit(char* cmdline, char** args){
    if(strcmp(args[0], "exit") == 0){
        freeArgs(cmdline, args);
        exit(0);
	}
}

int checkCWD(char* cwd, char** args){
    if(strcmp(args[0], "pwd") == 0){
        char cwdArray[32768]; //Max path size?
        cwd[MAX_PATH] = '\0';
        sprintf(cwd, "%s\n", getcwd(cwdArray, sizeof(cwdArray)));
        printf("%s", cwd);
        return 1;
    }
    return 0;
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

char** split (char* string){
    //printf("Read in %s", string);
    argCount = 1;
    int len = 0;
    char** args;

    countArgs(&argCount, &len, string);

    //printf("Number of arguments is %d\n", argCount);
    //printf("Longest word is %d long\n", len);

    args = (char**)malloc(sizeof(char*) * (argCount + 1));
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

        string = string + argLen; //move on to the next word
    }
    args[argCount] = NULL;

    /*for(int i = 0; i < argCount;  i++){
        printf("'%s' ", args[i]);
    }
    printf("\n");*/

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

int getArgCount(){
    return argCount;
}
