/*
 * logic.c
 *
 *  Created on: Sep 13, 2026
 *      Author: bomber
 */

#include <snake.h>
#include <stdio.h>

// @formatter:off
Player p1 = {
		.ID = 1,
		.pos = { GAME_MAP_WIDTH / 2, GAME_MAP_HEIGHT / 2 },
		.elem_type = ELEMENT_PLAYER
};
// @formatter:on

static void check_boundaries() {

}

void game_update(SNAKE_CMD type) {
	switch (type) {
	case SNK_CMD_NONE:
		return;
	case SNK_CMD_LEFT:
		p1.pos.x--;
		break;
	case SNK_CMD_RIGHT:
		p1.pos.x++;
		break;
	case SNK_CMD_UP:
		p1.pos.y++;
		break;
	case SNK_CMD_DOWN:
		p1.pos.y--;
		break;
		break;
	default:
		fprintf(stderr, "switch case default\n");
		break;
	}

	fprintf(stderr, "p1.pos.x = %d\np1.pos.y = %d\n", p1.pos.x, p1.pos.y);
}

int getX() {
	return p1.pos.x;
}
int getY() {
	return p1.pos.y;
}
void init() {
	p1.ID = 0;
	p1.pos.x = 5;
	p1.pos.y = 5;
}

