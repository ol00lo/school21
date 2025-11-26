#include <stdio.h>

#include "../data_libs/data_io.h"
#include "data_process.h"

int main(void) {
    double *data = NULL;
    int n = -1;

    if (input(&data, &n)) {
        printf("n/a");
        return 1;
    }

    if (normalization(data, n) && data != NULL && n > 0)
        output(data, n);
    else
        printf("ERROR");

    free(data);
    return 0;
}
