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

static ScreenBuffer	scrnbuff;
static NatCellBuff	cellbuff;

static void rtb_init(){
	//p_scrnbuff = rtn_get_scrnbuff();//remove
	//p_natcellbuff = rtn_get_natcellbuff();//remove
	scrnbuff = rtn_create_screenbuff();
	cellbuff = rtn_create_cellbuff();
	rtn_init();
}

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
	rtn_push_cell_in_buff(&cellbuff, &cell);
}

static void rtb_clean_screen(){
	rtn_clean_screen2(&scrnbuff);
}

/*
static void rtb_render(){
	rtn_render(&cellbuff);
	rtn_reset_natcellbuff(&cellbuff);//TODO check it if works
}
*/

static void rtb_render2(){
	rtn_render2(&cellbuff, &scrnbuff);
	rtn_reset_cellbuff(&cellbuff);//TODO check it if works
}

RenderAPI render_term_binding_create_api(){
	RenderAPI api = {
			.init			= rtb_init,
			.draw_buff		= rtb_api_cell_to_native_cell_and_push_in_buffer,
			.render_frame	= rtb_render2,
			.clean_screen	= rtb_clean_screen,
			.cleanup		= rtn_cleanup
	};
	return api;
}
