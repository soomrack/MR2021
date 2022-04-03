#include <stdio.h>
int LIFETIME = 120;

struct country
{
    char *name;
   double inflation;
};

struct Investor
{
    char *name; //имя
    long long int capital;  //копейки
    long long int bank_account;
    long long int flat;
    long int rent_mounth;
    int salary;
    long int monthly_saving;
    long int mortgage_pay_mounth;
    double bank_deposit_percent;
};

void init_russia (struct country *country)
{
    country->name="Russia";
    country->inflation = 7.5;
}

void init_alice (struct Investor *person)
{
    person->bank_deposit_percent=8.00;
    person->name="Alice";
    (*person).bank_account = 1000000*100;
    person->flat = 0;
    person->capital=person->bank_account;
    person->rent_mounth=30000*100;
    person->salary=150000*100;
    person->mortgage_pay_mounth=0;
    person->monthly_saving=50000*100;
}

void output(struct Investor person)
{
    int rur_m=(int)(person.bank_account / (100 * 1000 * 1000));
    int rur_t=(int)(person.bank_account / (100 * 1000)) - (rur_m * 1000);
    int rur = (int)(person.bank_account / 100)
              - (rur_m * 1000 * 1000 + rur_t * 1000);
    int kop = person.bank_account % 100;

    printf("Name: %s\n",person.name);
    printf("Bank account: %d %.3d %.3d rub %.2d kop\n",rur_m, rur_t, rur, kop);
    printf("Flat: %lld\n",person.flat);
    printf("********\n");
    printf("Capital: %lld\n",person.capital);
}


void bank_account_month_update(struct Investor *person)
    {
        int income = (int) (person->bank_account*person->bank_deposit_percent/100.0/12.0);
        person->bank_account +=income;
       // income =salary - person->rent_month;
       person->bank_account+=person->monthly_saving;



    }
    void capital_recalculate(struct Investor *person)
    {
        person->capital=0;
        person->capital=person->bank_account;
        person->capital=person->flat;
    }

   void month_update( struct Investor *person, struct country country)
           {
               bank_account_month_update(person);
           }

           void flat_price_year_update( struct Investor *person, struct country country)
    {
       int addon = (int) (person->flat * country.inflation/100);
       person->flat+=addon;
    }


    void year_update( struct Investor *person, struct country country)
    {
        flat_price_year_update(person,country);
    }



int main() {
    struct Investor alice;
    struct country russia;
    init_alice(&alice);
    init_russia(&russia);
    for(int month=1;month<=LIFETIME;month++)
    {
        month_update(&alice, russia);
        if (month%12==0)
        {
            year_update (&alice, russia);
        }
        capital_recalculate(&alice);

    }

    output(alice);
    return 0;
}
