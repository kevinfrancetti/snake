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
	KEY_API_q,
	KEY_API_w,
	KEY_API_s,
	KEY_API_a,
	KEY_API_d
}INPUT_KEY_API;
// @formatter:on


typedef struct{
	INPUT_KEY_API (*get_key)(void);
	void (*init)(void);
	void (*restore)(void);
	//bool (*should_quit)(void);
}InputApi;


#endif /* INCLUDE_INPUT_API_H_ */
