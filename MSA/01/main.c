#include <stdio.h>

int LIFETIME = 120;


struct Country {
    char *name;
    double inflation;  // percent, i.e. 6.00%    
};
    

struct Investor {
    char *name;  // Investor's name
    long long int capital;  // in RUR/100
    long long int bank_account;  // in RUR/100
    double bank_deposit_percent;  // i.e. 8.00% per year, monthly capitalization
    long long int flat;  // in RUR/100
    long int rent_month;  // in RUR/100
    long int salary;  // in RUR/100
    long int monthly_saving;  // in RUR/100
    long int mortgage_rent_month; // in RUR/100
};


void init_russia(struct Country *country) {
    country->name = "Russia";
    country->inflation = 7.25;
}


void init_alice(struct Investor *person) {
    person->name = "Alice";
        
    person->bank_account = 1000000 * 100;
    person->bank_deposit_percent = 8.00;
    person->flat = 0;
    person->mortgage_rent_month = 0;
    person->rent_month = 30000 * 100;
    person->salary = 150000 * 100;
    person->monthly_saving = 50000 * 100;
    
        
    person->capital = person->bank_account;
}


void output(struct Investor person) {
    printf("Name: %s \n", person.name);

    int rur_m = (int)(person.bank_account / (100 * 1000 * 1000));
    int rur_t = (int)(person.bank_account / (100 * 1000))
        - (rur_m * 1000);
    int rur = (int)(person.bank_account / 100)
        - (rur_m * 1000 * 1000 + rur_t * 1000);
    int kop = person.bank_account % 100;
    
    printf("Bank account: %d,%.3d,%.3d rur %.2d kop \n", rur_m, rur_t, rur, kop);
                   
    // printf("Bank account: %lld \n", person.bank_account);    
    printf("Flat: %lld \n", person.flat);
    printf("=== \n");
    printf("Capital: %lld \n", person.capital);
}


void bank_account_month_update(struct Investor *person) {
    // account percents
    int income = (int)(person->bank_account *
                       person->bank_deposit_percent / 100.0 / 12.0);
    person->bank_account += income;

    // salary
    //income = person->salary - person->rent_month;
    //person->bank_account += income;

    // monthly_savings
    person->bank_account += person->monthly_saving;
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


int main() {
    struct Country russia;
    struct Investor alice;

    init_russia(&russia);
    init_alice(&alice);

    for(int month = 1; month <= LIFETIME; month++) {
        month_update(&alice, russia);

        if(month % 12 == 0) {
            year_update(&alice, russia);
        }
        
        capital_recalculate(&alice);
    } 
    
    output(alice);
    
}
