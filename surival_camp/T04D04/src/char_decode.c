#include <stdio.h>

void print_decode() {
    char c[3];
    int is_first = 1;
    while (scanf("%2s", c) == 1) {
        if (c[0] == '\n') break;

        int n;
        if (sscanf(c, "%02x", &n) != 1) {
            printf("n/a");
            return;
        }

        char next_symbol;
        if (scanf("%c", &next_symbol) != 1) break;
        if (next_symbol != ' ' && next_symbol != '\n') {
            printf("n/a");
            return;
        }
        if (is_first == 1)
            printf("%c", n);
        else
            printf(" %c", n);
        if (next_symbol == '\n') break;
        is_first = 0;
    }
}

void print_encode() {
    char c;
    int is_first = 1;
    while (scanf("%c", &c) == 1) {
        if (c == '\n') break;
        if (c == ' ') continue;

        int saved_pos = ftell(stdin);
        char next_sumbol;
        if (scanf("%c", &next_sumbol) != 1) break;
        ungetc(next_sumbol, stdin);
        fseek(stdin, saved_pos, SEEK_SET);

        if (next_sumbol != ' ' && next_sumbol != '\n') {
            printf("n/a");
            return;
        }
        if (is_first)
            printf("%02x", (int)c);
        else
            printf(" %02x", (int)c);
        is_first = 0;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("n/a");
        return 1;
    }
    if (argv[1][0] == '0' && argv[1][1] == '\0') {
        print_encode();
    } else if (argv[1][0] == '1' && argv[1][1] == '\0') {
        print_decode();
    } else {
        printf("n/a");
        return 1;
    }
    return 0;
}
