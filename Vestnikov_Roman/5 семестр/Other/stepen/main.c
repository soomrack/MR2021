#include <stdio.h>
#include <math.h>
int stepen (int chislo, int stepen);
int main() {
    int a,b;
    printf("Введите число и степень\n");
    scanf("%d %d", &a,&b);
    int c = stepen(a,b);
    printf("Ответ:%d\n",c);
 int d = pow(a,b);
    printf("Второй ответ:%d",d);
    return 0;
}

int stepen (int chislo, int stepen)
{
   int otvet=chislo;
 for (int i=1;i<stepen;i++)
     otvet=otvet*chislo;
 return otvet;
 }
