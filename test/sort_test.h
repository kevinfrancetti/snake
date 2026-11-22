/*
 * sort_test.h
 *
 *  Created on: Nov 22, 2026
 *      Author: bomber
 */

#ifndef TEST_SORT_TEST_H_
#define TEST_SORT_TEST_H_

#include <stdbool.h>

//SORTING TEST
typedef struct {
	int swap_cnt;
	int index;
} BubbleSortState;

bool atomic_bubble_sort(BubbleSortState *self, int *array, int size);
bool bubble_sort(int *array, int size, bool stepbystep);

#endif /* TEST_SORT_TEST_H_ */
