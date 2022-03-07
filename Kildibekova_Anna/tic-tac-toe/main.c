#include<stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include "tic-tac-toe_bot.h"

struct Personalization {
    char crosses_or_noughts1;
    char name1[20];
    char name2[20];
};

struct Service {
    char *space;
    char current_sign;
    bool winner_x;
    bool winner_0;
    bool winner_no_one;
    bool end;
    int string;
    int column;
};

struct Table {
    int field_size;
    int **field;
    int *rows;
    int signs_in_a_row;
};

void init_Personalization(struct Personalization *personalization) {
    personalization->crosses_or_noughts1 = ' ';
}

void init_Service(struct Service *service) {
    service->string = 0;
    service->column = 0;
    service->end = false;
    service->winner_x=false;
    service->winner_0=false;
    service->winner_no_one=false;
    service->current_sign=' ';
}

void init_Table(struct Table *table) {
    table->field_size = 0;
}

/**
 *
 * @param personalization - player names
 */
void acquaintance1(struct Personalization *personalization) {
    printf("Player number one, enter your name:\n",personalization->name1);
    gets(personalization->name1);
}

void acquaintance2(struct Personalization *personalization) {
    printf("Player number two, enter your name:\n",personalization->name2);
    gets(personalization->name2);
}

void sign_selection(struct Personalization *personalization, struct Service service) {
    printf("%s pick your sign (x or 0):\n", personalization->name1);
    scanf("%c%c", &personalization->crosses_or_noughts1, &service.space);
    switch (personalization->crosses_or_noughts1) {
        case 'X':
        case 'x':
        case '*':
        case 'K':
        case 'k':
            personalization->crosses_or_noughts1='X';
            break;
        case '0':
        case 'O':
        case 'o':
            personalization->crosses_or_noughts1='0';
            break;
        default:
            printf("Symbol entered incorrectly\n");
    }
}

void field_size(struct Table *table, struct Service service) {
    printf("Enter field size:\n");
    scanf("%d%c", &table->field_size, &service.space);
    table->field= calloc(table->field_size, sizeof(int*));
    table->rows= calloc(table->field_size, sizeof(int));
    for (int i = 0; i<table->field_size; i++){
        table->field[i] = calloc(table->rows[i], sizeof(int));
    }
}

void signs_in_a_row(struct Table *table, struct Service service) {
    /*
    printf("Enter the amount of signs in a row:\n");
    scanf("%d%c", &table->signs_in_a_row, &service.space);
    if (table->signs_in_a_row > table->field_size) {
        printf("Error! The amount of signs in a row is too big!:\n");
    }
    if (table->signs_in_a_row <0) {
        printf("Error! The amount of signs in a row is too little!:\n");
    }
     */
    table->signs_in_a_row = table->field_size;
}

void field_numbering(struct Table *table) {
    for (int i = 0; i < table->field_size; i++) {
        for (int j = 0; j < table->field_size; j++) {
            table->field[i][j] = i*table->field_size + j + 1;
            if (table->field[i][j]<10) {
                printf("|  %d |", table->field[i][j]);
            }
            else {
                printf("| %d |", table->field[i][j]);
            }
        }
        printf("\n");
    }
}

void input(struct Personalization personalization, struct Table *table, struct Service service) {
    int address = 0;
    int i = 0;
    int j = 0;

    if (service.current_sign == personalization.crosses_or_noughts1) {
        printf("%s, choose a free cell number:\n", personalization.name1);
    } else {
        printf("%s, choose a free cell number:\n", personalization.name2);
    }
    scanf("%d%c", &address, &service.space);

    i=(address-1)/table->field_size;
    j=address-i*table->field_size-1;

    if (address > table->field_size * table->field_size)
        printf("Cell number entered incorrectly\n");
    if (address < 1)
        printf("Cell number entered incorrectly\n");
    if (table->field[i][j] < 1)
        printf("Cell number entered incorrectly\n");

    switch (service.current_sign) {
        case 'X':
            table->field[i][j] = -1;
            break;
        case '0':
            table->field[i][j] = 0;
            break;
        default:
            printf("Error\n");
    }
}

void output(struct Table table) {

    for (int i = 0; i < table.field_size; i++) {
        for (int j = 0; j < table.field_size; j++) {
            switch (table.field[i][j]) {
                case -1:
                    printf("|  X |");
                    break;
                case 0:
                    printf("|  0 |");
                    break;
                default:
                    if (table.field[i][j]<10) {
                        printf("|  %d |", table.field[i][j]);
                    }
                    else {
                        printf("| %d |", table.field[i][j]);
                    }
            }
        }
        printf("\n");
    }
}

void check_diagonal_l(struct Table table, struct Service *service) {
    for (int i = 0; i < table.signs_in_a_row-1; i++) {
        if (table.field[i][i] != table.field[i+1][i+1]) {
            if (service->winner_x==true) {
                service->winner_x=false;
            }
            else {
                service->winner_0=false;
            }
        }
    }
}

void check_vertical(struct Table table, struct Service *service) {
    int j = service->column;
    for (int i = 0; i < table.signs_in_a_row - 1; i++) {
        if (table.field[i][j] != table.field[i + 1][j]) {
            if (service->winner_x == true) {
                service->winner_x = false;
            }
            else {
                service->winner_0 = false;
            }
        }
    }
}

