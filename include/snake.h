/*
 * logic.h
 *
 *  Created on: Sep 13, 2026
 *      Author: bomber
 */

#ifndef INCLUDE_SNAKE_H_
#define INCLUDE_SNAKE_H_

#define GAME_MAP_WIDTH	90
#define GAME_MAP_HEIGHT	30

#define SNK_MAX_LEN		20


typedef enum{
	SNK_CMD_NONE,
	SNK_CMD_UP,
	SNK_CMD_DOWN,
	SNK_CMD_LEFT,
	SNK_CMD_RIGHT
}SNAKE_CMD;

typedef enum{
	SNK_UP,
	SNK_DOWN,
	SNK_LEFT,
	SNK_RIGHT
}SNK_DIRECTION;

typedef enum{
	ELEMENT_WALL,
	ELEMENT_FOOD,
	ELEMENT_SNK_PART,
	ELEMENT_SNK,
	ELEMENT_PLAYER
}ELEMENT_TYPE;

typedef struct{
	int x;
	int y;
}Position;

typedef struct{
	Position		pos;
	ELEMENT_TYPE 	elem_type;
}Element;

typedef struct{
	Position		body[SNK_MAX_LEN];
	int				head;
	int				len;
	int				tail;
	SNK_DIRECTION	direction;
	ELEMENT_TYPE	type;
}Snake;

typedef struct{
	int				width;
	int				height;
	Snake			snk;
	//Element			map_of_stuff[100];
	Element			food;
}SNK_GAME_STATE;

SNK_GAME_STATE snk_init(void);//new
void snk_update(SNK_GAME_STATE *gamestate, SNAKE_CMD cmd);//new


#endif /* INCLUDE_SNAKE_H_ */
