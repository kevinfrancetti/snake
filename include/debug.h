/*
 * debug.h
 *
 *  Created on: Oct 22, 2026
 *      Author: bomber
 */

#ifndef INCLUDE_DEBUG_H_
#define INCLUDE_DEBUG_H_

/**
 * xsyi x strings and y integers ecc..
 *
 * 1s1i means 1 string and 1 integer as arguments
 *
 * usage examples:
 * DEBUG1s1i("dio can un messaggio ed un int", 4753);
 * DEBUG1s1i("x = ", getX());
 *
 */

#ifdef DEBUG_ON

#define DEBUG1s1i(...) do {										\
	fprintf(stderr,"dbg: [file: %s] [line: %d] [func: %s]\n" 	\
			"msg: %s%d\n", __FILE__, __LINE__, __func__, __VA_ARGS__);	\
}									\
while (0)
#else
#define DEBUG1s1i(...) do {} while(0)
#endif /* DEBUG_ON */

#endif /* INCLUDE_DEBUG_H_ */
