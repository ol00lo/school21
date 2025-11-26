#include <stdio.h>
#include <stdlib.h>

// TODO: сделать пробел пропуском
// TODO: попробовать сделать ход одновременно
// TODO: обработать ctrl+D
// TODO: Протестировать всё!!!!!

#define WIDTH 80
#define HEIGHT 25
#define ROCKET_SIZE 3
#define BALL_SIZE 1
#define WIN_SCORE 2
#define ROCKET_TAB 10

void print_field(int ball_x, int ball_y, int left_rocket_y, int right_rocket_y, int score_left,
                 int score_right);

int check_ball_x(int ball_x, int ball_y, int rocket_left, int rocket_right);
int check_ball_y(int ball_y);

int move_rocket(int input, int code, int rocket);

int Final(int left_score, int right_score, int input);
void Congratulations(int player_number);
void print_goal(int win);

int main() {
    int rocket_left_y = HEIGHT / 2 - 1, rocket_right_y = HEIGHT / 2 - 1;
    int left_score = 0, right_score = 0;
    int ball_x = WIDTH / 2, ball_y = HEIGHT / 2;
    int x_step = 1, y_step = 1;
    int is_game_over = 0;

    while (!is_game_over) {
        printf("\033[2J\033[H");
        print_field(ball_x, ball_y, rocket_left_y, rocket_right_y, left_score, right_score);

        int input = getchar();

        rocket_left_y += move_rocket(input, 1, rocket_left_y);
        rocket_right_y += move_rocket(input, 0, rocket_right_y);

        ball_x += x_step;
        ball_y += y_step;

        if (check_ball_y(ball_y) != 0) y_step *= -1;
        int res_x = check_ball_x(ball_x, ball_y, rocket_left_y, rocket_right_y);
        if (res_x == 1)
            x_step *= -1;
        else if (res_x == 2)
            left_score++;
        else if (res_x == 3)
            right_score++;

        is_game_over = Final(left_score, right_score, input);
        if (res_x == 2 || res_x == 3) {
            rocket_left_y = rocket_right_y = ball_y = HEIGHT / 2;
            ball_x = WIDTH / 2;
        }
        if (input != 10 && input != EOF) {
            while (getchar() != 10 && input != EOF);
        }
    }
    return 0;
}

void print_field(int ball_x, int ball_y, int left_rocket_y, int right_rocket_y, int score_left,
                 int score_right) {
    // Очищаем экран
    printf("\033[H\033[J");

    // Верхняя граница
    printf(" ");
    for (int i = 0; i < WIDTH; i++) {
        printf("_");
    }
    printf("\n");

    // Отрисовываем поле
    for (int y = 0; y < HEIGHT; y++) {
        printf("|");  // Левая граница
        for (int x = 0; x < WIDTH; x++) {
            if (x == ball_x && y == ball_y) {
                printf("o");
            } else if (x == WIDTH / 2 && y % 2 == 0) {
                printf("|");
            } else if (x == ROCKET_TAB && (y >= left_rocket_y && y < left_rocket_y + ROCKET_SIZE)) {
                printf("█");
            } else if (x == WIDTH - ROCKET_TAB - 1 &&
                       (y >= right_rocket_y && y < right_rocket_y + ROCKET_SIZE)) {
                printf("█");
            }
            // Пустое пространство
            else {
                printf(" ");
            }
        }

        printf("|\n");  // Правая граница
    }

    // Нижняя граница
    printf(" ");
    for (int i = 0; i < WIDTH; i++) {
        printf("‾");
    }
    printf("\n");

    // Выводим счет
    printf("Score: %02d - %02d\n", score_left, score_right);
    printf("Controls: A/Z (Left)  K/M (Right)  SPACE (Skip)\n");
}

