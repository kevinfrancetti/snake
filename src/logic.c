/*
 * logic.c
 *
 *  Created on: Sep 13, 2026
 *      Author: bomber
 */

#include <stdio.h>
#include "logic.h"

Player p1 = { .ID = 1, .pos = { 1, 2 } };


void game_update(ACTION_TYPE type) {
	switch (type) {
	case ACTION_NONE:
		return;
	case ACTION_LEFT:
		p1.pos.x--;
		break;
	case ACTION_RIGHT:
		p1.pos.x++;
		break;
	case ACTION_UP:
		p1.pos.y++;
		break;
	case ACTION_DOWN:
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

