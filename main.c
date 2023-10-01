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
void generateFiles		(const char * filepath, char * filename);
int file_exists 		(const char *filename);
char * generateMarkup 	(char output[256], params *processParams, char *filename);
int askQuestion			(const char *question, char *answer, const size_t max_answer_length);
void insertString		(char* destination, int pos, char* seed);
int find_ins_index		(char* string, char* target, int ins_pos);


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
	typedef struct Snippet {
		char md[100];
		int ins_pos;
		char* target;
	} snippet;

	typedef struct Snippets {
		snippet base;
		snippet interface;
		snippet props;
	} snippets;

	// Declare snippets struct and assign markdown
	snippets md_snips;
	int mdbuf_length;

	//TODO MAKE INTO MACRO
	sprintf(md_snips.base.md, "const %s = () => {\n\treturn <></>;\n}\n\nexport default %s;", filename, filename);
	md_snips.base.ins_pos = 0;

	sprintf(md_snips.interface.md, "interface %sProps {\n\n}", filename);
	md_snips.interface.ins_pos = 0;// CHANGE

	sprintf(md_snips.props.md, "props: %sProps", filename);
	md_snips.props.target = "st = ()";
	md_snips.props.ins_pos = 3;

	mdbuf_length = sizeof md_snips;
	char* mdbuf = (char*)malloc(sizeof (mdbuf_length + 1));
	// Copy base markdown to buffer
	strcpy(mdbuf, md_snips.base.md);

	// Print MDBUF
	printf("\nMDBUF: %c\n", mdbuf[0]);

	find_ins_index(mdbuf, md_snips.props.target, md_snips.props.ins_pos);


	sprintf(output, "%s\n\nconst %s = (%s) => {\n\treturn <></>;\n}\n\nexport default %s;", md_snips.interface.md, filename, md_snips.props.md, filename);

	free(mdbuf);
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

void insertString(char* destination, int pos, char* seed)
{
    char * strC;

    strC = (char*)malloc(strlen(destination)+strlen(seed)+1);
    strncpy(strC,destination,pos);
    strC[pos] = '\0';
    strcat(strC,seed);
    strcat(strC,destination+pos);
    strcpy(destination,strC);
    free(strC);
}

int find_ins_index(char* string, char* target, int ins_pos) {
	int ins_index;
	int matched_index = 0;
	char matched[strlen(target)];


	for (int i = 0; i < strlen(string); i++) {

		if (string[i] == target[matched_index]) {
			matched[matched_index] = target[matched_index]; 
			matched_index++;
		} else {
			matched[0] = '\0';
			matched_index = 0;
		}

		if (strcmp(matched, target) == 0) {
			printf("\nTarget Found\n");
			break;
		}

		// printf("Matched ind: %i, i: %i, cur: %c, matched: %s\n", matched_index, i, string[i], matched);
	}

	// printf("Input String: %s\n", string);
	// printf("Target: %s\n", target);
	// printf("Insert Position: %i\n", matched_index);

	return 0;
}