void check_diagonal_r(struct Table table, struct Service *service) {
    int j=table.field_size-1;
    for (int i = 0; i < table.signs_in_a_row-1; i++) {
        if (table.field[i][j-i] != table.field[i+1][j-(i+1)]) {
            if (service->winner_x==true) {
                service->winner_x=false;
            }
            else {
                service->winner_0=false;
            }
        }
    }
}

void check_horizontal(struct Table table, struct Service *service) {
    int i = service->string;
    for (int j = 0; j < table.signs_in_a_row - 1; j++) {
        if (table.field[i][j] != table.field[i][j+1]) {
            if (service->winner_x == true) {
                service->winner_x = false;
            }
            else {
                service->winner_0 = false;
            }
        }
    }
}

void check_draw(struct Table table, struct Service *service) {
    int flag=0;
    if (service->winner_x == false && service->winner_0 == false) {
        for (int i = 0; i < table.field_size; i++) {
            for (int j = 0; j < table.field_size; j++) {
                if (table.field[i][j] < 1) {
                    flag += 1;
                }
            }
        }

        if (flag == table.field_size * table.field_size) {
            service->winner_no_one = true;
        }
    }
}

void check_all(struct Table table, struct Service *service) {
    int i=0;
    for (int j = 0; j < table.field_size; j++) {
        if (service->winner_x == false && service->winner_0 == false) {
            switch (table.field[i][j]) {
                case -1:
                    if (j == 0) {
                        service->winner_x = true;
                        check_diagonal_l(table, service);
                    }
                    if (service->winner_x == false) {
                        service->winner_x = true;
                        service->column = j;
                        check_vertical(table, service);
                        if (service->winner_x == false) {
                            if (j + 1 == table.field_size) {
                                service->winner_x = true;
                                check_diagonal_r(table, service);
                            }
                        }
                    }
                    break;

                case 0:
                    if (j == 0) {
                        service->winner_0 = true;
                        check_diagonal_l(table, service);
                    }
                    if (service->winner_0 == false) {
                        service->winner_0 = true;
                        service->column = j;
                        check_vertical(table, service);
                        if (service->winner_0 == false) {
                            if (j + 1 == table.field_size) {
                                service->winner_0 = true;
                                check_diagonal_r(table, service);
                            }
                        }
                    }
                    break;
            }
        }
    }
    int j=0;
    for ( i = 0; i < table.field_size; i++) {
        if (service->winner_x == false && service->winner_0 == false) {
            switch (table.field[i][j]) {
                case -1:
                    if (service->winner_x == false) {
                        service->winner_x = true;
                        service->string = i;
                        check_horizontal(table, service);
                    }
                    break;

                case 0:
                    if (service->winner_0 == false) {
                        service->winner_0 = true;
                        service->string = i;
                        check_horizontal(table, service);
                    }
                    break;
            }
        }
    }
    check_draw(table, service);
}

void won_no_one(struct Service *service) {
    service->end = true;
    printf("Game over.\n");
    printf("Won no one.\n");
}

void won_x(struct Personalization personalization, struct Service *service) {
    service->end = true;
    printf("Game over.\n");
    if (personalization.crosses_or_noughts1=='X') {
        printf("Won the %s !!!\n", personalization.name1);
    } else {
        printf("Won the %s !!!\n", personalization.name2);
    }

}

void won_0(struct Personalization personalization, struct Service *service) {
    service->end = true;
    printf("Game over.\n");
    if (personalization.crosses_or_noughts1=='X') {
        printf("Won the %s !!!\n", personalization.name2);
    } else {
        printf("Won the %s !!!\n", personalization.name1);
    }
}

void response_to_check(struct Personalization personalization, struct Service *service){
    if (service->winner_no_one == true) {
        won_no_one(service);
    }
    if (service->winner_x == true) {
        won_x(personalization, service);
    }
    if (service->winner_0 == true) {
        won_0(personalization, service);
    }
}

void act(struct Personalization personalization, struct Table *table,
                            struct Service *service, char type_of_play) {

    int current_player = 0;
    field_numbering(table);
    service->current_sign = personalization.crosses_or_noughts1;
    if (type_of_play == 'y') {
        while (service->end == false) {
            if (current_player == 0) {
                input(personalization, table, *service);
            } else {
                bot_main_function(table->field_size, table->field,
                                  personalization.crosses_or_noughts1);
            }
            output(*table);
            check_all(*table, service);
            response_to_check(personalization, service);
            if (current_player == 0) {
                current_player = 1;
            } else {
                current_player = 0;
            }
            printf("\t Next part (%d)\n", current_player);
        }
    }
    else {
        while (service->end == false) {
            input(personalization, table, *service);
            output(*table);
            check_all(*table, service);
            response_to_check(personalization, service);
            if (service->current_sign == 'X') {
                service->current_sign = '0';
            } else {
                service->current_sign = 'X';
            }
        }
    }
}


int main(void) {

    struct Personalization player;
    struct Service service;
    struct Table table;

    init_Personalization(&player);
    init_Service(&service);
    init_Table(&table);

    char type_of_play;

    hello();
    printf("Let's play tic-tac-toe!\n");
    printf("Do you want to play with bot? (y/n)\n");
    scanf("%c%c", &type_of_play, &service.space);

    acquaintance1(&player);
    if (type_of_play == 'y') {
        bot_greetings(player.name2);
    }
    else {
        acquaintance2(&player);
    }

    field_size(&table, service);
    signs_in_a_row(&table, service);
    sign_selection(&player, service);

    act(player, &table, &service, type_of_play);

    return 0;
}
