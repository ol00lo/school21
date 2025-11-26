#include <stdio.h>

int max_num(int num1, int num2){
    if (num1 > num2) {
        return num1;
    }
    else {
        return num2;
    }
}

int main()
{
    int num1, num2;
    if(scanf("%d %d", &num1, &num2) != 2){
        printf("n/a");
        return 0;
    }

    printf("%d", max_num(num1, num2));
    return 0;
}