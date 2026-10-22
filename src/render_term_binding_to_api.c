/*
 * render_term_binding_to_api.c
 *
 *  Created on: Oct 10, 2026
 *      Author: bomber
 */


#include "render_term_binding_to_api.h"
#include "render_term_native.h"


const char render_term_bindings_to_api[] = {
		[SHAPE_CIRCLE]	= 'O',
		[SHAPE_CROSS]	= 'X'
};

/*
static void render_term_binding_api_shape_to_native(RENDER_API_SHAPE shape){
	render_term_native_set_char(render_term_bindings_to_api[shape]);
}
*/

static void render_term_binding_api_drawcell_to_native(int raw, int col, RENDER_API_SHAPE shape){
	render_term_native_draw_cell(raw, NATIVE_SCREEN_HEIGHT - col, render_term_bindings_to_api[shape]);
}

RenderAPI render_term_binding_create_api(){
	RenderAPI api = {
			.init			= render_term_native_init,
			.draw_cell		= render_term_binding_api_drawcell_to_native,
			.render_frame	= render_term_native_render,
			.clean_screen	= render_term_native_clean_screen,
			.cleanup		= render_term_native_clean_screen
	};
	return api;
}
