#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Param {
	int state;
	char *flag;
} param;

typedef struct Params {
	param addProps;
} params;

char * generateFileName (char output[100], char * path, char * name, char * ext);
void generateFiles(const char * filepath, char * filename);
int file_exists (const char *filename);
char * generateMarkup (char output[256], params *processParams, char *filename);
int askQuestion(const char *question, char *answer, const size_t max_answer_length);

int main ( int argc, char *argv[] ) {
	char * path = getenv("PWD");
	char * ext = ".tsx";
	int addProps = 0;
	char markup[256];


	params processParams;
	processParams.addProps.state = 0;
	processParams.addProps.flag = "--props";

	generateMarkup(markup, &processParams, argv[1]);
	printf("FILENAME: %s\nMarkup: %s", argv[1], markup);

	int i;
	for (i = 1; i < argc; i++) {
		if ( strcmp(argv[i], processParams.addProps.flag) == 0 ) { 
			processParams.addProps.state = 1;
		}
	}

	for (i = 1; i < argc; i++) {
		char name[100];
		generateFileName(name, path, argv[i], ext);
		generateFiles(name, argv[i]);
	}

	printf("%i\n", processParams.addProps.state);

	return(0);
}

char * generateFileName (char output[100], char * path, char * name, char * ext) {
	sprintf(output, "%s/%s%s", path, name, ext);
	return output;
}

char * generateMarkup (char output[256], params *processParams, char *filename) {
	typedef struct Snippets {
		char base[100];
		char interface[50];
		char props[20];
	} snippets;

	// Declare snippets struct and assign markdown
	snippets mdSnip;
	sprintf(mdSnip.base, "const %s = () => {\n\treturn <></>;\n}\n\nexport default %s;", filename, filename);
	sprintf(mdSnip.interface, "interface %sProps {\n\n}", filename);
	sprintf(mdSnip.props, "props: %sProps", filename);

	sprintf(output, "%s\n\nconst %s = (%s) => {\n\treturn <></>;\n}\n\nexport default %s;", mdSnip.interface, filename, mdSnip.props, filename);

	// sprintf(interfaceSlice, "interface %sProps {}\n\n", filename);
	// sprintf(componentSlice, "const %s = () => {\n\treturn <></>;\n}\n\nexport default %s;", filename, filename);
	// sprintf(componentSliceProps, "const %s = (props: %sProps) => {\n\treturn <></>;\n}\n\nexport default %s;", filename, filename, filename);


	// if (processParams->addProps.state) {
	// 	sprintf(output, "%s%s", interfaceSlice, componentSliceProps);
	// } else {
	// 	sprintf(output, "%s", componentSlice);
	// }

	return output;
}

void generateFiles(const char * filepath, char * filename) {
	if (!file_exists(filepath)) {
		FILE *file = fopen(filepath, "w");
		fprintf(file, "const %s = () => {\n\treturn <></>;\n}\n\nexport default %s;", filename, filename);

		fclose(file);
	}
}

int file_exists (const char *filename) {
	FILE *fp = fopen(filename, "r");
    int is_exist = 0;

    if (fp != NULL) {
        is_exist = 1;
		printf("The file %s already exists!\n", filename);
        fclose(fp);
    }

    return is_exist;
}

int askQuestion(const char *question, char *answer, const size_t max_answer_length)
{
    int input_ok = 1;  

    // Show the user the question
    printf( "%s: ", question );

    // Throw away any existing input in the user's input-queue
    // (like if they answered with a really-long string previously)
    fflush(stdin);

    // Read a line of input from the user into <answer>, but not more
    // than <max_answer_length>-1 bytes are accepted (see fgets() for details)
    // If the fgets() returns EOF or an error, make sure we remember it
    if ( fgets( answer, max_answer_length, stdin ) == NULL )
        input_ok = 0;

    // return whether there was an error on input
    return input_ok;
}