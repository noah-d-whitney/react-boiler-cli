#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/params.h"
#include "../include/gen_md.h"
#include "../include/gen_file.h"

int main ( int argc, char *argv[] ) {
	char markdown[256];
	params process_params;
	params_init(&process_params);

	char** file_args;
	int file_args_i = 0;
	file_args = malloc(argc * sizeof(char*));

	for (int i = 1; i < argc; i++) {
		char* arg = argv[i];
		if ( strcmp(arg, process_params.add_props.flag) == 0 ) { 
			process_params.add_props.state = 1;
		}
		else if (strcmp(arg, process_params.ts.flag) == 0) {
			process_params.ts.state = 1;
			process_params.js.state = 0;
		}
		else if (strcmp(arg, process_params.js.flag) == 0) {
			process_params.js.state = 1;
			process_params.ts.state = 0;
		}
		else {
			file_args[file_args_i] = malloc(strlen(arg) * sizeof(char));
			strcpy(file_args[file_args_i], arg);
			file_args_i++;
			printf("%i\n", file_args_i);
		}
	}

	for (int i = 0; i < file_args_i; i++) {
		char name[100];
		gen_md(markdown, &process_params, file_args[i]);
		gen_file_name(name, process_params.path, file_args[i], process_params.ext);
		gen_file(name, file_args[i], markdown);
		markdown[0] = '\0';
	}

	return(0);
}