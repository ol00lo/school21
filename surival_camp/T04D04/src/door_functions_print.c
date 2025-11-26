#include <math.h>
#include <stdio.h>
#include <string.h>

double agnesi(double x) { return 1.0 / (1.0 + x * x); }

double bernoulli(double x) {
    double s1 = sqrt(1.0 + 4.0 * x * x);
    double s2 = s1 - x * x - 1;
    if (s2 < 0) {
        return -1;
    }
    return sqrt(s2);
}

double hyperbola(double x) {
    if (x == 0) return -1;
    return 1 / x / x;
}

void print_graph(char* name) {
    const double PI = 3.14159265358979323846;
    const int WIDTH = 42;
    const int HEIGHT = 21;

    char grid[HEIGHT][WIDTH];

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grid[i][j] = ' ';
        }
    }

    int x_axis = HEIGHT / 2;
    for (int j = 0; j < WIDTH; j++) {
        grid[x_axis][j] = '-';
    }

    int y_axis = WIDTH / 2;
    for (int i = 0; i < HEIGHT; i++) {
        grid[i][y_axis] = '|';
    }

    double step_x = (2 * PI) / (WIDTH - 1);

    double min_y = 0, max_y = 0;
    for (int j = 0; j < WIDTH; j++) {
        double x = -PI + j * step_x;
        double y;
        if (strcmp(name, "agnesi") == 0)
            y = agnesi(x);
        else if (strcmp(name, "bernoulli") == 0)
            y = bernoulli(x);
        else if (strcmp(name, "hyperbola") == 0)
            y = hyperbola(x);
        if (y != -1) {
            if (y < min_y) min_y = y;
            if (y > max_y) max_y = y;
        }
    }

    double scale_y = (max_y - min_y) > 0 ? (HEIGHT - 1) / (max_y - min_y) : 1;

    for (int j = 0; j < WIDTH; j++) {
        double x = -PI + j * step_x;
        double y;
        if (strcmp(name, "agnesi") == 0)
            y = agnesi(x);
        else if (strcmp(name, "bernoulli") == 0)
            y = bernoulli(x);
        else if (strcmp(name, "hyperbola") == 0)
            y = hyperbola(x);
        else
            printf("n/a");

        if (y != -1) {
            int i = HEIGHT - 1 - (int)((y - min_y) * scale_y);
            if (i >= 0 && i < HEIGHT && j >= 0 && j < WIDTH) {
                grid[i][j] = '*';
            }
        }
    }

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    print_graph("agnesi");
    printf("\n====================agnesi======================\n\n");
    print_graph("bernoulli");
    printf("\n====================bernoulli======================\n\n");
    print_graph("hyperbola");
    printf("\n===================hyperbola=======================");

    return 0;
}