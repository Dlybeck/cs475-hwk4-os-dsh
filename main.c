/*
 * main.c
 *
 *  Created on: Mar 17 2017
 *      Author: david
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <string.h>
#include "dsh.h"

#define MAX_PROC 250

int main(int argc, char *argv[]) {

	// DO NOT REMOVE THE BLOCK BELOW (FORK BOMB PREVENTION) //
	struct rlimit limit;
	limit.rlim_cur = MAX_PROC;
	limit.rlim_max = MAX_PROC;
	setrlimit(RLIMIT_NPROC, &limit);
	// DO NOT REMOVE THE BLOCK ABOVE THIS LINE //


	char *cmdline = (char*) malloc(MAXBUF); // stores user input from commmand line
	int run = 0;
	while(1){
		if(run > 0){
			printf("dsh> ");
		
			if(fgets(cmdline, MAXBUF, stdin) != NULL){
				char** args;
				args = processArgs(cmdline);

				if(strcmp(args[0], "exit") == 0){
					exit(0);
				}

				/*int argCount = 1;
				int argLen = 0;
				countArgs(&argCount, &argLen, cmdline);

				printf("There are %d arguments ", argCount);

				for(int i = 0; i < argCount; i++){
					free(args[i]);
				}*/

				free(args);
			}
		}
		run = 1;
	}

	return 0;
}
