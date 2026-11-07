	/*
 * inputi_api.h
 *
 *  Created on: Sep 17, 2026
 *      Author: bomber
 */

#ifndef INCLUDE_INPUT_API_H_
#define INCLUDE_INPUT_API_H_


// @formatter:off
typedef enum{
	KEY_API_NONE,
	KEY_API_Q,
	KEY_API_W,
	KEY_API_S,
	KEY_API_A,
	KEY_API_D
}INPUT_KEY_API;
// @formatter:on


typedef struct{
	INPUT_KEY_API (*get_key)(void);
	void (*init)(void);
	void (*restore)(void);
	//bool (*should_quit)(void);
}InputApi;


#endif /* INCLUDE_INPUT_API_H_ */
