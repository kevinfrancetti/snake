/*
 * input_factory.c
 *
 *  Created on: Sep 20, 2026
 *      Author: bomber
 */


#include <stdio.h>
#include "input_factory.h"
#include "input_term.h"


InputApi input_create(INPUT_TYPE type){

	if(type == INPUT_TERMINAL){
		return input_term_create();
	}else{
		fprintf(stderr, "No imlementation for GLFW, using TERMINAL \n");
		return input_term_create();
	}
}


