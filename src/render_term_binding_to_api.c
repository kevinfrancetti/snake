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
		[SHAPE_CROSS]	= 'X',
		[SHAPE_HASH]	= '#',
		[SHAPE_VOID]	= ' ',
		[SHAPE_PLUS]	= '+'
};


//static ScreenBuffer	*p_scrnbuff;
//static NatCellBuff	*p_natcellbuff;

static NatScreenBuffer	screnbuff;
static NatFrameBuff	framebuff;

static void rtb_init(){
	screnbuff = rtn_create_screenbuff();
	framebuff = rtn_create_cellbuff();
	rtn_init();
}

static void rtb_api_cell_to_native_cell_and_push_in_buffer(RendAPIDrawInstructions api){//TODO testing
	NatTermCell cell = {
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
	rtn_push_cell_in_buff(&framebuff, &cell);
}


static void rtb_render2(){
	rtn_render(&framebuff, &screnbuff);
	rtn_framebuff_reset(&framebuff);//TODO check it if works
}

static void rtb_clear_color(RendAPIColorRGB apirgb){
	NatTermColor natrgb = {.r = apirgb.r, .g = apirgb.g, .b = apirgb.b};
	rtn_clear_color(&framebuff, natrgb);
}

RenderAPI render_term_binding_create_api(){
	RenderAPI api = {
			.init			= rtb_init,
			.draw_buff		= rtb_api_cell_to_native_cell_and_push_in_buffer,
			.clear_color	= rtb_clear_color,
			.render_frame	= rtb_render2,
			.clean_screen	= rtn_screen_clean_now,
			.cleanup		= rtn_cleanup
	};
	return api;
}
