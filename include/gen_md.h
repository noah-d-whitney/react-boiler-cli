#include "params.h"

typedef struct Snippet {
	char md[100];
	int ins_pos;
	char target[20];
} snippet;

typedef struct Snippets {
	snippet base;
	snippet interface;
	snippet props;
} snippets;

char* gen_md 		(char output[256], params *processParams, char *filename);
char* gen_file_name	(char output[100], char * path, char * name, char * ext);
