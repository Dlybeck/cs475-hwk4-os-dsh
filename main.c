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
	char *cwd = (char*) malloc((MAX_PATH+1) * sizeof(char));
	int run = 0;
	while(1){
		if(run > 0){
			printf("dsh> ");
		
			if(fgets(cmdline, MAXBUF, stdin) != NULL){
				int output = 0;
				char** args;
				args = split(cmdline);

				checkExit(cmdline, args);
				output += checkCWD(cwd, args);
				output += checkCD(args);
				
				if(args[0][0] == '/')
					output += mode1(args);
				else
					output += mode2(args);

				if(output == 0) printf("'%s' is not a valid command\n", args[0]);

				freeArgs(cmdline, args);
			}
		}
		run = 1;
	}

	return 0;
}
