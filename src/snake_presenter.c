/*
 * snake_presenter.c
 *
 *  Created on: Oct 6, 2026
 *      Author: bomber
 */

#include "snake_presenter.h"

//SP := Snake Presenter
#define SP_RGB(red, green, blue)	{ .r = red, .g = green, .b = blue }


//Colors
#define WORLD_BG_BG			SP_RGB(0, 100, 100)
#define WORLD_BG_EDGE 		SP_RGB(255, 0, 255)
#define WORLD_FG_EDGE		SP_RGB(0, 255, 0)

static RenderAPI *render;
static SNK_GAME_STATE *g_gamestate;

typedef enum{
	CELL_HEAD,
	CELL_BODY,
	CELL_WALL
}PRESENTER_CELL_TYPE;

typedef struct {
	Element buff[100];
	int len;
} DrawMemory;

static DrawMemory g_memory;
static DrawMemory next;

static void snk_pres_first_draw(void);



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

void snk_pres_new_init(RenderAPI *rend, SNK_GAME_STATE *state){
	render = rend;
	snk_pres_new_first_draw(state);
}

void snk_pres_init(RenderAPI *rend, SNK_GAME_STATE *state) {
	render = rend;
	g_gamestate = state;
	snk_pres_first_draw();
}

static void snk_pres_first_draw() {
	RendAPIDrawInstructions cell;

	for (int y = 1; y < g_gamestate->height; y++) {
		for (int x = 1; x < g_gamestate->width; x++) {
			cell.pos.x = x;
			cell.pos.y = y;
			if (y == 1 || x == 1 || y == g_gamestate->height - 1
					|| x == g_gamestate->width - 1) {
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



void clear_old_drawn() {
	RendAPIDrawInstructions cellclear;

	for (int i = 0; i < g_memory.len; i++) {
		cellclear.pos.x = g_memory.buff[i].pos.x;
		cellclear.pos.y = g_memory.buff[i].pos.y;
		cellclear.fg = (RendAPIColorRGB ) { .r = 0, .g = 0, .b = 0 };//TODO probably can remove this line
		cellclear.bg = (RendAPIColorRGB ) WORLD_BG_BG;
		cellclear.shape = SHAPE_VOID;
		render->draw_buff(cellclear);
	}
	g_memory.len = 0;
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
		cell->shape = SHAPE_CIRCLE;
		break;
	}

}


void snk_pres_rend(SNK_GAME_STATE *gamestate){//new
	Snk2 *snake = &gamestate->snk2;
	int head = snake->head;
	int tail = snake->tail;
	int len = snake->len;

	RendAPIDrawInstructions cell;
	cell.pos.x = snake->body[tail].x;
	cell.pos.y = snake->body[tail].y;

	if(len == 1){
		set_cell_style(&cell, CELL_HEAD);
		render->draw_buff(cell);
	}

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

	render->render_frame();

}

void snk_pres_render_state() {
	Element head = g_gamestate->snk.parts[0];
	Element food = g_gamestate->food;

	clear_old_drawn();

	g_memory.buff[0] = head;
	g_memory.len = 1;
	//g_memory.elements[1] = head;
	for (int i = 1; i < g_gamestate->snk.len; i++) {

	}

	RendAPIDrawInstructions cell;
	cell.pos.x = head.pos.x;
	cell.pos.y = head.pos.y;
	cell.fg = (RendAPIColorRGB ) { .r = 24, .g = 34, .b = 255 };
	cell.bg = (RendAPIColorRGB ) { .r = 100, .g = 150, .b = 255 };
	cell.shape = SHAPE_CIRCLE;
	render->draw_buff(cell);
	cell.pos.x = food.pos.x;
	cell.pos.y = food.pos.y;
	cell.fg = (RendAPIColorRGB ) { .r = 255, .g = 34, .b = 0 };
	cell.bg = (RendAPIColorRGB ) { .r = 0, .g = 255, .b = 0 };
	cell.shape = SHAPE_HASH;
	render->draw_buff(cell);

	render->render_frame();

}
