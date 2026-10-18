/*
 * render_factory.c
 *
 *  Created on: Sep 14, 2026
 *      Author: bomber
 */

#include <stdio.h>
#include "render_factory.h"
#include "render_term_binding_to_api.h"
//#include "render_gl" TODO

RenderAPI render_create(RENDER_TYPE type) {
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


