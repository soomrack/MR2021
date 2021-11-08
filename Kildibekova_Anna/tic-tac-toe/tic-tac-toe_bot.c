#include "tic-tac-toe_bot.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hello(void) {
    printf("Hello!\n");
}

struct Bot_Personalization {
    char crosses_or_noughts;
    char bot_name[20];
    int number_of_sign;
};

struct Bot_Table {
    int **priority_field;
    int *priority_rows;
};

void init_Bot_Personalization(struct Bot_Personalization *bot_personalization) {
    bot_personalization->crosses_or_noughts = ' ';
    strcpy(bot_personalization->bot_name, "RK-800");
}

void priority_field_size(struct Bot_Table *bot_table, int field_size) {
    bot_table->priority_field = calloc(field_size, sizeof(int*));
    bot_table->priority_rows= calloc(field_size, sizeof(int));
    for (int i = 0; i<field_size; i++){
        bot_table->priority_field[i] = calloc(bot_table->priority_rows[i], sizeof(int));
    }
}

void bot_sign_selection(struct Bot_Personalization *bot_personalization,
                        char crosses_or_noughts1) {
    if (crosses_or_noughts1=='X') {
        bot_personalization->crosses_or_noughts='0';
        bot_personalization->number_of_sign = 0;
    } else {
        bot_personalization->crosses_or_noughts='X';
        bot_personalization->number_of_sign = -1;
    }
}

void first_priority_calculation(struct Bot_Table *bot_table, int field_size) {
    for (int i=0; i < field_size; i++) {
        for (int j=0; j < field_size; j++) {
            bot_table->priority_field[i][j] =field_size;

            if ((i==0 || i==field_size-1) && (j==0 || j==field_size-1)) {
                bot_table->priority_field[i][j] = field_size+1;
            }

            if (i==(field_size-1)/2 && j==(field_size-1)/2) {
                bot_table->priority_field[i][j] = field_size+2;
            }
        }
    }
}

void diagonal_l_priority(struct Bot_Table *bot_table, int field_size, int **field) {
    for (int i=0; i < field_size-1; i++) {
        for (int j = 0; j < field_size-1; j++) {
           int flag = 0;
           int i_beg = i;
           int j_beg = j;
            while (i< field_size-1 && j< field_size-1 && field[i][j] == field[i + 1][j + 1]) {
                i++;
                j++;
                flag++;
            }
            if (flag > 0) {
                if (i_beg>0 && j_beg>0 && field[i_beg-1][j_beg-1]>0) {
                    bot_table->priority_field[i_beg-1][j_beg-1] += field_size + 2*flag;
                }
                if (i<field_size-1 && j<field_size-1 && field[i+1][j+1]>0) {
                    bot_table->priority_field[i+1][j+1] += field_size + 2*flag;
                }
            }
        }
    }
}

void vertical_priority(struct Bot_Table *bot_table, int field_size, int **field) {

    for (int i=0; i < field_size-1; i++) {
        for (int j = 0; j < field_size; j++) {
            int flag = 0;
            int i_beg = i;
            while (i< field_size-1 && field[i][j] == field[i + 1][j]) {
                i++;
                flag++;
            }
            if (flag > 0) {
                if (i_beg>0 && field[i_beg-1][j]>0) {
                    bot_table->priority_field[i_beg-1][j] += field_size + 2*flag;
                }
                if (i<field_size-1 && field[i+1][j]>0) {
                    bot_table->priority_field[i+1][j] += field_size + 2*flag;
                }
            }
        }
    }
}

void diagonal_r_priority(struct Bot_Table *bot_table, int field_size, int **field) {
    for (int i=0; i < field_size-1; i++) {
        for (int j = 1; j < field_size; j++) {
            int flag = 0;
            int i_beg = i;
            int j_beg = j;
            while (i< field_size-1 && j>0 && field[i][j] == field[i + 1][j - 1]) {
                i++;
                j--;
                flag++;
            }
            if (flag > 0) {
                if (i_beg>0 && j_beg<field_size-1 && field[i_beg-1][j_beg+1]>0) {
                    bot_table->priority_field[i_beg-1][j_beg+1] += field_size + 2*flag;
                }
                if (i<field_size-1 && j>0 && field[i+1][j-1]>0) {
                    bot_table->priority_field[i+1][j-1] += field_size + 2*flag;
                }
            }
        }
    }
}

void horizontal_priority(struct Bot_Table *bot_table, int field_size, int **field) {
    for (int i=0; i < field_size; i++) {
        for (int j = 0; j < field_size-1; j++) {
            int flag = 0;
            int j_beg = j;
            while (j< field_size-1 && field[i][j] == field[i][j+1]) {
                j++;
                flag++;
            }
            if (flag > 0) {
                if (j_beg>0 && field[i][j_beg-1]>0) {
                    bot_table->priority_field[i][j_beg-1] += field_size + 2*flag;
                }
                if (j<field_size-1 && field[i][j+1]>0) {
                    bot_table->priority_field[i][j+1] += field_size + 2*flag;
                }
            }
        }
    }
} //OK

