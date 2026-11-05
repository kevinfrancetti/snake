/*
 * generic_test.c
 *
 *  Created on: Nov 2, 2026
 *      Author: bomber
 */

#include <stdio.h>
#include "debug.h"

#define SIZE 3






typedef struct {
	int x;
	int y;
} Position;

typedef struct CyclicBuff CyclicBuff;

struct CyclicBuff{
	Position buff[SIZE];
	int head;
	int tail;
	int len;
	void (*push)(CyclicBuff* self, Position pos);
	Position (*pop)(CyclicBuff* self);
};

void push(CyclicBuff *cb, Position p);
Position pop(CyclicBuff *cb);


CyclicBuff create_cyclicBuff() {
	CyclicBuff cb = { .buff = { }, .head = 0, .tail = 0, .len = 0 };
	cb.push = push;
	cb.pop = pop;
	return cb;
}

//snake like push_normal, a real cb only head++
void push(CyclicBuff *cb, Position p) {
	if(cb->len == SIZE){
		DEBUG1s1i("buff full\n",0);
		return;
	}
	if(cb->len == 0){
		cb->buff[cb->head] = p;
		cb->len++;
		//cb->head = (cb->head + 1) % SIZE;
		return;
	}
	cb->head = (cb->head + 1) % SIZE;
	cb->buff[cb->head] = p;
	cb->len++;
	//cb->tail++;
	//cb->len++;
}

Position pop(CyclicBuff *cb) {
	Position p = cb->buff[cb->tail];
	cb->tail = (cb->tail + 1) % SIZE;
	cb->len--;
	return p;
}

//for snake
void move(CyclicBuff *cb, Position p){
	push(cb, p);
	pop(cb);
}

int main() {
	CyclicBuff cb = create_cyclicBuff();
	Position p = { .x = 5, .y = 1 };
	push(&cb, p);
	p.x = 22;
	p.y = 99;
	push(&cb, p);
	p.y = 572;
	push(&cb, p);
	push(&cb, p);
	pop(&cb);
	p.x = 666;
	push(&cb, p);
	p.x = 6644;
	move(&cb, p);
	printf("porco dio\n");
	return 0;
}
