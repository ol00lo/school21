#include <stdio.h>

#include "../data_libs/data_io.h"
#include "decision.h"

int main(void) {
    double *data = NULL;
    int n = -1;
    if (input(&data, &n)) {
        printf("n/a");
        return 1;
    }
    if (make_decision(data, n) && data != NULL && n > 0)
        printf("YES");
    else
        printf("NO");
    free(data);
}
