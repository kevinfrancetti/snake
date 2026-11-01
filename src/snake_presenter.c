/*
 * snake_presenter.c
 *
 *  Created on: Oct 6, 2026
 *      Author: bomber
 */

#include "snake_presenter.h"

#define SP_RGB(red, green, blue)	{ .r = red, .g = green, .b = blue }

#define WORLD_BG_BG			SP_RGB(0, 100, 100)

#define WORLD_BG_EDGE 		SP_RGB(255, 0, 255)
#define WORLD_FG_EDGE		SP_RGB(0, 255, 0)

static RenderAPI *render;
static SNK_GAME_STATE *snk_game_state;

typedef struct {
	Element body[100];
	int len;
} DrawMemory;

static DrawMemory g_memory;
static DrawMemory next;

void snk_pres_first_draw() {
	RendAPIDrawInstructions cell;

	for (int y = 1; y < snk_game_state->height; y++) {
		for (int x = 1; x < snk_game_state->width; x++) {
			cell.pos.x = x;
			cell.pos.y = y;
			if (y == 1 || x == 1 || y == snk_game_state->height - 1
					|| x == snk_game_state->width - 1) {
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

void snk_pres_init(RenderAPI *rend, SNK_GAME_STATE *state) {
	render = rend;
	snk_game_state = state;
	snk_pres_first_draw();
}

void clear_old_drawn() {
	RendAPIDrawInstructions cellclear;

	for (int i = 0; i < g_memory.len; i++) {
		cellclear.pos.x = g_memory.body[i].pos.x;
		cellclear.pos.y = g_memory.body[i].pos.y;
		cellclear.fg = (RendAPIColorRGB ) { .r = 0, .g = 0, .b = 0 };
		cellclear.bg = (RendAPIColorRGB ) WORLD_BG_BG;
		cellclear.shape = SHAPE_VOID;
		render->draw_buff(cellclear);
	}
	g_memory.len = 0;
}

void snk_pres_render_state() {
	Element head = snk_game_state->snk.body[0];
	Element food = snk_game_state->food;

	clear_old_drawn();

	g_memory.body[0] = head;
	g_memory.len = 1;
	//g_memory.elements[1] = head;
	for (int i = 1; i < snk_game_state->snk.len; i++) {

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
