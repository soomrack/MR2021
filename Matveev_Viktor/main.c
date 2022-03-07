#include <stdio.h>

int LIFETIME = 120;

struct Investor {
    const char *name; //investor's name
    long long int capital;  // RUR/100
    long long int bank_account; // RUR/100
    double bank_deposit_persent; // i.e. 8.00% per year, monthly capitalization
    long int monthly_savings; // RUR/100
    long long int flat; // RUR/100
    long int rent_month; // RUR/100
    long int salary; // RUR/100
    long int pay_month; // RUR/100
};

struct Country
{
    double inflation; // percent, i.e. 6.00%
    const char* name;
};

void init_russia(struct Country *country)
{
    country->name = "Russia";
    country->inflation = 7.5;
};

void init_alice(struct Investor *person) {
    person->name = "Alice";

    person->bank_account = 1000000 * 100;
    person->bank_deposit_persent = 8.00;
    person->flat = 0;
    person->rent_month = 30000 * 100;
    person->pay_month = 0;
    person->salary = 150000 * 100;
    person->monthly_savings = 50000 * 100;

    person->capital = person->bank_account;
}

void bank_account_month_update(struct Investor *person) {
    // account persent
    int income = (int)(person->bank_account * person->bank_deposit_persent / 100.0/12.0);
    person->bank_account += income;

    //salary
    //income = person->salary - person->rent_month;
    //person->bank_account += income;

    //monthly_savings
    person->bank_account += person->monthly_savings;
}

void capital_recalculate(struct Investor *person) {
    person->capital = 0;
    person->capital += person->bank_account;
    person->capital += person->flat;
}

void month_update(struct Investor *person, struct Country country) {
    bank_account_month_update(person);
   }

void flat_price_year_update(struct Investor *person, struct Country country) {
    int addon = (int)(person->flat * country.inflation / 100.0);
    person->flat += addon;
}

void year_update(struct Investor *person, struct Country country) {
    flat_price_year_update(person, country);
}

void output(struct Investor person) {
    printf("Name: %s \n", person.name);

    int rur_m = (int)(person.bank_account / (100 * 1000 * 1000));
    int rur_t = (int)(person.bank_account / (100 * 1000)) - (rur_m * 1000);
    int rur = (int)(person.bank_account / 100) - (rur_m * 1000 * 1000 + rur_t * 1000);
    int kop = person.bank_account % 100;

    printf("Bank account: %d,%.3d,%.3d rur %.2d kop \n", rur_m, rur_t, rur, kop);

    //printf("Bank acount: %lld \n", person.bank_account);
    printf("Flat: %lld \n", person.flat);
    printf("=== \n");
    printf("Capital: %lld \n", person.capital);
}

int main()
{
    struct Country russia;
    struct Investor alice;

    init_russia(&russia);
    init_alice(&alice);

    for(int month = 1; month<=LIFETIME; month++){
        month_update(&alice, russia);

        if (month % 12 == 0) {
            year_update(&alice, russia);
        }

        capital_recalculate(&alice);
    }

    output(alice);
   }
