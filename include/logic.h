/*
 * logic.h
 *
 *  Created on: Sep 13, 2026
 *      Author: bomber
 */

#ifndef INCLUDE_LOGIC_H_
#define INCLUDE_LOGIC_H_

#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3



void init();
void update(int instruction);


typedef struct{
	int x;
	int y;
}Position;


typedef struct{
	int ID;
	Position pos;
}Player;



#endif /* INCLUDE_LOGIC_H_ */
