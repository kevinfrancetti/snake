/*
 * logic.c
 *
 *  Created on: Sep 13, 2026
 *      Author: bomber
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "snake.h"
#include "debug.h"


SNK_GAME_STATE	gs;
Element*		p_snk_head;


SNK_GAME_STATE snk_init(){
	// @formatter:off
	SNK_GAME_STATE gamestate = {
			.width	= GAME_MAP_WIDTH,
			.height	= GAME_MAP_HEIGHT,
			.snk2	= {
					.head	= 0,
					.tail	= 0,
					.len	= 0,
					.direction = SNK_RIGHT,
					.type	= ELEMENT_SNK
			},
	};
	// @formatter:on
	return gamestate;
}


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
	snake->len++;
	return false;
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

//return the last position so it's easy for the presenter to remove the cell
Position move(Snk2 *snake, Position *newhead){
	if(snake->len == 0) {
		return (Position) {-1, -1};
	}

	Position lasttail = snake->body[snake->tail];
	snake->head = (snake->head + 1) % SNK_MAX_LEN;
	snake->body[snake->head] = *newhead;
	snake->tail= (snake->tail + 1) % SNK_MAX_LEN;
	return lasttail;
}

void snk_update(SNK_GAME_STATE gamestate, SNAKE_CMD cmd){
	Snk2 *snake = &gamestate.snk2;

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

	Position headpos = snake->body[snake->head];

	switch (cmd) {

	case SNK_CMD_LEFT:
		snake->direction = SNK_LEFT;
		headpos.x -= 1;
		break;
	case SNK_CMD_RIGHT:
		snake->direction = SNK_RIGHT;
		headpos.x += 1;
		break;
	case SNK_CMD_UP:
		snake->direction = SNK_UP;
		headpos.y += 1;
		break;
	case SNK_CMD_DOWN:
		snake->direction = SNK_DOWN;
		headpos.y -= 1;
		break;
	default:
		fprintf(stderr, "switch case default\n");
		break;
	}

	move(snake, &headpos);

}


void snk_game_init() {
	srand(2);
	gs.snk.head				= 0;
	gs.snk.tail				= 0;
	gs.snk.len				= 1;
	p_snk_head				= &gs.snk.parts[gs.snk.head];

	/*
	p_snk2							= &gamestate.snk2;
	p_snk2->head					= 0;
	p_snk2->tail					= 0;
	p_snk2->len						= 1;

	p_snk2->body[p_snk2->head].x 	= 6;
	p_snk2->body[p_snk2->head].y 	= 6;
	p_snk2->type					= ELEMENT_SNK;
	*/

	p_snk_head->pos.x		= 5;
	p_snk_head->pos.y		= 5;
	p_snk_head->elem_type	= ELEMENT_SNK_PART;


	gs.snk.direction		= SNK_RIGHT;

	gs.height				= GAME_MAP_HEIGHT;
	gs.width				= GAME_MAP_WIDTH;

	gs.food.pos.x			= rand()%GAME_MAP_WIDTH;
	gs.food.pos.y			= rand()%GAME_MAP_HEIGHT;
	gs.food.elem_type		= ELEMENT_FOOD;
}

void test_update(Snake* snake, SNAKE_CMD cmd){

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

	int x = snake->parts[snake->head].pos.x;
	int y = snake->parts[snake->head].pos.y;

	Position p;
	switch (cmd) {

	case SNK_CMD_LEFT:
		snake->direction = SNK_LEFT;
		p.x = x - 1;
		p.y = y;

		break;
	case SNK_CMD_RIGHT:
		gs.snk.direction = SNK_RIGHT;


		break;
	case SNK_CMD_UP:
		gs.snk.direction = SNK_UP;


		break;
	case SNK_CMD_DOWN:
		gs.snk.direction = SNK_DOWN;


		break;
	default:
		fprintf(stderr, "switch case default\n");
		break;
	}

}

void snk_update2(SNAKE_CMD type){
	Element head = gs.snk.parts[gs.snk.head];


	// @formatter:off
	if(type == SNK_CMD_NONE){
		switch(gs.snk.direction){
		case SNK_UP:	type = SNK_CMD_UP; break;
		case SNK_DOWN:	type = SNK_CMD_DOWN; break;
		case SNK_LEFT:	type = SNK_CMD_LEFT; break;
		case SNK_RIGHT:	type = SNK_CMD_RIGHT; break;
		}
	}
	// @formatter:on

	Position p;
	switch (type) {

	case SNK_CMD_LEFT:
		gs.snk.direction = SNK_LEFT;
		p.x = gs.snk.parts[gs.snk.head].pos.x - 1;


		break;
	case SNK_CMD_RIGHT:
		gs.snk.direction = SNK_RIGHT;


		break;
	case SNK_CMD_UP:
		gs.snk.direction = SNK_UP;


		break;
	case SNK_CMD_DOWN:
		gs.snk.direction = SNK_DOWN;


		break;
	default:
		fprintf(stderr, "switch case default\n");
		break;
	}



}

void snk_game_update(SNAKE_CMD cmd) {

	// @formatter:off
	if(cmd == SNK_CMD_NONE){
		switch(gs.snk.direction){
		case SNK_UP:	cmd = SNK_CMD_UP; break;
		case SNK_DOWN:	cmd = SNK_CMD_DOWN; break;
		case SNK_LEFT:	cmd = SNK_CMD_LEFT; break;
		case SNK_RIGHT:	cmd = SNK_CMD_RIGHT; break;
		}
	}
	// @formatter:on



	switch (cmd) {

	case SNK_CMD_LEFT:
		gs.snk.direction = SNK_LEFT;
		p_snk_head->pos.x--;
		break;
	case SNK_CMD_RIGHT:
		gs.snk.direction = SNK_RIGHT;
		p_snk_head->pos.x++;
		break;
	case SNK_CMD_UP:
		gs.snk.direction = SNK_UP;
		p_snk_head->pos.y++;
		break;
	case SNK_CMD_DOWN:
		gs.snk.direction = SNK_DOWN;
		p_snk_head->pos.y--;
		break;
	default:
		fprintf(stderr, "switch case default\n");
		break;
	}

	//Check collision with food
	if(p_snk_head->pos.x == gs.food.pos.x && p_snk_head->pos.y == gs.food.pos.y){
		gs.food.pos.x			= rand()%GAME_MAP_WIDTH;
		gs.food.pos.y			= rand()%GAME_MAP_HEIGHT;
	}


	fprintf(stderr, "p1.pos.x = %d\np1.pos.y = %d\n", p_snk_head->pos.x,
			p_snk_head->pos.y);
}

SNK_GAME_STATE* snk_game_get_state(void){
	return &gs;
}



