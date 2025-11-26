#include "draw.h"

#include <math.h>
#include <stdio.h>

#include "calculation.h"

#define WIDTH 80
#define HEIGHT 25
#define MAX_X 4.0 * M_PI
#define MIN_X 0.0
#define MAX_Y 1.0
#define MIN_Y -1.0

int draw_graph(Stack* s) {
    const double step_x = (MAX_X - MIN_X) / (WIDTH - 1);
    const double step_y = (MAX_Y - MIN_Y) / (HEIGHT - 1);

    int is_correct = 0;
    for (double i = -1; i < 1; i += step_y) {
        for (int j = 0; j < WIDTH; j++) {
            double buf = calc_res(s, j * step_x, &is_correct);
            if (is_correct) {
                break;
            } else if (fabs(buf - i) <= step_y / 2) {
                printf("*");
            } else {
                printf(".");
            }
        }
        if (is_correct) break;
        if (i != 25) printf("\n");
    }
    return is_correct;
}
