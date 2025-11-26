#include "data_change.h"

void sort(double *data, int n) {
    for (double *j = data; j - data < n; j++) {
        for (double *i = data; i - data < n - 1 - (j - data); i++) {
            if (*i > *(i + 1)) {
                double tmp = *i;
                *i = *(i + 1);
                *(i + 1) = tmp;
            }
        }
    }
}
