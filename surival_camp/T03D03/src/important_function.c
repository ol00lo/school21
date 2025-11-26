#include <stdio.h>
#include <math.h>

float important_function(float x)
{
    float s1 = 7e-3 * pow(x, 4);
    float s2 = (22.8 * pow(x, 1 / 3) - 1e3) * x + 3;
    float s3 = (x * x / 2);
    float s4 = pow(x * (10 + x), 2 / x);

    return s1 + s2 / s3 - s4 - 1.01;
}

int main()
{
    float x;
    if (scanf("%f", &x) != 1)
    {
        printf("n/a");
        return 0;
    }
    printf("%.1f", important_function(x));
    return 0;
}