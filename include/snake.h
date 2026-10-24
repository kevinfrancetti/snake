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


typedef enum{
	SNK_CMD_NONE,
	SNK_CMD_UP,
	SNK_CMD_DOWN,
	SNK_CMD_LEFT,
	SNK_CMD_RIGHT
}SNAKE_CMD;


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
	Element			components[100];
	int				size;
}SNAKE;

typedef struct{
	int				width;
	int				height;
	int				snk_size;
	int				map_size;
	SNAKE			snake;
	Element			map_of_stuff[100];
}SNK_GAME_STATE;


void snake_game_init(void);
void game_update(SNAKE_CMD);
SNK_GAME_STATE* snake_game_get_state(void);
int getX(void);
int getY(void);






#endif /* INCLUDE_SNAKE_H_ */
