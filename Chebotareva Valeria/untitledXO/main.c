#include <stdio.h>
#include <stdbool.h>

char field[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

void printer(char *field) {
    for (int i = 0; i < 9; i++) {
        printf("%c ", field[i]);
        if ((i == 2) || (i == 5)) {
            printf("\n");
        }
    }
    printf("\n");
}

bool check(char *field) {
    bool ind=0;
    if (((field[0] == field[1]) && (field[1] == field[2])) ||
        ((field[3] == field[4]) && (field[4] == field[5])) ||
        ((field[6] == field[7]) && (field[7] == field[8])) ||
        ((field[0] == field[4]) && (field[4] == field[8])) ||
        ((field[2] == field[4]) && (field[4] == field[6])) ||
        ((field[0] == field[3]) && (field[3] == field[6])) ||
        ((field[1] == field[4]) && (field[4] == field[7])) ||
        ((field[2] == field[5]) && (field[5] == field[8]))) {
        printf("Игра закончена! \n");
        ind=1;
    }
    return ind;
}

void Xmovement(void) {
    int number;
    printf("X move to cell: \n");
    scanf("%d", &number);
    if ((field[number - 1] == 'x') || (field[number - 1] == 0)) {

        printf("you mast to choose free cell\n");
        Xmovement();
    } else {
        field[number - 1] = 'x';
    }
}

void Omovement(void) {
    int number;
    printf("0 move to cell: \n");
    scanf("%d", &number);
    if ((field[number - 1] == 'x') || (field[number - 1] == 0)) {
        printf("you mast to choose free cell\n");
        Omovement();
    } else {
        field[number-1] = '0';
    }
}

int main() {

    for (int i = 0; i < 4; i++) {
        printer(field);
        Xmovement();
        if (check(field)){
            break;
        }
        printer(field);
        Omovement();
        if (check(field)){
            break;
        }
        if (i==4){
            printf("both winners,both losers:)\n ");
        }
    }
    return 0;
}


