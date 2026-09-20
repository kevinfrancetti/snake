#include <key_bindings.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <poll.h>
#include "render_api.h"
#include "render_factory.h"
#include "input_api.h"
#include "input_factory.h"
#include "logic.h"

void print_some_shit();

int main() {

	// 1. Preparo un array con un solo elemento (stdin)
	struct pollfd fds[1];
	fds[0].fd = STDIN_FILENO;      // monitoro stdin
	fds[0].events = POLLIN;      // voglio sapere quando ci sono dati in lettura
	fds[0].revents = 0;            // verrà riempito da poll()

	print_some_shit();

	RenderAPI render = render_create(RENDER_OPENGL);
	InputApi input = input_create(INPUT_TERMINAL);

	render.init();
	render.clean_screen();
	fflush(stdout);
	while (1) {

		int ret = poll(fds, 1, 1000);

		fprintf(stderr, "ret: %d\n", ret);

		if (ret == 0) {
			fprintf(stderr, "Timeout\n");
		} else if (ret == -1) {
			fprintf(stderr, "Error\n");
		} else {
			char ch = 'P';
			//read(STDIN_FILENO, &ch, 1);
			Key key = input.get_key();
			//fprintf(stderr, "Here i read: %c \n", ch);

			if (ch == '1') {
				render.draw_cell(1, 2, 0);
			}


			ACTION_TYPE action = key_binding_to_action[key];
			game_update(action);

			fprintf(stderr, "x = %d", getX());
			fprintf(stderr, "y = %d", getY());
			render.draw_cell(getX(), getY(), 0);


			if (key == KEY_QUIT) {
				fprintf(stderr, "quit\n");
				break;
			}
		}

	}

	render.cleanup();
	return 0;
}

void print_some_shit() {
	int row, col, n;
	for (row = 0; row < 11; row++) {
		for (col = 0; col < 10; col++) {
			n = 10 * row + col;
			if (n > 109)
				break;
			printf("\033[%dm %3d\033[m", n, n);
		}
	}
	printf("\n");
}
