/*
 * generic_test.c
 *
 *  Created on: Nov 2, 2026
 *      Author: bomber
 */

#include <stdio.h>
#include <stdbool.h>
#include "debug.h"

#define SIZE 4

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
	Position p;
	if(cb->len == 0){
		DEBUG1s1i("buff empty", 0);
		return (Position) {-1,-1};
	}
	if(cb->len == 1){
		p = cb->buff[cb->tail];
		cb->len--;
		return (Position) {-1,-1};
	}
	p = cb->buff[cb->tail];
	cb->tail = (cb->tail + 1) % SIZE;
	cb->len--;
	return p;
}

//for snake
void move(CyclicBuff *cb, Position p){
	cb->head = (cb->head + 1) % SIZE;
	cb->buff[cb->head] = p;
	cb->tail = (cb->tail + 1) % SIZE;
}

void test01(){
	int a = 0;
	printf("A: %d \n", 5-0%5);
	printf("A: %d \n", 0-1%5);
	printf("A: %d \n", 5-2%5);
	printf("A: %d \n", 5-3%5);
	printf("A: %d \n", 5-4%5);
	printf("A: %d \n", 5-5%5);

}

int main() {

	test01();

	/*
	CyclicBuff cb = create_cyclicBuff();
	Position p = { .x = 5, .y = 1 };

	for(int i = 0; i < 2; i++){
		push(&cb, p);
		move(&cb, (Position) {1,2});
		if(i >= 0){
			for(int j = 0; j < 5; j++){
				pop(&cb);
			}
		}
	}
	move(&cb, (Position) {1,2});
	printf("HERE!\n");
	pop(&cb);
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
	*/
	return 0;
}
