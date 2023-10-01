#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/gen_md.h"

void inj_snip			(char* destination, int pos, char* seed);
int find_ins_index		(char* string, char* target, int ins_pos);

char* gen_md (char output[256], params *processParams, char *filename) {
	// Declare snippets struct and assign markdown
	snippets md_snips;
	int mdbuf_length;

	//TODO MAKE INTO MACRO
	sprintf(md_snips.base.md, "const %s = () => {\n\treturn <></>;\n}\n\nexport default %s;", filename, filename);
	md_snips.base.ins_pos = 0;

	sprintf(md_snips.interface.md, "interface %sProps {\n\n}", filename);
	md_snips.interface.ins_pos = 0;// CHANGE

	sprintf(md_snips.props.md, "props: %sProps", filename);
	strcpy(md_snips.props.target, "= () =>");
	md_snips.props.ins_pos = 3;

	mdbuf_length = sizeof md_snips;
	char* mdbuf = (char*)malloc(sizeof (mdbuf_length + 1));

	// Copy base markdown to buffer
	strcpy(mdbuf, md_snips.base.md);
	// Print MDBUF

	int i = find_ins_index(mdbuf, md_snips.props.target, md_snips.props.ins_pos);
	inj_snip(mdbuf, i, md_snips.props.md);

	strcpy(output, mdbuf);

	free(mdbuf);
	return output;
}

void inj_snip(char* destination, int pos, char* seed) {
    char strC[strlen(destination) + strlen(seed) + 1];

    strncpy(strC,destination,pos);
    strC[pos] = '\0';
    strcat(strC,seed);
    strcat(strC,destination+pos);
    strcpy(destination,strC);
}

int find_ins_index(char* string, char* target, int ins_pos) {
	int ins_index, matched_index;
	char matched[strlen(target)];

	matched_index = 0;

	for (int i = 0; i < strlen(string); i++) {

		if (strcmp(matched, target) == 0) {
			ins_index = i - strlen(target) + ins_pos;
			break;
		}

		if (string[i] == target[matched_index]) {
			matched[matched_index] = target[matched_index]; 
			matched_index++;
		} else {
			matched[0] = '\0';
			matched_index = 0;
		}

	}

	return ins_index;
}

char * gen_file_name (char output[100], char * path, char * name, char * ext) {
	sprintf(output, "%s/%s%s", path, name, ext);
	return output;
}
