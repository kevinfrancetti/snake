/*
 * render_api_test.c
 *
 *  Created on: Oct 18, 2026
 *      Author: bomber
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "render_api.h"
#include "render_factory.h"
#include "sort_test.h"

#define BUF_SIZE	2


typedef uint32_t Entity;

#define CA_SIZE 80




typedef enum {
	DEAD, ALIVE
} CA_Cell;

typedef struct {
	CA_Cell buf1[CA_SIZE];
	CA_Cell buf2[CA_SIZE];
	CA_Cell *curr_buf;
} CA; //CA:=Cellular Automata

CA_Cell rule01[2][2] = {
		[DEAD][DEAD] = ALIVE,
		[DEAD][ALIVE] = ALIVE,
		[ALIVE][DEAD] = DEAD,
		[ALIVE][ALIVE] = DEAD,
};


CA_Cell rule1(const CA_Cell *cells, int size, int index, CA_Cell (*rules)[2]) {
	CA_Cell l = cells[(index + size - 1) % size];
	CA_Cell r = cells[(index + 1) % size];
	return rules[l][r];
}


/**
 *
 * l c r :  111 110 101 100 011 010 001 000
 * nuovo :   0   0   0   1   1   1   1   0     <- è 00011110 = 30
 *
 */
CA_Cell rule_wolfram(const CA_Cell *cells, int size, int index, uint8_t rule){
	CA_Cell l = cells[(index + size - 1) % size];
	CA_Cell c = cells[index];
	CA_Cell r = cells[(index + 1) % size];
	return (rule >> (l << 2) | (c << 1) | r ) & 1;
}

void init_creatures(CA *ca, int size) {
	ca->curr_buf = ca->buf1;
	for (int i = 0; i < size; i++) {
		ca->curr_buf[i] = DEAD;
	}
	//ca->curr_buf[0] = ALIVE;
	ca->curr_buf[20] = ALIVE;
}

void print_creatues(CA *ca, int size) {
	for (int i = 0; i < size; i++) {
		if (ca->curr_buf[i] == DEAD) {
			printf(" ");
		} else
			printf("#");
	}
	printf("\n");
}

void update_creatures(CA *ca, int size) {
	CA_Cell *new;
	if (ca->curr_buf != ca->buf1) {
		new = ca->buf1;
	} else
		new = ca->buf2;

	for (int i = 0; i < size; i++) {
		//new[i] = rule1(ca->curr_buf, size, i, rule01);
		new[i] = rule_wolfram(ca->curr_buf, size, i, 30);
	}
	ca->curr_buf = new;
}


void print_array(int *array, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d,", array[i]);
	}
	printf("\n");
}

void render_CA(RenderAPI *render, int *array, int size) {
	static int cnt = 0;
	RendAPIDrawInstructions cell;
	//cnt++;
	cell.pos.y = 5;
	cell.fg = (RendAPIColorRGB ) { 0, 0, 0 };
	cell.bg = (RendAPIColorRGB ) { 0, 0, 0 };
	cell.shape = SHAPE_CIRCLE; //TODO seg fault investigate
	for (int i = 0; i < size; i++) {
		cell.pos.x = i;
		render->draw_buff(cell);
	}
	render->render_frame();
}

void render_array01(RenderAPI *render, int *array, int size) {
	static int cnt = 0;
	RendAPIDrawInstructions cell;
	//cnt++;
	cell.pos.y = 5;
	cell.fg = (RendAPIColorRGB ) { 0, 0, 0 };
	cell.bg = (RendAPIColorRGB ) { 0, 0, 0 };
	cell.shape = SHAPE_CIRCLE; //TODO seg fault investigate
	int step = (255 / (size - 1));
	for (int i = 0; i < size; i++) {
		cell.bg.r = step * array[i];
		cell.bg.g = 255 - (step * array[i]);
		cell.pos.x = i;
		render->draw_buff(cell);
	}
	render->render_frame();
}


void test_bubble_sort_and_render() {
	srand(135);
	int size = 40;
	int array1[size];

	RenderAPI render = render_create(RENDER_TERMINAL);

	for (int i = 0; i < size; i++) {
		array1[i] = rand() % size;
	}

	BubbleSortState state = { 0, 0 };

	do {
		render_array01(&render, array1, size);
		usleep(1000 * 10);
	} while (!atomic_bubble_sort(&state, array1, size));
}

int main() {

	//test_bubble_sort_and_render();

	CA ca;
	init_creatures(&ca, CA_SIZE);
	print_creatues(&ca, CA_SIZE);
	update_creatures(&ca, CA_SIZE);
	print_creatues(&ca, CA_SIZE);
	int i = 0;
	do {
		update_creatures(&ca, CA_SIZE);
		print_creatues(&ca, CA_SIZE);
		usleep(1000 * 1000);
	} while (i++ < 100);


	return 0;
}



