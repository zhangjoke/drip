#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include <locale.h>

#define WATER_PAIR 1
#define DEPTH 2
#define WATER_LEVEL (LINES - DEPTH)

int main()
{
	setlocale(LC_ALL,"");
	initscr();
	curs_set(0);

	start_color();
	init_pair(WATER_PAIR, COLOR_BLACK, COLOR_WHITE);
	clear();

	attron(COLOR_PAIR(WATER_PAIR)); //绘制水
	for (int y = WATER_LEVEL; y <= LINES; y++)
		mvhline(y, 0, ' ', COLS);

	attroff(COLOR_PAIR(WATER_PAIR));
	refresh();

	move(0 , COLS/2);
	printw("%s", "╏");

	int sleep_time = 70000;
	int i;
	for (i = 1; i < WATER_LEVEL; i++) { //水滴接触到水面前的情况
		if (i < WATER_LEVEL) {
			usleep(sleep_time);
			move(i, COLS / 2);
			printw("%s", "╏");
			refresh();
			move(i, COLS / 2);
			printw("%s", "┃");

			if ( i == (WATER_LEVEL -1)) {
				usleep(sleep_time + 300);
				attron(COLOR_PAIR(WATER_PAIR));
				move (WATER_LEVEL, COLS / 2);
				printw("%s", "┃");
				attroff(COLOR_PAIR(WATER_PAIR));
			}
		}
		sleep_time -=100;
		
		move(i / 2, COLS / 2);
		printw("%s", " ");
		refresh();
	}

	attron(COLOR_PAIR(WATER_PAIR)); //刚落下的情况
	move (WATER_LEVEL, COLS / 2);
	printw("%s", "━");
	move (WATER_LEVEL, COLS / 2);
	printw("%s", " ");

	attroff(COLOR_PAIR(WATER_PAIR));
	for (int n = 0; n < 2*WATER_LEVEL/3; n++) {
		move (n, COLS / 2);
		printw("%s", " ");
	}
	refresh();

	usleep(2*sleep_time);
	move((i+1) / 2, COLS / 2);
	printw("%s", " ");
	move((i+2) / 2, COLS / 2);
	printw("%s", " ");
	refresh();

	usleep(2*sleep_time); //水逐渐向四周扩散，力量也在减弱
	attron(COLOR_PAIR(WATER_PAIR));
	move (WATER_LEVEL, COLS / 2);
	printw("%s", "┅");
	attroff(COLOR_PAIR(WATER_PAIR));
	for (int n = 0; n < 3*WATER_LEVEL/4; n++) {
		move (n, COLS / 2);
		printw("%s", " ");
	}
	refresh();

	usleep(2*sleep_time);
	attron(COLOR_PAIR(WATER_PAIR));
	move (WATER_LEVEL, COLS / 2);
	printw("%s", " ");
	attroff(COLOR_PAIR(WATER_PAIR));
	move (WATER_LEVEL -1, COLS / 2 - 1);
	printw("%s", "╍");
	move (WATER_LEVEL -1, COLS / 2 + 1);
	printw("%s", "╍");
	for (int n = 0; n < WATER_LEVEL; n++) {
		move (n, COLS / 2);
		printw("%s", " ");
	}
	refresh();

	usleep(2*sleep_time); //水珠弹起的状态
	move (WATER_LEVEL - 2, COLS / 2 - 2);
	printw("%s", ".");
	move (WATER_LEVEL - 2, COLS / 2 + 2);
	printw("%s", ".");
	refresh();

	usleep(2*sleep_time);
	move (WATER_LEVEL - 2, COLS / 2 - 2);
	printw("%s", " ");
	move (WATER_LEVEL - 2, COLS / 2 + 2);
	printw("%s", " ");
	move (WATER_LEVEL - 1, COLS / 2 - 1);
	printw("%s", " ");
	move (WATER_LEVEL - 1, COLS / 2 + 1);
	printw("%s", " ");
	refresh();


	endwin();
	exit(EXIT_SUCCESS);
}
