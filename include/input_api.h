/*
 * inputi_api.h
 *
 *  Created on: Sep 17, 2026
 *      Author: bomber
 */

#ifndef INCLUDE_INPUT_API_H_
#define INCLUDE_INPUT_API_H_



typedef enum{
	KEY_NONE,
	KEY_QUIT,
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT
}Key;



typedef struct{
	Key (*get_key)(void);
	//bool (*should_quit)(void);
}InputApi;


#endif /* INCLUDE_INPUT_API_H_ */
