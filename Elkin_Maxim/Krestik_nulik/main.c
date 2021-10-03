#include <stdio.h>
#include <stdbool.h>

char arr[8];
int x;
int a=0;
// задаем игровое поле с адресами
void start_field_values() {
    for (int m=0; m<=2; m++) {
        for (int n=0; n<=2; n++) {
            a=m*3+(n+1);
            arr[a-1]=a+'0';
        }
    }
}
// выводим содержимое поля на экран
void print_field() {
    for (int m=0; m<=2; m++) {
        for (int n=0; n<=2; n++) {
            a=m*3+n;
            printf("%c  ", arr[a]);
        }
        printf("\n");
    }
}
// ввод позиции крестика
void x_position() {
    printf("Input X position\n");
    scanf("%d", &x);
    // проверка правильности адреса
    if ((x<1)||(x>9)) {
        printf("Incorrect value\n");
    }
    else {
        if (arr[x - 1] == 'X' || arr[x - 1] == 'O') {
            // проверка на попытку презаписи
            printf("Cheater detected!\n Lose a turn!\n");
        } else {
            arr[x - 1] = 'X';
        }
    }
}
// ввод позиции нолика
void o_position() {
    printf("Input O position\n");
    scanf("%d", &x);
    // проверка правильности адреса
    if ((x<1)||(x>9)) {
        printf("Incorrect value\n");
    }
    else {
        if (arr[x - 1] == 'X' || arr[x - 1] == 'O') {
            // проверка на попытку презаписи
            printf("Cheater detected!\n Lose a turn!\n");
        } else {
            arr[x - 1] = 'O';
        }
    }
}
// проверка выйгрышной комбинации
bool win() {
    // вертикальные и горизонтальные строчки
    for (int w=0; w<=2; w++) {
        if ((arr[3*w]==arr[3*w+1]&&arr[3*w+1]==arr[3*w+2])||
            (arr[w]==arr[w+3]&&arr[w+3]==arr[w+6])) {
            printf ("You are winner\n");
            return true;
        }
    }
    // диагональные строчки
    if ((arr[0]==arr[4]&&arr[4]==arr[8])||
        (arr[2]==arr[4]&&arr[4]==arr[6])) {
        printf("You are winner\n");
        return true;
    }
}
// проверка на заполненность поля
bool end_of_field() {
    int v=0;
    for (int e=0; e<=8; e++) {
        if (arr[e]=='X'||arr[e]=='O') {
            v++;
        }
    }
    if (v==9) {
        return true;
    }
    else {
        return false;
    }
}

int main() {
    start_field_values();
    print_field();
    int f=1; //счетчик для определения очередности хода
    while (f>0) {
        if (f%2!=0) {
            x_position();
            print_field();
        }
        else {
            o_position();
            print_field();
        }
        if (win()==true) {
            printf("Game Over!");
            return 0;
        }
        if (end_of_field()==true) {
            printf("End of the field!\n Game Over!");
            return 0;
        }
        f++;
    }
}
