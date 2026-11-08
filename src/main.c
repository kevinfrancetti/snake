#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <poll.h>

#include "snake.h"
#include "snake_key_bindings.h"
#include "snake_presenter.h"

#include "render_api.h"
#include "render_factory.h"

#include "input_api.h"
#include "input_factory.h"

//#define DEBUG_ON
#include "debug.h"

int main() {

	// 1. Preparo un array con un solo elemento (stdin)
	struct pollfd fds[1];
	fds[0].fd = STDIN_FILENO;	// monitoro stdin
	fds[0].events = POLLIN;		// voglio sapere quando ci sono dati in lettura
	fds[0].revents = 0;			// verrà riempito da poll()


	RenderAPI render = render_create(RENDER_TERMINAL);
	InputApi input = input_factory_create(INPUT_TERMINAL);

	render.init();
	input.init();
	render.clean_screen();

	SNK_GAME_STATE gamestate = snk_init();//new
	snk_pres_init(&render, &gamestate);//new
	while (1) {
		int ret = poll(fds, 1, 1000);

		DEBUG1s1i("poll return val=", ret);

		if (ret == 0) {
			DEBUG1s("timeout");
			snk_update(&gamestate, SNK_CMD_NONE);
			snk_pres_rend(&gamestate);
		} else if (ret == -1) {
			DEBUG1s("poll ret val=-1");
		} else {

			INPUT_KEY_API key = input.get_key();
			SNAKE_CMD cmd = snake_key_bindings[key];

			snk_update(&gamestate, cmd);
			snk_pres_rend(&gamestate);

			if (key == KEY_API_Q) {//quit
				DEBUG1s("quit");
				break;
			}
		}

	}

	//render2.cleanup();
	render.cleanup();
	input.restore();
	return 0;
}

