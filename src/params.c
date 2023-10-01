#include <stdlib.h>
#include "../include/params.h"

void params_init(params* params) {
	params->add_props.flag = "--props";
	params->add_props.state = 0;
	params->js.flag = "--js";
	params->js.state = 0;
	params->ts.flag = "--ts";
	params->ts.state = 1;
	params->ext = ".tsx";
	params->path = getenv("PWD");
} 
