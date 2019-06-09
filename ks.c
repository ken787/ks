#include <curses.h>
#include <signal.h>
#include <unistd.h>

#define HEIGHT 3
#define WIDTH 17
#define STR1 " _A_A_A_A_A_A_A_ "
#define STR2 " >  KASU OTSU! < "
#define STR3 " ^Y^Y^Y^Y^Y^Y^Y^ "

int show_ks(int x);

int main(void) {
    initscr();
    signal(SIGINT, SIG_IGN);
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    leaveok(stdscr, TRUE);
    scrollok(stdscr, FALSE);

    for (int x = COLS-1; x > COLS/2 - WIDTH/2; x--) {
        if (show_ks(x) == ERR) break;
        show_ks(x);
        getch();
        refresh();
        usleep(50000);
    }
    usleep(3000000);
    for (int x = COLS/2 - WIDTH/2;; x--) {
        if (show_ks(x) == ERR) break;
        show_ks(x);
        getch();
        refresh();
        usleep(50000);
    }
    mvcur(0, COLS - 1, LINES - 1, 0);
    endwin();

    return 0;
}

int show_ks(int x) {
    static char *kasu_array[HEIGHT] = {STR1, STR2, STR3};
    int i, y;
    if (x < -WIDTH) {
        return ERR;
    }
    y = LINES/2 - HEIGHT;
    for (i = 0; i < HEIGHT; i++) {
        char *kasu_line = kasu_array[i];
        int t_x = x;
        for (; t_x < 0; t_x++, kasu_line++) {
            if (*kasu_line == '\0') break;
        }
        for (; *kasu_line != '\0'; kasu_line++, t_x++) {
            if (mvaddch(y+i, t_x, *kasu_line) == ERR) break;
        }
    }

    return OK;
}

