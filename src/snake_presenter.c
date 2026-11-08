/*
 * snake_presenter.c
 *
 *  Created on: Oct 6, 2026
 *      Author: bomber
 */

#include "snake_presenter.h"
#include "debug.h"

//SP := Snake Presenter
#define SP_RGB(red, green, blue)	{ .r = red, .g = green, .b = blue }


//Colors
#define WORLD_BG_BG			SP_RGB(0, 100, 100)
#define WORLD_BG_EDGE 		SP_RGB(255, 0, 255)
#define WORLD_FG_EDGE		SP_RGB(0, 255, 0)

static RenderAPI *render;

typedef enum{
	CELL_HEAD,
	CELL_BODY,
	CELL_WALL,
	CELL_BACKGROUND,
	CELL_FOOD
}PRESENTER_CELL_TYPE;

static void snk_pres_new_first_draw(SNK_GAME_STATE *state){
	RendAPIDrawInstructions cell;

		for (int y = 1; y < state->height; y++) {
			for (int x = 1; x < state->width; x++) {
				cell.pos.x = x;
				cell.pos.y = y;
				if (y == 1 || x == 1 || y == state->height - 1
						|| x == state->width - 1) {
					cell.shape = SHAPE_HASH;
					cell.fg = (RendAPIColorRGB ) WORLD_FG_EDGE;
					cell.bg = (RendAPIColorRGB ) WORLD_BG_EDGE;
				} else {
					cell.shape = SHAPE_VOID;
					cell.bg = (RendAPIColorRGB ) WORLD_BG_BG;
				}
				render->draw_buff(cell);
			}
		}
		render->render_frame();
}

void snk_pres_init(RenderAPI *rend, SNK_GAME_STATE *state){
	render = rend;
	snk_pres_new_first_draw(state);
}

static void set_cell_style(RendAPIDrawInstructions *cell, PRESENTER_CELL_TYPE type) {

	switch (type) {
	case CELL_HEAD:
		cell->fg = (RendAPIColorRGB ) { .r = 24, .g = 34, .b = 255 };
		cell->bg = (RendAPIColorRGB ) { .r = 100, .g = 150, .b = 255 };
		cell->shape = SHAPE_CIRCLE;
		break;
	case CELL_BODY:
		cell->fg = (RendAPIColorRGB ) { .r = 24, .g = 34, .b = 255 };
		cell->bg = (RendAPIColorRGB ) { .r = 255, .g = 150, .b = 0 };
		cell->shape = SHAPE_HASH;
		break;
	case CELL_FOOD:
		cell->fg = (RendAPIColorRGB ) { .r = 24, .g = 34, .b = 255 };
		cell->bg = (RendAPIColorRGB ) { .r = 255, .g = 150, .b = 0 };
		cell->shape = SHAPE_PLUS;
		break;
	case CELL_BACKGROUND:
		cell->bg = (RendAPIColorRGB ) WORLD_BG_BG;
		cell->shape = SHAPE_VOID;
		break;
	}

}

void snk_pres_rend(SNK_GAME_STATE *gamestate){//new
	Snk2 *snake = &gamestate->snk2;
	const int head = snake->head;
	const int tail = snake->tail;
	const int len = snake->len;
	//render->clean_screen();

	RendAPIDrawInstructions cell;
	cell.pos.x = gamestate->food.pos.x;
	cell.pos.y = gamestate->food.pos.y;
	set_cell_style(&cell, CELL_FOOD);
	render->draw_buff(cell);

	cell.pos.x = snake->body[tail].x;
	cell.pos.y = snake->body[tail].y;

	/*
	if(len == 1){
		set_cell_style(&cell, CELL_HEAD);
		render->draw_buff(cell);
	}
	*/

	for(int i = 0; i < len; i++){
		cell.pos.x = snake->body[(tail + i)%SNK_MAX_LEN].x;
		cell.pos.y = snake->body[(tail + i)%SNK_MAX_LEN].y;
		if(i == len - 1){
			set_cell_style(&cell, CELL_HEAD);
		}else{
			set_cell_style(&cell, CELL_BODY);
		}
		render->draw_buff(cell);
	}
	if(len < SNK_MAX_LEN){//TODO
		cell.pos.x = snake->body[(tail + SNK_MAX_LEN - 1) % SNK_MAX_LEN].x;//TODO
		cell.pos.y = snake->body[(tail + SNK_MAX_LEN - 1) % SNK_MAX_LEN].y;
		DEBUG1s1i("remove x=", cell.pos.x);
		DEBUG1s1i("remove y=", cell.pos.y);
		set_cell_style(&cell, CELL_BACKGROUND);
		render->draw_buff(cell);
	}else{

	}


	render->render_frame();

}
