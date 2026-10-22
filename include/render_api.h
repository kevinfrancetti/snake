/*
 * render_interface.h
 *
 *  Created on: Sep 13, 2026
 *      Author: bomber
 */

#ifndef INCLUDE_RENDER_API_H_
#define INCLUDE_RENDER_API_H_

typedef enum{
	RENDER_API_EMPTY,
	CELL_PLAYER,
	CELL_SIZE,
	SHAPE_CIRCLE,
	SHAPE_CROSS
}RENDER_API_SHAPE;


typedef struct {
    void (*init)(void);
    void (*draw_cell)(int x, int y, RENDER_API_SHAPE type);
    void (*render_frame)(void);  // aggiorna lo schermo
    void (*cleanup)(void);
    void (*clean_screen)(void);
} RenderAPI;


#endif /* INCLUDE_RENDER_API_H_ */
