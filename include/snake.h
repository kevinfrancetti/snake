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
#define SNK_MAX_LEN		100


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
	ELEMENT_SNK_HEAD,
	ELEMENT_SNK_BODY,
	ELEMENT_PLAYER
}ELEMENT_TYPE;

typedef struct{
	int x;
	int y;
}Position;


typedef struct{
	int				ID;
	Position		pos;
	ELEMENT_TYPE 	elem_type;
}Element;

typedef struct{
	Element			body[SNK_MAX_LEN];
	int				head;
	int				len;
	int				tail;
	SNK_DIRECTION	direction;
}Snake;

typedef struct{
	int				width;
	int				height;
	Snake			snk;
	//Element			map_of_stuff[100];
	Element			food;
}SNK_GAME_STATE;


void snk_game_init(void);
void snk_game_update(SNAKE_CMD);
SNK_GAME_STATE* snk_game_get_state(void);






#endif /* INCLUDE_SNAKE_H_ */
