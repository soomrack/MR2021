#include <stdio.h>

int LIFETIME = 120;

struct Country{
    char* name;
    double inflation;       //percents, i.e. 7.25 %
};

struct Investor{
    char *name;                     // investor's name
    long long int capital;          // in kopeikas (rub/100)
    long long int bank_account;     // in kopeikas (rub/100)
    double bank_deposit_percent;    // i.e. 8.00 % per year
    long long int flat;             // in kopeikas (rub/100)
    long int rent_month;            // in kopeikas (rub/100)
    long int salary;                // in kopeikas (rub/100)
    long int monthly_saving;
    long int mortgage_pay_month;    // in kopeikas (rub/100)
};

void init_russia(struct Country *country){
    country->name = "Russia";
    country->inflation = 7.25;
}

void init_alice(struct Investor *person){
    person->name = "Alice";
    person->bank_deposit_percent = 8.00;
    person->bank_account = 1000000 * 100;
    person->flat = 0;
    person->rent_month = 30000 * 100;
    person->mortgage_pay_month = 0;
    person->salary = 150000 * 100;
    person->monthly_saving = 50000 * 100;

    person->capital = person->bank_account;
}

void output(struct Investor person){
    printf("Name %s\n", person.name);

    int rur_m = (int)(person.bank_account / 100 / 1000 / 1000);
    int rur_t = (int)(person.bank_account / 100 / 1000 % 1000);
    int rur = (int)(person.bank_account / 100 % 1000);
    int kop = (int)(person.bank_account % 100);
    printf("Bank account %d,%.3d,%.3d.%.2d\n", rur_m, rur_t, rur, kop);
    printf("Capital %lld\n", person.capital);
}

void bank_account_month_update(struct Investor *person){
    // account percents
    int income = (int)((double)person->bank_account *
                       person -> bank_deposit_percent / 100.0 / 12.0);
    person->bank_account += income;

    // salary
    //income = (int)(person->salary - person->rent_month);
    //person->bank_account += income;

    // monthly saving
    person->bank_account += person->monthly_saving;

}

void capital_recalculate(struct Investor *person){
    person->capital = person->bank_account;
}

void month_update(struct Investor *person, struct Country country){
    bank_account_month_update(person);
}

void flat_price_update(struct Investor *person, struct Country country){
    int addon = (int)(person->flat * country.inflation / 100.0);
    person->flat += addon;
}

void year_update(struct Investor *person, struct Country country){
    flat_price_update(person, country);
}

int main() {
    struct Investor alice;
    struct Country russia;

    init_alice(&alice);
    init_russia(&russia);
    for (int month = 1; month <= LIFETIME; month++){
        month_update(&alice, russia);
        if (month % 12 == 0){
            year_update(&alice, russia);
        }
        capital_recalculate(&alice);
    }

    output(alice);
    return 0;
}

/* ##### Notes #####
 *
 * Blocks of the program:
 * 1. Output on the display
 * 2. Data initialization
 * 3. Month changing of variables
 * 4. Random events
 *
 *
 * Scheme:
 * |init| -> |calculating| -> |output|
 *                /\
 *                |
 *          |random events|
 *
 * Functions:
 *  init();
 *  output();
 *  bank_account_month_update();
 * */