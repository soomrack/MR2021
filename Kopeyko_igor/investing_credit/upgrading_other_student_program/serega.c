#include <stdio.h>
#include <math.h>

int main() {
    long long int x = 100000000; // лимон с копейками
    long long int dop;
    long long int rub;
    long long int cop;

// Новые переменные для инфляции
    long long int rent = 4000000;
    long long int kv_price = 1000000000;
    for (long int i = 1; i <= 240; i++) {
        dop = (double) (x * 8.0 / 1200.0); // коэфициент процента
        x = x + dop; // накопление
        rub = x / 100;
        cop = x % 100;
        x = x + 11200000 - rent;
        if (i%12==0) {  // условие что раз в год инфляция
            rent *= 1.075;
            kv_price *= 1.075;
            printf ("Rent: %d Ap. price: %lld Bank account: %lld%lld|||| Year %d\n",rent,kv_price,rub,cop,i/12);
        }
    }
    if (cop < 10) {
        printf("==================\nBank account: %lli.0%lli\n", rub, cop);
    } else {
        printf("Nakopim: %lli.%lli\n", rub, cop);
    }
    double ip = 10000000;
    double pl;
    double s = 9000000; //остаток долга
    pl = (s*14.0/1200.0)/(1-pow(1200.0/1214.0,240)); // платеж по кредиту
    printf("PerMonth:%6.2f, Summ: %6.2f\n", pl, pl*240);
    printf("Price: %6.2f\n", ip);
}
