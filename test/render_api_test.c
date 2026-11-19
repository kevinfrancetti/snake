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

#define BUF_SIZE	2

/*
 RendAPIDrawInstructions g_cells1[BUF_SIZE];
 RendAPIDrawInstructions g_cells2[BUF_SIZE];
 RendAPIDrawInstructions *g_ptr_cells;

 void init_cells(RendAPIDrawInstructions *cells, int size) {
 for (int i = 0; i < size; i++) {
 (cells + i)->pos.x = i;
 (cells + i)->pos.y = 5;
 (cells + i)->bg = (RendAPIColorRGB ) { .r = 0, .g = 0, .b = 255 };
 }
 }

 void rend_cells(RenderAPI *render, RendAPIDrawInstructions *cells, int size) {
 for (int i = 0; i < size; i++) {
 render->draw_buff(cells[i]);
 }
 render->render_frame();
 }

 void update_cells() {

 }
 */

typedef uint32_t Entity;

#define NUM_CREATURES 10




typedef enum {
	DEAD, ALIVE
} State;

typedef struct {
	State buf1[NUM_CREATURES];
	State buf2[NUM_CREATURES];
	State *states;
} CA; //CA:=Cellular Automata

void rule1(const State *cells, int size, int index) {
	State l = cells[(index + size - 1) % size];
	State r = cells[(index + 1) % size];


}

void init_creatures(CA *ca, int size) {
	ca->states = ca->buf1;
	for (int i = 0; i < size; i++) {
		ca->states[i] = DEAD;
	}
	ca->states[0] = ALIVE;
	ca->states[2] = ALIVE;
}

void print_creatues(CA *ca, int size) {
	for (int i = 0; i < size; i++) {

		if (ca->states[i] == DEAD) {
			printf("D,");
		} else
			printf("A,");

	}
	printf("\n");
}

void update_creatures(CA *state, int size) {
	State *new;
	if (state->states != state->buf1) {
		new = state->buf1;
	} else
		new = state->buf2;

	for (int i = 0; i < size; i++) {
		new[i] = state->states[(i + size - 1) % size]; //prev creature
	}

	state->states = new;

}

//SORTING TEST
typedef struct {
	int swap_cnt;
	int index;
} BubbleSortState;

bool atomic_bubble_sort(BubbleSortState *self, int *array, int size) {
	if (array[self->index] > array[self->index + 1]) {
		self->swap_cnt++;
		int tmp = array[self->index];
		array[self->index] = array[self->index + 1];
		array[self->index + 1] = tmp;
	}
	self->index++;
	if (self->index == size - 1) {
		if (self->swap_cnt == 0) {
			self->index = 0;
			self->swap_cnt = 0;
			return true;
		} else {
			self->index = 0;
			self->swap_cnt = 0;
			return false;
		}
	}
	return false;
}

bool bubble_sort(int *array, int size, bool stepbystep) {
	int swap_cnt = 0;
	do {
		swap_cnt = 0;
		for (int i = 0; i < size - 1; i++) {
			if (array[i] > array[i + 1]) {
				swap_cnt++;
				int tmp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = tmp;
			}
		}
	} while (swap_cnt > 0 && !stepbystep);
	if (swap_cnt == 0)
		return true;
	else
		return false;
}

void print_array(int *array, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d,", array[i]);
	}
	printf("\n");
}

void render_array(RenderAPI *render, int *array, int size) {
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
//END SORTING TEST

typedef int (*ptr_fn)(void);

ptr_fn (*f)(int);

int func1(void) {
	return 0;
}

ptr_fn func2(int a) {
	printf("this is func: %d\n", a);
	return func1;
}

int main() {
	f = func2;
	int test = (*f)(7)();
	printf("test: %d\n", test);
	CA state[NUM_CREATURES];
	init_creatures(state, NUM_CREATURES);
	print_creatues(state, NUM_CREATURES);
	update_creatures(state, NUM_CREATURES);
	print_creatues(state, NUM_CREATURES);
	int i = 0;
	do {
		update_creatures(state, NUM_CREATURES);
		print_creatues(state, NUM_CREATURES);
		usleep(1000 * 1000);
	} while (i++ < 10);

	/*
	 RenderAPI render = render_create(RENDER_TERMINAL);
	 //ciao
	 init_cells(g_cells1, BUF_SIZE);
	 rend_cells(&render, g_cells1, BUF_SIZE);

	 RendAPIDrawInstructions cel;
	 cel.pos.x = 0;
	 cel.pos.y = 0;
	 cel.fg = (RendAPIColorRGB ) { .r = 24, .g = 34, .b = 255 };
	 cel.bg = (RendAPIColorRGB ) { .r = 255, .g = 0, .b = 0 };
	 cel.shape = SHAPE_CIRCLE;
	 render.draw_buff(cel);
	 cel.pos.x = 1;
	 cel.pos.y = 1;
	 render.draw_buff(cel);

	 cel.bg = (RendAPIColorRGB ) { .r = 0, .g = 255, .b = 255 };
	 cel.pos.x = 10;
	 render.draw_buff(cel);
	 render.render_frame();
	 render.clear_color((RendAPIColorRGB ) { 100, 0, 0 });
	 sleep(1);
	 //render.render_frame();
	 */

	/*
	 render.draw_cell(1, 1, SHAPE_CROSS);
	 render.draw_cell(1, 2, SHAPE_CIRCLE);
	 render.draw_cell(2, 1, SHAPE_CROSS);
	 render.draw_cell(2, 2, SHAPE_CIRCLE);
	 */

	//render.draw_cell(1, 1, SHAPE_CROSS);
	//render.draw_cell(4, 5, SHAPE_CROSS);
	return 0;
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
		//	print_array(array1, size);
		render_array(&render, array1, size);
		usleep(1000 * 10);
	} while (!atomic_bubble_sort(&state, array1, size));

	/*
	 do {
	 print_array(array1, size);
	 } while (!bubble_sort(array1, size, true));
	 */

}

