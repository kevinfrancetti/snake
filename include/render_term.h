/*
 * render.h
 *
 *  Created on: Sep 13, 2026
 *      Author: bomber
 */

#ifndef INCLUDE_RENDER_TERM_H_
#define INCLUDE_RENDER_TERM_H_

#include "render_api.h"


#define CELL_VOID 0
#define CELL_WALL 1

#define CSI "\x1b["   //Control Sequence Introducer
#define ANSI_CLEAR CSI "2J"



//#define ANSI_CLEAR_SCREEN printf(CSI "2J")


RenderAPI terminal_render_create(void);


#endif /* INCLUDE_RENDER_TERM_H_ */
