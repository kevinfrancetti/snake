/*
 * logic.c
 *
 *  Created on: Sep 13, 2026
 *      Author: bomber
 */

#include <stdio.h>
#include <stdlib.h>
#include "snake.h"
#include "debug.h"

Element*		p_snk_head;
SNK_GAME_STATE	state;


void snk_game_init() {
	srand(2);
	state.snk.head				= 0;
	state.snk.tail				= 0;
	state.snk.len				= 1;

	p_snk_head					= &state.snk.body[state.snk.head];

	p_snk_head->pos.x			= 5;
	p_snk_head->pos.y			= 5;
	p_snk_head->elem_type		= ELEMENT_SNK_HEAD;


	state.snk.direction			= SNK_RIGHT;

	state.height				= GAME_MAP_HEIGHT;
	state.width					= GAME_MAP_WIDTH;

	state.food.pos.x			= rand()%GAME_MAP_WIDTH;
	state.food.pos.y			= rand()%GAME_MAP_HEIGHT;
	state.food.elem_type		= ELEMENT_FOOD;
}

void test(){

}

void snk_update2(SNAKE_CMD type){
	Element futurehead = state.snk.body[state.snk.head];


	// @formatter:off
	if(type == SNK_CMD_NONE){
		switch(state.snk.direction){
		case SNK_UP:	type = SNK_CMD_UP; break;
		case SNK_DOWN:	type = SNK_CMD_DOWN; break;
		case SNK_LEFT:	type = SNK_CMD_LEFT; break;
		case SNK_RIGHT:	type = SNK_CMD_RIGHT; break;
		}
	}
	// @formatter:on


	switch (type) {

	case SNK_CMD_LEFT:
		state.snk.direction = SNK_LEFT;
		futurehead.pos.x--;
		break;
	case SNK_CMD_RIGHT:
		state.snk.direction = SNK_RIGHT;
		futurehead.pos.x++;
		break;
	case SNK_CMD_UP:
		state.snk.direction = SNK_UP;
		futurehead.pos.y++;
		break;
	case SNK_CMD_DOWN:
		state.snk.direction = SNK_DOWN;
		futurehead.pos.y--;
		break;
	default:
		fprintf(stderr, "switch case default\n");
		break;
	}

	//TODO remove all this shit and this shit function
	state.snk.body[state.snk.head].elem_type = ELEMENT_SNK_BODY;//old head change type
	state.snk.head = (state.snk.head + 1) % SNK_MAX_LEN;





}

void snk_game_update(SNAKE_CMD type) {

	// @formatter:off
	if(type == SNK_CMD_NONE){
		switch(state.snk.direction){
		case SNK_UP:	type = SNK_CMD_UP; break;
		case SNK_DOWN:	type = SNK_CMD_DOWN; break;
		case SNK_LEFT:	type = SNK_CMD_LEFT; break;
		case SNK_RIGHT:	type = SNK_CMD_RIGHT; break;
		}
	}
	// @formatter:on



	switch (type) {

	case SNK_CMD_LEFT:
		state.snk.direction = SNK_LEFT;
		p_snk_head->pos.x--;
		break;
	case SNK_CMD_RIGHT:
		state.snk.direction = SNK_RIGHT;
		p_snk_head->pos.x++;
		break;
	case SNK_CMD_UP:
		state.snk.direction = SNK_UP;
		p_snk_head->pos.y++;
		break;
	case SNK_CMD_DOWN:
		state.snk.direction = SNK_DOWN;
		p_snk_head->pos.y--;
		break;
	default:
		fprintf(stderr, "switch case default\n");
		break;
	}

	//Check collision with food
	if(p_snk_head->pos.x == state.food.pos.x && p_snk_head->pos.y == state.food.pos.y){
		state.food.pos.x			= rand()%GAME_MAP_WIDTH;
		state.food.pos.y			= rand()%GAME_MAP_HEIGHT;
	}


	fprintf(stderr, "p1.pos.x = %d\np1.pos.yfefef = %d\n", p_snk_head->pos.x,
			p_snk_head->pos.y);
}

SNK_GAME_STATE* snk_game_get_state(void){
	return &state;
}



