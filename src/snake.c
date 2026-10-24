/*
 * logic.c
 *
 *  Created on: Sep 13, 2026
 *      Author: bomber
 */

#include <snake.h>
#include <stdio.h>


Element*		ptr_snk_head;
SNK_GAME_STATE	state;


void snake_game_init() {
	ptr_snk_head				= &state.snake.components[0];

	ptr_snk_head->pos.x			= 5;
	ptr_snk_head->pos.y			= 5;
	ptr_snk_head->elem_type		= ELEMENT_SNK_HEAD;

	state.snake.size			= 1;
	state.height				= GAME_MAP_HEIGHT;
	state.width					= GAME_MAP_WIDTH;
}


void game_update(SNAKE_CMD type) {
	switch (type) {
	case SNK_CMD_NONE:
		return;
	case SNK_CMD_LEFT:
		ptr_snk_head->pos.x--;
		break;
	case SNK_CMD_RIGHT:
		ptr_snk_head->pos.x++;
		break;
	case SNK_CMD_UP:
		ptr_snk_head->pos.y++;
		break;
	case SNK_CMD_DOWN:
		ptr_snk_head->pos.y--;
		break;
	default:
		fprintf(stderr, "switch case default\n");
		break;
	}

	fprintf(stderr, "p1.pos.x = %d\np1.pos.yfefef = %d\n", ptr_snk_head->pos.x,
			ptr_snk_head->pos.y);
}

SNK_GAME_STATE* snake_game_get_state(void){
	return &state;
}

int getX() {
	return ptr_snk_head->pos.x;
}
int getY() {
	return ptr_snk_head->pos.y;
}


