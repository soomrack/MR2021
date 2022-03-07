#include<stdio.h>

struct Symbols {
    char *space, *winner, crosses_or_noughts;
    int n, end, str, stolb;
    int field[];
};

void init_symbols(struct Symbols *symbols) {
    symbols->space = " ";
    symbols->winner = " ";
    //symbols->crosses_or_noughts=" ";
    symbols->n = 0;
    symbols->end = 0;
}

void field_size(struct Symbols *symbols) {
    printf("Enter field size:\n");
    scanf("%d%c", &symbols->n, &symbols->space);

}

void intr(struct Symbols *symbols) {
    for (int i = 0; i < (symbols->n * symbols->n); i++) {
        symbols->field[i] = i + 1;
        printf("|%d|", symbols->field[i]);
        if ((i + 1) == (i + 1) / symbols->n * symbols->n)
            printf("\n");
    }
}

void output(struct Symbols *symbols) {

    for (int i = 0; i < (symbols->n * symbols->n); i++) {
        switch (symbols->field[i]) {
            case -1:
                printf("|X|");
                break;
            case 0:
                printf("|0|");
                break;
            default:
                printf("|%d|", symbols->field[i]);
        }

        if ((i + 1) == (i + 1) / symbols->n * symbols->n)
            printf("\n");
    }

}

void input(struct Symbols *symbols) {
    int address = 0;

    printf("Choose a free cell number:\n");
    scanf("%d%c", &address, &symbols->space);

    if (address > symbols->n * symbols->n)
        printf("Cell number entered incorrectly\n");
    if (address < 1)
        printf("Cell number entered incorrectly\n");
    if (symbols->field[address - 1] < 1)
        printf("Cell number entered incorrectly\n");

    printf("Choose symbol:\n");
    scanf("%s%c", &symbols->crosses_or_noughts, &symbols->space);

    switch (symbols->crosses_or_noughts) {
        case 'X':
        case 'x':
        case '*':
        case 'K':
        case 'k':
            symbols->field[address - 1] = -1;
            break;
        case '0':
        case 'O':
        case 'o':
            symbols->field[address - 1] = 0;
            break;
        default:
            printf("Symbol entered incorrectly\n");
    }
}

int check_diagonal_l(struct Symbols *symbols) {
    int s = 0;
    for (int t = 0; t < symbols->n; t++) {
        if (symbols->field[t * symbols->n + t] < 1)
            s = s + 1;
    }
    return s;
}

int check_vertical(struct Symbols *symbols) {
    int s = 0;
    for (int t = 0; t < symbols->n; t++) {
        if (symbols->field[symbols->stolb + t * symbols->n] < 1)
            s = s + 1;
    }
    return s;
}

int check_horizontal(struct Symbols *symbols) {
    int s = 0;
    for (int t = 0; t < symbols->n; t++) {
        if (symbols->field[symbols->str * symbols->n + t] < 1)
            s = s + 1;
    }
    return s;
}

int check_diagonal_r(struct Symbols *symbols) {
    int s = 0;
    for (int t = 0; t < symbols->n; t++) {
        if (symbols->field[(symbols->n - 1) * (t + 1)] < 1)
            s = s + 1;
    }
    return s;
}

void check(struct Symbols *symbols) {
    int counter_x = 0;
    int counter_0 = 0;
    symbols->str = 0;
    for (int i = 0; i < symbols->n; i++) {
        switch (symbols->field[i]) {
            case -1:
                if (i == 0) {
                    counter_x = check_diagonal_l(symbols);
                }
                if (counter_x < symbols->n) {
                    symbols->stolb = i;
                    counter_x = check_vertical(symbols);
                    if (counter_x < symbols->n) {
                        if (i + 1 == symbols->n) {
                            counter_x = check_diagonal_r(symbols);
                        }
                    }
                }
                break;

            case 0:
                if (i == 0) {
                    counter_0 = check_diagonal_l(symbols);
                }
                if (counter_0 < symbols->n) {
                    symbols->stolb = i;
                    counter_0 = check_vertical(symbols);
                    if (counter_0 < symbols->n) {
                        if (i + 1 == symbols->n) {
                            counter_0 = check_diagonal_r(symbols);
                        }
                    }
                }
                break;
        }
        switch (symbols->field[i * symbols->n]) {
            case -1:
                if (counter_x < symbols->n) {
                    symbols->str = i;
                    counter_x = check_horizontal(symbols);
                }
                break;

            case 0:
                if (counter_0 < symbols->n) {
                    symbols->str = i;
                    counter_0 = check_horizontal(symbols);
                }
                break;
        }
    }
    if (counter_x == symbols->n) {
        symbols->end = 1;
        symbols->winner = "crosses";
    }

    if (counter_0 == symbols->n) {
        symbols->end = 1;
        symbols->winner = "noughts";
    }

}

void act(struct Symbols *symbols) {

    intr(symbols);
    while (symbols->end == 0) {
        input(symbols);
        output(symbols);
        check(symbols);
    }


}

void result(struct Symbols symbols) {
    printf("Game over\n");
    printf("Won the %s !!!\n", symbols.winner);
}

int main(void) {
    struct Symbols sign;
    init_symbols(&sign);

    printf("Let's play tic-tac-toe\n");

    field_size(&sign);
    act(&sign);
    result(sign);

}