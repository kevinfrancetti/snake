/*
 * logic.c
 *
 *  Created on: Sep 13, 2026
 *      Author: bomber
 */

#include "logic.h"

Player p1;


void update(int instruction){

	switch (instruction) {
		case UP:
			printf("up\n");
			break;
		case DOWN:
			printf("down\n");
			break;
		default:
			printf("default\n");
			break;
	}


}



void init(){
	p1.ID = 0;
	p1.pos.x = 5;
	p1.pos.y = 5;
}

