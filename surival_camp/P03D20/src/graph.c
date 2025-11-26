#include <stdio.h>

#include "draw.h"
#include "stack.h"
#include "stack_oper.h"

#define MAX_STR_LEN 128

int check_folders(Stack* s);

int main() {
    char inp_str[MAX_STR_LEN];
    if (fgets(inp_str, sizeof(inp_str), stdin) != NULL) {
        Stack s = tokenize(inp_str);
        if (!check_folders(&s)) {
            printf("n/a");
            stack_freee(&s);
            return 1;
        }
        Stack new_s = shunting_yard(&s);
        if (draw_graph(&new_s)) {
            printf("n/a");
        }
        stack_freee(&new_s);
        stack_freee(&s);
    }

    return 0;
}

int check_folders(Stack* s) {
    int copen = 0;
    int cclose = 0;
    for (int i = 0; i <= s->curr_token; i++) {
        if (s->tokens[i]->type == 1 && s->tokens[i]->oper == '(')
            copen++;
        else if (s->tokens[i]->type == 1 && s->tokens[i]->oper == ')')
            cclose++;
    }
    return copen == cclose;
}
