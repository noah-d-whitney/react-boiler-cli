#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void generateFiles(char *path, char *filename);
int file_exists (const char *filename);

int main ( int argc, char *argv[] ) {
	char *path = getenv("PWD");
	char *filename = argv[2];

	if ( strcmp(argv[1], "generate") == 0 ) {
		generateFiles(path, filename);
	}
}

void generateFiles(char *path, char *filename) {
	const char *filepath = strcat(path, filename);
	int exists = file_exists(filepath);
	
	printf("PATH :%s\n", (exists == 0) ? filepath : "getenv returned NULL");

	if (!exists) {
		FILE *file = fopen(filepath, "w");
		fprintf(file, "const Test = () => {\n\n}\n\nexport default Test;");

		fclose(file);
	}

}

int file_exists (const char *filename) {
	FILE *fp = fopen(filename, "r");
	bool is_exist = 0;

	if (fp != NULL) {
    	is_exist = 1;
    	fclose(fp); // close the file
	}

	return is_exist;
}