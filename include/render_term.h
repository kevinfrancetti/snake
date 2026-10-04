/*
 * render.h
 *
 *
 * This code only works if terminal is in raw mode.
 *
 *
 *  Created on: Sep 13, 2026
 *      Author: bomber
 */

#ifndef INCLUDE_RENDER_TERM_H_
#define INCLUDE_RENDER_TERM_H_

#include "render_api.h"

#define HEIGHT	30
#define WIDTH	90



RenderAPI terminal_render_create(void);


#endif /* INCLUDE_RENDER_TERM_H_ */
