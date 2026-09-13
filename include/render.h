/*
 * render.h
 *
 *  Created on: Sep 13, 2026
 *      Author: bomber
 */

#ifndef INCLUDE_RENDER_H_
#define INCLUDE_RENDER_H_

#define CELL_VOID 0
#define CELL_WALL 1

#define CSI "\x1b["   //Control Sequence Introducer



#define ANSI_CLEAR_SCREEN printf(CSI "2J")


void draw_at(int x, int y, int type);
void terminal_clean_screen(void);




#endif /* INCLUDE_RENDER_H_ */
