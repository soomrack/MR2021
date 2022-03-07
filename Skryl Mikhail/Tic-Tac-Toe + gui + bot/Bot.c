//
// Created by Michael Sk on 05.11.2021.
//

#include "Bot.h"
#include <stdio.h>
#include <gtk/gtk.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

bool isFirst = FALSE;
int random_cell(void);
int defence(void);
int attack(void);

int easy_bot() {
    int pos=0;
    pos=random_cell();
    return pos;
}

int medium_bot() {
    int pos1 = -1;
    if (isFirst == FALSE) {
        pos1 = random_cell();
        isFirst = TRUE;
        return pos1;
    }
    else {
        return defence();
    }
}

int hard_bot(void) {
    int pos1 = -1;
    if (isFirst == FALSE) {
        pos1 = random_cell();
        isFirst = TRUE;
        return pos1;
    }
    else {
        return attack();
    }
}

int random_cell() {
    int pos=0;
    time_t t;
    srand(time(&t));
    pos=(rand() % 9);
    while ((field_condition[pos] != 'X') || (field_condition[pos] != '0')) {
        if ((field_condition[pos] != 'X') && (field_condition[pos] != '0')) {
            field_condition[pos] = label;
            break;
        }
        pos++;
        if (pos > 8) {
            pos=0;
        }
    }
    return pos;
}

int attack() {
    int attack_position=0;
    for (int i = 0; i < 9; ++i) {
        if ((field_condition[3 * i] == 'X') && (field_condition[3 * i + 1] == 'X') &&
            (field_condition[3 * i + 2] != 'X') && (field_condition[3 * i + 2] != '0')) {
            attack_position = 3 * i + 2;
            field_condition[attack_position] = label;
            return attack_position;
        }
        if ((field_condition[3 * i] == 'X') && (field_condition[3 * i + 2] == 'X') &&
            (field_condition[3 * i + 1] != 'X') && (field_condition[3 * i + 1] != '0')) {
            attack_position = 3 * i + 1;
            field_condition[attack_position] = label;
            return attack_position;
        }
        if ((field_condition[3 * i + 1] == 'X') && (field_condition[3 * i + 2] == 'X') &&
            (field_condition[3 * i] != 'X') && (field_condition[3 * i] != '0')) {
            attack_position = 3 * i;
            field_condition[attack_position] = label;
            return attack_position;
        }
        if ((field_condition[i] == 'X') && (field_condition[i + 3] == 'X') &&
            (field_condition[i + 6] != 'X') && (field_condition[i + 6] != '0')) {
            attack_position = i + 6;
            field_condition[attack_position] = label;
            return attack_position;
        }
        if ((field_condition[i] == 'X') && (field_condition[i + 6] == 'X') &&
            (field_condition[i + 3] != 'X') && (field_condition[i + 3] != '0')) {
            attack_position = i + 3;
            field_condition[attack_position] = label;
            return attack_position;
        }
        if ((field_condition[i + 3] == 'X') && (field_condition[i + 6] == 'X') &&
            (field_condition[i] != 'X') && (field_condition[i] != '0')) {
            attack_position = i;
            field_condition[attack_position] = label;
            return attack_position;
        }
        else if ((field_condition[i + 3] == 'X') && (field_condition[i + 6] == 'X')
                 && (field_condition[i] == 'X')) {
            attack_position=random_cell();
            return attack_position;
        }
    }
    if ((field_condition[0] == 'X') && (field_condition[4] == 'X') &&
        (field_condition[8] != 'X') && (field_condition[8] != '0')) {
        attack_position = 8;
        field_condition[attack_position] = label;
        return attack_position;
    } else if ((field_condition[0] == 'X') && (field_condition[8] == 'X') &&
               (field_condition[4] != 'X') && (field_condition[4] != '0')) {
        attack_position = 4;
        field_condition[attack_position] = label;
        return attack_position;
    } else if ((field_condition[4] == 'X') && (field_condition[8] == 'X') &&
               (field_condition[0] != 'X') && (field_condition[0] != '0')) {
        attack_position = 0;
        field_condition[attack_position] = label;
        return attack_position;
    } else if ((field_condition[2] == 'X') && (field_condition[4] == 'X') &&
               (field_condition[6] != 'X') && (field_condition[6] != '0')) {
        attack_position = 6;
        field_condition[attack_position] = label;
        return attack_position;
    } else if ((field_condition[2] == 'X') && (field_condition[6] == 'X') &&
               (field_condition[4] != 'X') && (field_condition[4] != '0')) {
        attack_position = 4;
        field_condition[attack_position] = label;
        return attack_position;
    } else if ((field_condition[4] == 'X') && (field_condition[6] == 'X') &&
               (field_condition[2] != 'X') && (field_condition[2] != '0')) {
        attack_position = 2;
        field_condition[attack_position] = label;
        return attack_position;
    } else {
        attack_position = defence();
        return attack_position;
    }
}

