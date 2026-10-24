#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <poll.h>

#include "snake.h"
#include "snake_key_bindings.h"

#include "render_api.h"
#include "render_factory.h"

#include "input_api.h"
#include "input_factory.h"

//#define DEBUG_ON
#include "debug.h"


int main() {

	// 1. Preparo un array con un solo elemento (stdin)
	struct pollfd fds[1];
	fds[0].fd = STDIN_FILENO;      // monitoro stdin
	fds[0].events = POLLIN;      // voglio sapere quando ci sono dati in lettura
	fds[0].revents = 0;            // verrà riempito da poll()


	RenderAPI render = render_create(RENDER_TERMINAL);
	InputApi input = input_factory_create(INPUT_TERMINAL);

	render.init();
	input.init();
	render.clean_screen();
	fflush(stdout);
	int i = 0;
	int j = 0;
	while (1) {

		int ret = poll(fds, 1, 1000);

		fprintf(stderr, "ret: %d\n", ret);

		if (ret == 0) {
			fprintf(stderr, "Timeout\n");
		} else if (ret == -1) {
			fprintf(stderr, "Error\n");
		} else {

			INPUT_KEY_API key = input.get_key();

			SNAKE_CMD action = snake_key_bindings[key];
			game_update(action);

			int x = getX();
			int y = getY();

			DEBUG1s1i("x = ", getX());
			DEBUG1s1i("y = ", getY());


			//some test for the render
			RendAPIDrawInstructions apiInfo;
			apiInfo.pos.x	= x;
			apiInfo.pos.y	= y;
			apiInfo.fg		= (RendAPIColorRGB) {.r = 24, .g = 34, .b = 255};
			apiInfo.bg		= (RendAPIColorRGB) {.r = 255, .g = 34, .b = 255};
			apiInfo.shape	= SHAPE_CIRCLE;

			render.draw_buff(apiInfo);
			render.render_frame();




			if (key == KEY_API_q) {//quit
				fprintf(stderr, "quit\n");
				break;
			}
		}

	}

	//render2.cleanup();
	input.restore();
	return 0;
}

