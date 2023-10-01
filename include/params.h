#pragma once

typedef struct Param {
	int state;
	char* flag;
} param;

typedef struct Params {
	char *path, *ext;
	param add_props, js, ts;
} params;

void params_init(params* params);