int defence() {
    int pos1=0;
    for (int i = 0; i < 9; ++i) {
        if ((field_condition[3 * i] == '0') && (field_condition[3 * i + 1] == '0') &&
            (field_condition[3 * i + 2] != 'X') && (field_condition[3 * i + 2] != '0')) {
            pos1 = 3 * i + 2;
            field_condition[pos1] = label;
            return pos1;
        }
        if ((field_condition[3 * i] == '0') && (field_condition[3 * i + 2] == '0') &&
            (field_condition[3 * i + 1] != 'X') && (field_condition[3 * i + 1] != '0')) {
            pos1 = 3 * i + 1;
            field_condition[pos1] = label;
            return pos1;
        }
        if ((field_condition[3 * i + 1] == '0') && (field_condition[3 * i + 2] == '0') &&
            (field_condition[3 * i] != 'X') && (field_condition[3 * i] != '0')) {
            pos1 = 3 * i;
            field_condition[pos1] = label;
            return pos1;
        }
        if ((field_condition[i] == '0') && (field_condition[i + 3] == '0') &&
            (field_condition[i + 6] != 'X') && (field_condition[i + 6] != '0')) {
            pos1 = i + 6;
            field_condition[pos1] = label;
            return pos1;
        }
        if ((field_condition[i] == '0') && (field_condition[i + 6] == '0') &&
            (field_condition[i + 3] != 'X') && (field_condition[i + 3] != '0')) {
            pos1 = i + 3;
            field_condition[pos1] = label;
            return pos1;
        }
        if ((field_condition[i + 3] == '0') && (field_condition[i + 6] == '0') &&
            (field_condition[i] != 'X') && (field_condition[i] != '0')) {
            pos1 = i;
            field_condition[pos1] = label;
            return pos1;
        }
        else if ((field_condition[i + 3] == '0') && (field_condition[i + 6] == '0')
                 && (field_condition[i] == 'X')) {
            pos1=random_cell();
            return pos1;
        }
    }
    if ((field_condition[0] == '0') && (field_condition[4] == '0') &&
        (field_condition[8] != 'X') && (field_condition[8] != '0')) {
        pos1 = 8;
        field_condition[pos1] = label;
        return pos1;
    } else if ((field_condition[0] == '0') && (field_condition[8] == '0') &&
               (field_condition[4] != 'X') && (field_condition[4] != '0')) {
        pos1 = 4;
        field_condition[pos1] = label;
        return pos1;
    } else if ((field_condition[4] == '0') && (field_condition[8] == '0') &&
               (field_condition[0] != 'X') && (field_condition[0] != '0')) {
        pos1 = 0;
        field_condition[pos1] = label;
        return pos1;
    } else if ((field_condition[2] == '0') && (field_condition[4] == '0') &&
               (field_condition[6] != 'X') && (field_condition[6] != '0')) {
        pos1 = 6;
        field_condition[pos1] = label;
        return pos1;
    } else if ((field_condition[2] == '0') && (field_condition[6] == '0') &&
               (field_condition[4] != 'X') && (field_condition[4] != '0')) {
        pos1 = 4;
        field_condition[pos1] = label;
        return pos1;
    } else if ((field_condition[4] == '0') && (field_condition[6] == '0') &&
               (field_condition[2] != 'X') && (field_condition[2] != '0')) {
        pos1 = 2;
        field_condition[pos1] = label;
        return pos1;
    } else {
        pos1 = random_cell();
        return pos1;
    }
}