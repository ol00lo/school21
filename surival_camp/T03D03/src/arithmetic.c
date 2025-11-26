#include <stdio.h>

int main()
{
    int num1, num2;
    if(scanf("%d %d", &num1, &num2) != 2){
        printf("n/a");
        return 0;
    }

    int sum = num1 + num2;
    int sub = num1 - num2;
    int mult = num1 * num2;

    printf("%d %d %d ", sum ,sub, mult);

    if(num2 == 0) {
        printf("n/a");
    }
    else {
        int div = num1 / num2;
        printf("%d", div);
    }

    return 0;
}