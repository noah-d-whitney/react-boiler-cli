#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/params.h"
#include "../include/gen_md.h"
#include "../include/gen_file.h"

int main ( int argc, char *argv[] ) {
	char * path = getenv("PWD");
	char * ext = ".tsx";
	int addProps = 0;
	char markdown[256];

	params processParams;
	processParams.addProps.state = 0;
	processParams.addProps.flag = "--props";

	gen_md(markdown, &processParams, argv[1]);

	for (int i = 1; i < argc; i++) {
		if ( strcmp(argv[i], processParams.addProps.flag) == 0 ) { 
			processParams.addProps.state = 1;
		} else {
			char name[100];
			gen_file_name(name, path, argv[i], ext);
			gen_file(name, argv[i], markdown);
		}
	}

	return(0);
}