#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define HEIGH 25
#define WIDTH 80


int** create_grid();
void free_grid(int** grid);
void print_grid(int** grid);
void update_grid(int** grid);
int initialaze_grid(int** grid);

int main() {
    int** grid = create_grid();
    if (grid == NULL) {
        printf("n/a");
        return 1;
    }

    if (initialaze_grid(grid) != 1) {
        printf("n/a");
        return 1;
    }

    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);

    print_grid(grid);
    refresh();
    int delay = 10000000;
    int r = 1;
    while (r) {
        int ch = getch();
        switch (ch) {
            case ' ':
                r = 0;
                break;
            case 'A':
            case 'a':
                delay = (delay > 10000) ? delay - 10000 : delay - 1000;
                break;
            case 'Z':
            case 'z':
                delay += 10000;
                break;
            default: continue;
        }
        print_grid(grid);
        update_grid(grid);
        usleep(delay);
    }
    endwin();
    free_grid(grid);
    return 0;
}

int** create_grid() {
    int** grid = malloc(HEIGH * sizeof(int*));
    for (int i = 0; i < HEIGH; i++) {
        grid[i] = calloc(WIDTH, sizeof(int));
    }
    return grid;
}

int initialaze_grid(int** grid) {
    char line[WIDTH + 2];
    int row = 0;
    while (row < HEIGH && fgets(line, sizeof(line), stdin) != NULL) {
        for (int col = 0; col < WIDTH && line[col] != '\0' && line[col] != '\n'; col++) {
            grid[row][col] = (line[col] == '1') ? 1 : 0;
        }
        row++;
    }
    return 1;
}

void free_grid(int** grid) {
    for (int i = 0; i < HEIGH; i++) {
        free(grid[i]);
    }
    free(grid);
}

void print_grid(int** grid) {
    for (int i = 0; i < HEIGH; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (grid[i][j])
                mvprintw(i, j, "*");
            else
                mvprintw(i, j, " ");
        }
    }
    refresh();

}

void copy_grid(int** grid, int** new_grid) {
    for (int i = 0; i < HEIGH; i++)
        for (int j = 0; j < WIDTH; j++) grid[i][j] = new_grid[i][j];
}

int count_neigh(int** grid, int I, int J) {
    int count = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (i == 0 && j == 0) continue;
            int ii = (i + I + HEIGH) % HEIGH;
            int jj = (j + J + WIDTH) % WIDTH;
            count += grid[ii][jj];
        }
    }
    return count;
}

void update_grid(int** grid) {
    int** new_grid = create_grid();
    for (int i = 0; i < HEIGH; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int nneigh = count_neigh(grid, i, j);
            if (grid[i][j])
                new_grid[i][j] = (nneigh == 2 || nneigh == 3) ? 1 : 0;
            else
                new_grid[i][j] = (nneigh == 3) ? 1 : 0;
        }
    }
    copy_grid(grid, new_grid);
    free_grid(new_grid);
}
