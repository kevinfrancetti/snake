/*
 * render_factory.c
 *
 *  Created on: Sep 14, 2026
 *      Author: bomber
 */

#include <stdio.h>
#include "render_factory.h"
#include "render_term.h"
//#include "render_gl" TODO


RenderAPI render_create(RENDER_TYPE type){
	if(type == RENDER_TERMINAL) return terminal_render_create();
	if(type == RENDER_OPENGL){
		fprintf(stderr, "OPENGL NOT IMPLEMENTED, USING TERMINAL\n");
		return terminal_render_create();
	}

	return terminal_render_create();

}
