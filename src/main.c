#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <poll.h>

//struct termios oldt, newt;

void print_some_shit();
void set_terminal_non_canonical_mode();
void set_terminal_canonical_mode();

int main() {
	double clock_time = clock();
	time_t old_time = time(NULL);

	double last_time = clock_time;
	double dt = 2 * CLOCKS_PER_SEC;

	printf("Hi: %f \n", clock_time);

	// 1. Preparo un array con un solo elemento (stdin)
	struct pollfd fds[1];
	fds[0].fd = STDIN_FILENO;      // monitoro stdin
	fds[0].events = POLLIN;      // voglio sapere quando ci sono dati in lettura
	fds[0].revents = 0;            // verrà riempito da poll()

	set_terminal_non_canonical_mode();

	print_some_shit();

	while (clock_time / CLOCKS_PER_SEC < 10.1) {

		int ret = poll(fds, 1, 0);
//		printf("ret: %d\n", ret);

		clock_time = clock();
//		printf("clock_time: %f\n", clock_time);
//
//		time_t new_time = time(NULL);
//		double diff = difftime(new_time, old_time);
//		printf("real time: %f\n", diff);

		if (ret == 0) {
//			printf("Timeout\n");
		} else if (ret == -1) {
//			printf("Error\n");
		} else {
			char ch;
			read(STDIN_FILENO, &ch, 1);
			printf("Here i read: %c \n", ch);
		}

	}

	set_terminal_canonical_mode();

	time_t new_time = time(NULL);
	double diff = difftime(new_time, old_time);
	printf("real time: %f\n", diff);
	printf("Hi: %f \n", clock_time);
	return 0;
}

void set_terminal_non_canonical_mode() {
	struct termios terminal;
	tcgetattr(STDIN_FILENO, &terminal);
	terminal.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
}

void set_terminal_canonical_mode() {
	struct termios terminal;
	tcgetattr(STDIN_FILENO, &terminal);
	terminal.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
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
