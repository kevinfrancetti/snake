/*
 * render_factory.c
 *
 *  Created on: Sep 14, 2026
 *      Author: bomber
 */

#include <stdio.h>
#include "render_factory.h"
#include "render_term.h" //TODO to be removed
#include "render_term_binding_to_api.h"
//#include "render_gl" TODO

RenderAPI render_create2(RENDER_TYPE type) {
	switch (type) {
	case RENDER_TERMINAL:
		return render_term_binding_create_api();
		break;
	case RENDER_OPENGL:
		return render_term_binding_create_api(); //TODO
		break;
	default:
		return render_term_binding_create_api(); //TODO
	}
}

RenderAPI render_create(RENDER_TYPE type) {
	if (type == RENDER_TERMINAL)
		return terminal_render_create();
	if (type == RENDER_OPENGL) {
		fprintf(stderr, "OPENGL NOT IMPLEMENTED, USING TERMINAL\n");
		return terminal_render_create();
	}

	return terminal_render_create();

}
