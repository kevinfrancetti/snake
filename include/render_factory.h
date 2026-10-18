/*
 * render_factory.h
 *
 *  Created on: Sep 14, 2026
 *      Author: bomber
 */

#ifndef INCLUDE_RENDER_FACTORY_H_
#define INCLUDE_RENDER_FACTORY_H_

#include "render_api.h"

 typedef enum{
	 RENDER_TERMINAL,
	 RENDER_OPENGL
 }RENDER_TYPE;




RenderAPI render_create(RENDER_TYPE);
RenderAPI render_create2(RENDER_TYPE);


#endif /* INCLUDE_RENDER_FACTORY_H_ */
