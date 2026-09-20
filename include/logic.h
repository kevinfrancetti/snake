/*
 * logic.h
 *
 *  Created on: Sep 13, 2026
 *      Author: bomber
 */

#ifndef INCLUDE_LOGIC_H_
#define INCLUDE_LOGIC_H_


typedef enum{
	ACTION_NONE,
	ACTION_UP,
	ACTION_DOWN,
	ACTION_LEFT,
	ACTION_RIGHT
}ACTION_TYPE;



void init();
void game_update(ACTION_TYPE);
int getX();
int getY();


typedef struct{
	int x;
	int y;
}Position;


typedef struct{
	int ID;
	Position pos;
}Player;



#endif /* INCLUDE_LOGIC_H_ */
