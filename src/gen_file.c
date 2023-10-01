#include <stdio.h>
#include "../include/gen_file.h"

int file_exists (const char *filename);

void gen_file (const char* filepath, char* filename, char* markdown) {
	if (!file_exists(filepath)) {
		FILE *file = fopen(filepath, "w");
		fprintf(file, "%s", markdown);

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

char * gen_file_name (char output[100], char * path, char * name, char * ext) {
	sprintf(output, "%s/%s%s", path, name, ext);
	return output;
}