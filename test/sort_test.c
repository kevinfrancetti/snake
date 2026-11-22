/*
 * sort_test.c
 *
 *  Created on: Nov 22, 2026
 *      Author: bomber
 */

#include <stdbool.h>

#include "sort_test.h"

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
