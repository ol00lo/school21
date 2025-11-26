#include <stdio.h>

int main()
{
    float num1, num2;
    if (scanf("%f %f", &num1, &num2) != 2)
    {
        printf("n/a");
        return 0;
    }
    if (num1*num1 + num2*num2 <25){
        printf("GOTCHA");
    }
    else{
        printf("MISS");
    }
    return 0;
}