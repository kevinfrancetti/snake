/*
 * inputi_api.h
 *
 *  Created on: Sep 17, 2026
 *      Author: bomber
 */

#ifndef INCLUDE_INPUT_API_H_
#define INCLUDE_INPUT_API_H_



typedef enum{
	KEY_API_NONE,
	KEY_API_QUIT,
	KEY_API_UP,
	KEY_API_DOWN,
	KEY_API_LEFT,
	KEY_API_RIGHT
}INPUT_KEY_API;



typedef struct{
	INPUT_KEY_API (*get_key)(void);
	void (*init)(void);
	void (*restore)(void);
	//bool (*should_quit)(void);
}InputApi;


#endif /* INCLUDE_INPUT_API_H_ */