void second_priority_calculation(struct Bot_Personalization bot_personalization,
                                 struct Bot_Table *bot_table,
                                 int field_size, int **field) {
    printf("diagonal_l\n");
    diagonal_l_priority(bot_table, field_size, field);
    printf("vertical\n");
    vertical_priority(bot_table, field_size, field);
    printf("diagonal_r\n");
    diagonal_r_priority(bot_table, field_size, field);
    printf("horizontal\n");
    horizontal_priority(bot_table, field_size, field);

    for (int i=0; i < field_size; i++) {
        for (int j=0; j < field_size; j++) {
            if (field[i][j]<1 &&
                field[i][j] != bot_personalization.number_of_sign) {
                if (i>0 && j>0 && field[i-1][j-1]>0) {
                    bot_table->priority_field[i-1][j-1] += field_size-1;
                }
                if (i>0 && j<field_size-1 && field[i-1][j+1]>0) {
                    bot_table->priority_field[i-1][j+1] += field_size-1;
                }
                if (i>0  && field[i-1][j]>0) {
                    bot_table->priority_field[i-1][j] += field_size-1;
                }
                if (i<field_size-1  && field[i+1][j]>0) {
                    bot_table->priority_field[i+1][j] += field_size-1;
                }
                if (i<field_size-1 && j<field_size-1  && field[i+1][j+1]>0) {
                    bot_table->priority_field[i+1][j+1] += field_size-1;
                }
                if (i<field_size-1 && j>0 && field[i+1][j-1]>0) {
                    bot_table->priority_field[i+1][j-1] += field_size-1;
                }
                if (j>0  && field[i][j-1]>0) {
                    bot_table->priority_field[i][j-1] += field_size-1;
                }
                if (j<field_size-1  && field[i][j+1]>0) {
                    bot_table->priority_field[i][j+1] += field_size-1;
                }
            }

            if (field[i][j]<1 &&
                field[i][j] == bot_personalization.number_of_sign) {
                if (i>0 && j>0 && field[i-1][j-1]>0) {
                    bot_table->priority_field[i-1][j-1] += field_size-2;
                }
                if (i>0 && j<field_size-1 && field[i-1][j+1]>0) {
                    bot_table->priority_field[i-1][j+1] += field_size-2;
                }
                if (i>0  && field[i-1][j]>0) {
                    bot_table->priority_field[i-1][j] += field_size-2;
                }
                if (i<field_size-1  && field[i+1][j]>0) {
                    bot_table->priority_field[i+1][j] += field_size-2;
                }
                if (i<field_size-1 && j<field_size-1  && field[i+1][j+1]>0) {
                    bot_table->priority_field[i+1][j+1] += field_size-2;
                }
                if (i<field_size-1 && j>0 && field[i+1][j-1]>0) {
                    bot_table->priority_field[i+1][j-1] += field_size-2;
                }
                if (j>0  && field[i][j-1]>0) {
                    bot_table->priority_field[i][j-1] += field_size-2;
                }
                if (j<field_size-1  && field[i][j+1]>0) {
                    bot_table->priority_field[i][j+1] += field_size-2;
                }
            }
        }
    }
}

void choose_a_cell(struct Bot_Personalization bot_personalization,
                   struct Bot_Table bot_table,
                   int field_size, int **field) {
    int max_priority = 0;
    for (int i=0; i < field_size; i++) {
        for (int j=0; j < field_size; j++) {
            if (bot_table.priority_field[i][j] > max_priority) {
                max_priority = bot_table.priority_field[i][j];
            }
        }
    }
    for (int i=0; i < field_size; i++) {
        for (int j=0; j < field_size; j++) {  // Сделать выбор более низкого приор-та
            if (bot_table.priority_field[i][j] == max_priority &&
                                                  field[i][j] > 0) {
                field[i][j] = bot_personalization.number_of_sign;
                i = field_size;
                j = field_size;
            }
        }
    }
}

void bot_main_function(int field_size, int **field, char crosses_or_noughts1) {
    struct Bot_Personalization RK_800;
    struct Bot_Table bot_table;

    init_Bot_Personalization(&RK_800);
    printf("bot_sign_selection\n");
    bot_sign_selection(&RK_800, crosses_or_noughts1);
    printf("priority_field_size\n");
    priority_field_size(&bot_table, field_size);
    printf("first_priority_calculation:\n");
    first_priority_calculation(&bot_table, field_size);

    for (int i = 0; i < field_size; i++) {
        for (int j = 0; j < field_size; j++) {
                printf("| %d |", bot_table.priority_field[i][j]);
        }
        printf("\n");
    }

    printf("second_priority_calculation:\n");
    second_priority_calculation(RK_800, &bot_table, field_size, field);

    for (int i = 0; i < field_size; i++) {
        for (int j = 0; j < field_size; j++) {
            printf("| %d |", bot_table.priority_field[i][j]);
        }
        printf("\n");
    }printf("\n");

    choose_a_cell(RK_800,bot_table,field_size, field);
}

void bot_greetings(char *name2) {
    struct Bot_Personalization RK_800;
    init_Bot_Personalization(&RK_800);

    printf("Hi, my name is %s, lets battle!\n\n",
                      RK_800.bot_name);
    strcpy(name2, RK_800.bot_name);
}