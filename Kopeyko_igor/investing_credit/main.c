#include <stdio.h>
#include <math.h>

int main() {
    // this part of program is responsible for investing
    double babki=100000000.0;
    double umnozh=1.0+(0.08/12.0);
    printf("%f\n",umnozh);
    for(int k=0;k<240;k++) {
        babki=babki*umnozh;
        babki+=7200000.0;
        int god=k/12;
        printf("Year %d Month %d\t Bank account %f\n",god+1,k+1,babki/100.0);
    }

    // this part of program is responsible for credit
    printf("\nCredit:\n");
    double platezh;
    double dolg=1000000000.0;
    double first_pay=100000000.0;
    dolg=dolg-first_pay;
    double pro_cent=14.0;
    platezh=(dolg*(pro_cent/(12.0*100.0)))/(1.0-(pow((1.0+pro_cent/(12.0*100.0)),-240.0)));
    double vse = platezh*240;
    printf("Payment: %f\t Money will be payed overall: %f",platezh,vse);

    return 0;
}
