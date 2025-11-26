#include "data_stat.h"

double max(double *data, int n) {
    double cmax = data[0];
    for (int i = 1; i < n; i++)
        if (data[i] > cmax) cmax = data[i];
    return cmax;
}

double min(double *data, int n) {
    double cmin = data[0];
    for (int i = 1; i < n; i++)
        if (data[i] < cmin) cmin = data[i];
    return cmin;
}

double mean(double *data, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) sum += data[i];
    return sum / n;
}

double variance(double *data, int n) {
    double v = 0;
    double m = mean(data, n);
    for (int i = 0; i < n; i++) v += (data[i] - m) * (data[i] - m);
    return v / n;
}