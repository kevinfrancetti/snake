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
	fds[0].fd = STDIN_FILENO;      // monitoro stdin
	fds[0].events = POLLIN;      // voglio sapere quando ci sono dati in lettura
	fds[0].revents = 0;            // verrà riempito da poll()


	RenderAPI render = render_create(RENDER_TERMINAL);
	InputApi input = input_factory_create(INPUT_TERMINAL);

	render.init();
	input.init();
	render.clean_screen();

	//snk_game_init();//OLD
	//snk_pres_init(&render, snk_game_get_state());


	SNK_GAME_STATE gamestate = snk_init();//new
	snk_pres_new_init(&render, &gamestate);//new



	while (1) {


		int ret = poll(fds, 1, 1000);

		fprintf(stderr, "ret: %d\n", ret);

		if (ret == 0) {
			fprintf(stderr, "Timeout\n");
			//snk_game_update(SNK_CMD_NONE);//OLD
			snk_update(&gamestate, SNK_CMD_NONE);//NEW
			snk_pres_rend(&gamestate);//new
			//snk_pres_render_state();OLD
		} else if (ret == -1) {
			fprintf(stderr, "Error\n");
		} else {

			INPUT_KEY_API key = input.get_key();
			SNAKE_CMD cmd = snake_key_bindings[key];

			//snk_game_update(cmd);//old
			snk_update(&gamestate, cmd);//new

			//snk_pres_render_state();//old
			snk_pres_rend(&gamestate);//new







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

