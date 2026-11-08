/*
 * render_interface.h
 *
 *  Created on: Sep 13, 2026
 *      Author: bomber
 */

#ifndef INCLUDE_RENDER_API_H_
#define INCLUDE_RENDER_API_H_


#include <stdint.h>

typedef enum{
	SHAPE_VOID,
	SHAPE_CIRCLE,
	SHAPE_CROSS,
	SHAPE_PLUS,
	SHAPE_HASH
}RENDER_API_SHAPE;

typedef struct{
	uint8_t r;
	uint8_t g;
	uint8_t b;
}RendAPIColorRGB;

typedef struct{
	int x;
	int y;
}RendAPIPosition;

typedef struct{
	RendAPIPosition		pos;
	RendAPIColorRGB		fg;
	RendAPIColorRGB		bg;
	RENDER_API_SHAPE	shape;
}RendAPIDrawInstructions;

typedef struct {
    void (*init)(void);
    void (*draw_buff)(RendAPIDrawInstructions);
    void (*render_frame)(void);  // aggiorna lo schermo
    void (*cleanup)(void);
    void (*clean_screen)(void);
} RenderAPI;


#endif /* INCLUDE_RENDER_API_H_ */
