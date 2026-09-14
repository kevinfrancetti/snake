#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <poll.h>
#include "render_api.h"
#include "render_factory.h"
#include "logic.h"



void print_some_shit();


int main() {

	// 1. Preparo un array con un solo elemento (stdin)
	struct pollfd fds[1];
	fds[0].fd = STDIN_FILENO;      // monitoro stdin
	fds[0].events = POLLIN;      // voglio sapere quando ci sono dati in lettura
	fds[0].revents = 0;            // verrà riempito da poll()

	//set_terminal_non_canonical_mode();

	print_some_shit();

	RenderAPI render = render_create(RENDER_OPENGL);

	render.init();
	render.clean_screen();
	fflush(stdout);
	while (1) {

		int ret = poll(fds, 1, 1000);

		fprintf(stderr, "merda\n");

		fprintf(stderr, "ret: %d\n", ret);

		if (ret == 0) {
			fprintf(stderr, "Timeout\n");
		} else if (ret == -1) {
			fprintf(stderr, "Error\n");
		} else {
			char ch;
			read(STDIN_FILENO, &ch, 1);
			fprintf(stderr, "Here i read: %c \n", ch);

			if (ch == '1') {
				render.draw_cell(1, 2, 0);
			}

			if (ch == '2') {
				render.draw_cell(4, 7, 1);
			}

			if (ch == 'q') {
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
