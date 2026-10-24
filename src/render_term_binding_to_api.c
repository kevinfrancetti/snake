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


static NativeTermContext ctx = { 0 };


static void rtb_api_cell_to_native_cell_and_push_in_buffer(RendAPIDrawInstructions api){//TODO testing
	NativeTermCell cell = {
			.pos.row	= NATIVE_SCREEN_HEIGHT - api.pos.y,
			.pos.col	= api.pos.x,
			.fg.r		= api.fg.r,
			.fg.g		= api.fg.g,
			.fg.b		= api.fg.b,
			.bg.r		= api.bg.r,
			.bg.g		= api.bg.g,
			.bg.b		= api.bg.b,
			.c			= render_term_bindings_to_api[api.shape]
	};
	rtn_draw_buff(&ctx, &cell);
}

static void rtb_render(){
	rtn_render(&ctx);
	rtn_reset_buffer(&ctx);//TODO check it if works
}

RenderAPI render_term_binding_create_api(){
	RenderAPI api = {
			.init			= rtn_init,
			.draw_buff		= rtb_api_cell_to_native_cell_and_push_in_buffer,
			.render_frame	= rtb_render,
			.clean_screen	= rtn_clean_screen,
			.cleanup		= rtn_clean_screen
	};
	return api;
}