int move_rocket(int input, int code, int rocket) {
    if (code) {
        if (input == 97 || input == 65) {
            if (rocket > 0) return -1;
            return 0;
        } else if (input == 122 || input == 90) {
            if (rocket < HEIGHT - ROCKET_SIZE) return 1;
            return 0;
        }
    } else {
        if (input == 107 || input == 75) {
            if (rocket > 0) return -1;
            return 0;
        }
        if (input == 109 || input == 77) {
            if (rocket < HEIGHT - ROCKET_SIZE) return 1;
            return 0;
        }
    }
    // printf("error in command");
    return 0;
}

int check_ball_y(int ball_y) {
    if (ball_y >= HEIGHT - 1 || ball_y <= 0) return 1;
    return 0;
}

int check_ball_x(int ball_x, int ball_y, int rocket_left, int rocket_right) {
    if (ball_x <= ROCKET_TAB + 1 && (ball_y <= rocket_left + ROCKET_SIZE && ball_y >= rocket_left))
        return 1;
    else if (ball_x >= WIDTH - ROCKET_TAB - 2 &&
             (ball_y <= rocket_right + ROCKET_SIZE && ball_y >= rocket_right))
        return 1;
    else if (ball_x <= 0)
        return 3;
    else if (ball_x >= WIDTH - 1)
        return 2;
    return 0;
}

int Final(int left_score, int right_score, int input) {
    if (left_score == WIN_SCORE) {
        Congratulations(1);
        return 1;
    }
    if (right_score == WIN_SCORE) {
        Congratulations(0);
        return 1;
    }
    if (input == EOF) {
        printf("    DRAW!");
        return 1;
    }
    return 0;
}

void Congratulations(int player_number) {
    printf("\033[H\033[J");

    printf("             __          __ _____  _   _  _   _  ______  _____     \n");
    printf("             \\ \\        / /|_   _|| \\ | || \\ | ||  ____||  __ \\  _ \n");
    printf("              \\ \\  /\\  / /   | |  |  \\| ||  \\| || |__   | |__) |(_)\n");
    printf("               \\ \\/  \\/ /    | |  | . ` || . ` ||  __|  |  _  /    \n");
    printf("                \\  /\\  /    _| |_ | |\\  || |\\  || |____ | | \\ \\  _ \n");
    printf("                 \\/  \\/    |_____||_| \\_||_| \\_||______||_|  \\_\\(_)\n");
    if (player_number) {
        printf("  _____   _              __     __ ______  _____    _      ______  ______  _______  \n");
        printf(" |  __ \\ | |        /\\   \\ \\   / /|  ____||  __ \\  | |    |  ____||  ____||__   __| \n");
        printf(" | |__) || |       /  \\   \\ \\_/ / | |__   | |__) | | |    | |__   | |__      | |    \n");
        printf(" |  ___/ | |      / /\\ \\   \\   /  |  __|  |  _  /  | |    |  __|  |  __|     | |    \n");
        printf(" | |     | |___  / ____ \\   | |   | |____ | | \\ \\  | |___ | |____ | |        | |    \n");
        printf(" |_|     |_____|/_/    \\_\\  |_|   |______||_|  \\_\\ |_____||______||_|        |_|    \n");
    } else {
        printf(
            "  _____   _              __     __ ______  _____    _____   _____   _____  _    _  _______ \n");
        printf(
            " |  __ \\ | |        /\\   \\ \\   / /|  ____||  __ \\  |  __ \\ |_   _| / ____|| |  | ||__   "
            "__| \n");
        printf(
            " | |__) || |       /  \\   \\ \\_/ / | |__   | |__) | | |__) |  | |  | |  __ | |__| |   | | "
            "\n");
        printf(
            " |  ___/ | |      / /\\ \\   \\   /  |  __|  |  _  /  |  _  /   | |  | | |_ ||  __  |   | | "
            "\n");
        printf(
            " | |     | |___  / ____ \\   | |   | |____ | | \\ \\  | | \\ \\  _| |_ | |__| || |  | |   | | "
            "\n");
        printf(
            " |_|     |_____|/_/    \\_\\  |_|   |______||_|  \\_\\ |_|  \\_\\|_____| \\_____||_|  |_|   "
            "|_| \n");
    }
    printf("\n");
}