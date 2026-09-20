/*
 * input_factory.h
 *
 *  Created on: Sep 20, 2026
 *      Author: bomber
 */

#ifndef INCLUDE_INPUT_FACTORY_H_
#define INCLUDE_INPUT_FACTORY_H_

#include "input_api.h"



typedef enum{
	INPUT_TERMINAL,
	INPUT_GLFW
}INPUT_TYPE;


InputApi input_create(INPUT_TYPE);


#endif /* INCLUDE_INPUT_FACTORY_H_ */
