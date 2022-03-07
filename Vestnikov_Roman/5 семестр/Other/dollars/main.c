#include <stdio.h>
#define DOLL 72.82
int main()
{
    float sumr = 1;
    while (sumr!=0)
    {
        printf("Введите сумму в рублях (0 для выхода):");
        scanf("%f",&sumr);
        if (sumr!=0) {
            printf("%.2f рублей составляют %.2f долларов США\n",sumr,sumr/DOLL);
        } }
    printf("Готово!");
}
