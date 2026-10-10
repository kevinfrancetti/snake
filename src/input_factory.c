/*
 * input_factory.c
 *
 *  Created on: Sep 20, 2026
 *      Author: bomber
 */


#include <stdio.h>
#include "input_factory.h"
#include "input_term_binding_to_api.h"


InputApi input_factory_create(INPUT_TYPE type){

	if(type == INPUT_TERMINAL){
		return input_term_bindinig_create();
	}else{
		fprintf(stderr, "No imlementation for GLFW, using TERMINAL \n");
		return input_term_bindinig_create();
	}
}


