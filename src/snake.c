/*
 * logic.c
 *
 *  Created on: Sep 13, 2026
 *      Author: bomber
 *
 *      This snake game is implemented with a circular buffer. The presenter can use this
 *      information for a better implementation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "snake.h"
#include "debug.h"

SNK_GAME_STATE snk_init() {
	srand(1);
	// @formatter:off
	SNK_GAME_STATE gamestate = {
			.width	= GAME_MAP_WIDTH,
			.height	= GAME_MAP_HEIGHT,
			.snk2	= {
					.body[0].x = 6,
					.body[0].y = 6,
					.head	= 0,
					.tail	= 0,
					.len	= 1,
					.direction = SNK_RIGHT,
					.type	= ELEMENT_SNK
			},
			.food = {
					.pos = {
							.x = rand()%GAME_MAP_WIDTH,
							.y = rand()%GAME_MAP_HEIGHT
					},
					.elem_type = ELEMENT_FOOD
			},
	};
		// @formatter:on
	return gamestate;
}


/**
 * Snake ate something
 */
static bool push(Snk2 *snake, Position *newhead){
	if(snake->len >= SNK_MAX_LEN){
		DEBUG1s1i("snake buff full", 0);
		return false;
	}
	if(snake->len == 0){
		snake->body[snake->head] = *newhead;
		snake->len++;
		return true;
	}
	snake->head = (snake->head + 1) % SNK_MAX_LEN;
	snake->body[snake->head] = *newhead;
	snake->len++;
	return true;
}

static bool pop(Snk2 *snake, Position *newhead){
	if(snake->len == 0){
		DEBUG1s1i("snake buff empty", 0);
		return false;
	}
	if(snake->len == 1){
		*newhead = snake->body[snake->tail];
		snake->len--;
		return true;
	}
	*newhead = snake->body[snake->tail];
	snake->tail= (snake->tail + 1) % SNK_MAX_LEN;
	snake->len--;
	return false;
}

//
/**
 * Normal move (no eat) the snake and push the new head in front
 *
 * For the presenter:
 * return the last position so it's easy for the presenter to remove the cell
 */
static Position move(Snk2 *snake, Position *newhead){
	if(snake->len == 0) {
		return (Position) {-1, -1};//error pos
	}

	Position lasttail = snake->body[snake->tail];
	snake->head = (snake->head + 1) % SNK_MAX_LEN;
	snake->body[snake->head] = *newhead;
	snake->tail= (snake->tail + 1) % SNK_MAX_LEN;
	return lasttail;
}

void snk_update(SNK_GAME_STATE *gamestate, SNAKE_CMD cmd){
	Snk2 *snake = &gamestate->snk2;

	// @formatter:off
	if(cmd == SNK_CMD_NONE){
		switch(snake->direction){
		case SNK_UP:	cmd = SNK_CMD_UP; break;
		case SNK_DOWN:	cmd = SNK_CMD_DOWN; break;
		case SNK_LEFT:	cmd = SNK_CMD_LEFT; break;
		case SNK_RIGHT:	cmd = SNK_CMD_RIGHT; break;
		}
	}
	// @formatter:on

	Position snakehead = snake->body[snake->head];

	switch (cmd) {

	case SNK_CMD_LEFT:
		snake->direction = SNK_LEFT;
		snakehead.x -= 1;
		break;
	case SNK_CMD_RIGHT:
		snake->direction = SNK_RIGHT;
		snakehead.x += 1;
		break;
	case SNK_CMD_UP:
		snake->direction = SNK_UP;
		snakehead.y += 1;
		break;
	case SNK_CMD_DOWN:
		snake->direction = SNK_DOWN;
		snakehead.y -= 1;
		break;
	default:
		fprintf(stderr, "switch case default\n");
		break;
	}

	if(snakehead.x == gamestate->food.pos.x && snakehead.y == gamestate->food.pos.y){
		gamestate->food.pos.x = rand()%GAME_MAP_WIDTH;
		gamestate->food.pos.y = rand()%GAME_MAP_HEIGHT;
		push(&gamestate->snk2, &snakehead);
	}else{
		move(snake, &snakehead);
	}



}

//Check collision with food
/*
if(p_snk_head->pos.x == gs.food.pos.x && p_snk_head->pos.y == gs.food.pos.y){
	gs.food.pos.x			= rand()%GAME_MAP_WIDTH;
	gs.food.pos.y			= rand()%GAME_MAP_HEIGHT;
}
*/




