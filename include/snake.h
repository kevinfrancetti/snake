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
	ACTION_NONE,
	ACTION_UP,
	ACTION_DOWN,
	ACTION_LEFT,
	ACTION_RIGHT
}SNAKE_ACTION;


typedef enum{
	ELEMENT_WALL,
	ELEMENT_FOOD,
	ELEMENT_PLAYER
}ELEMENT_TYPE;



void init();
void game_update(SNAKE_ACTION);
int getX();
int getY();


typedef struct{
	int x;
	int y;
}Position;


typedef struct{
	int ID;
	Position pos;
	ELEMENT_TYPE elem_type;
}Player;



#endif /* INCLUDE_SNAKE_H_ */
