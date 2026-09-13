/*
 * render_interface.h
 *
 *  Created on: Sep 13, 2026
 *      Author: bomber
 */

#ifndef INCLUDE_RENDER_INTERFACE_H_
#define INCLUDE_RENDER_INTERFACE_H_


typedef struct {
    void (*init)(void);
    void (*draw_cell)(int x, int y, int type); // type = 0 empty, 1 food, 2 snake
    void (*render_frame)(void);  // aggiorna lo schermo
    void (*cleanup)(void);
    void (*clean_screen)(void);
} RenderAPI;


#endif /* INCLUDE_RENDER_INTERFACE_H_ */
