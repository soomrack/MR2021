//
// Версия игры с ботом
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//Создаем массив поля, один индекс это одна ячейка на поле
char field[9] = {'1','2','3','4','5','6','7','8','9'};
int mistake_move = 0;

int bot_defend(void) {
    int defend_move = 9;

    // Создаем Альтернативную матрицу, где нолики равны 1, а крестики равны 10
    int field_copy[9];
    // заполняем ее
    for (int i = 0; i <= 8; i++){
        if (field[i] == 'X') field_copy[i] = 10;
        else if (field[i] == 'O') field_copy[i] = 1;
        else field_copy[i] = 0;
    }

    //проверяем первую диагональ на опасность победы игрока
    if ((field_copy[0] + field_copy[4] + field_copy[8]) == 2) {
        //узнаем где пустая клетка чтобы прервать комбинацию для победы игрока
        for (int i = 0; i <= 8; i = i + 4){
            if (field_copy[i] == 0){
                defend_move = i; // Присваиваем значения индекса клетки для хода
            }
        }
    }

    //проверяем вторую диагональ на опасность
    if ((field_copy[2] + field_copy[4] + field_copy[6]) == 2) {
        //узнаем где контр удар
        for (int i = 2; i <= 6; i = i + 2){
            if (field_copy[i] == 0){
                defend_move = i; // Присваиваем значения индекса клетки для хода
            }
        }
    }

    // Проверяем все горизонтали на опасность победы игрока
    for (int i = 0; i <= 6; i = i + 3) {
        if ((field_copy[i] + field_copy[i+1] + field_copy[i+2]) == 2) {
            //определяем пустую клетку для защиты
            if (field_copy[i] == 0){
                defend_move = i;
            } else if (field_copy[i+1] == 0) {
                defend_move = i+1;
            } else defend_move = i+2;
        }
    }

    // Проверяем опасность победы игрока по вертикали
    for (int i = 0; i <= 2; i++) {
        if ((field_copy[i] + field_copy[i+3] + field_copy[i+6]) == 2) {
            //определяем пустую клетку для защиты
            if (field_copy[i] == 0){
                defend_move = i;
            } else if (field_copy[i+3] == 0) {
                defend_move = i+3;
            } else defend_move = i+6;
        }
    }

    return defend_move; //возвращаем индекс для хода предотвращения победы игрока
}


int bot_attack(void) {
    int attack_move = 9;

    // Создаем Альтернативную матрицу, где нолики равны 1, а крестики равны 10
    int field_copy[9];
    // заполняем ее
    for (int i = 0; i <= 8; i++){
        if (field[i] == 'X') field_copy[i] = 10;
        else if (field[i] == 'O') field_copy[i] = 1;
        else field_copy[i] = 0;
    }



    //проверяем первую диагональ на возможность победы
    if ((field_copy[0] + field_copy[4] + field_copy[8]) == 20) {
        //узнаем где пустая клетка чтобы победить
        for (int i = 0; i <= 8; i = i + 4){
            if (field_copy[i] == 0){
                attack_move = i; // Присваиваем значения индекса клетки для хода
            }
        }
    }

    //проверяем вторую диагональ на возможность победы
    if ((field_copy[2] + field_copy[4] + field_copy[6]) == 20) {
        //узнаем где победный ход
        for (int i = 2; i <= 6; i = i + 2){
            if (field_copy[i] == 0){
                attack_move = i; // Присваиваем значения индекса клетки для хода
            }
        }
    }

    // Проверяем все горизонтали на возможность победы
    for (int i = 0; i <= 6; i = i + 3) {
        if ((field_copy[i] + field_copy[i+1] + field_copy[i+2]) == 20) {
            //определяем пустую клетку для атаки
            if (field_copy[i] == 0){
                attack_move = i;
            } else if (field_copy[i+1] == 0) {
                attack_move = i+1;
            } else attack_move = i+2;
        }
    }

    // Проверяем возможность победы по вертикали
    for (int i = 0; i <= 2; i++) {
        if ((field_copy[i] + field_copy[i+3] + field_copy[i+6]) == 20) {
            //определяем пустую клетку для атаки
            if (field_copy[i] == 0){
                attack_move = i;
            } else if (field_copy[i+3] == 0) {
                attack_move = i+3;
            } else attack_move = i+6;
        }
    }

    return attack_move; //возвращаем индекс для победного хода
}




int bot_progress(void) {
    int progress_move = 9;

    // Создаем Альтернативную матрицу, где нолики равны 1, а крестики равны 10
    int field_copy[9];
    // заполняем ее
    for (int i = 0; i <= 8; i++){
        if (field[i] == 'X') field_copy[i] = 10;
        else if (field[i] == 'O') field_copy[i] = 1;
        else field_copy[i] = 0;
    }

    //проверяем первую диагональ на возможность хода
    if ((field_copy[0] + field_copy[4] + field_copy[8]) == 10) {
        //узнаем где пустая клетка
        for (int i = 0; i <= 8; i = i + 4){
            if (field_copy[i] == 0){
                progress_move = i; // Присваиваем значения индекса клетки для хода
            }
        }
    }

    //проверяем вторую диагональ на возможность хода
    if ((field_copy[2] + field_copy[4] + field_copy[6]) == 10) {
        //узнаем где пустая клетка
        for (int i = 2; i <= 6; i = i + 2){
            if (field_copy[i] == 0){
                progress_move = i; // Присваиваем значения индекса клетки для хода
            }
        }
    }

    // Проверяем все горизонтали на возможность хода
    for (int i = 0; i <= 6; i = i + 3) {
        if ((field_copy[i] + field_copy[i+1] + field_copy[i+2]) == 10) {
            //определяем пустую клетку для атаки
            if (field_copy[i] == 0){
                progress_move = i;
            } else if (field_copy[i+1] == 0) {
                progress_move = i+1;
            } else progress_move = i+2;
        }
    }

    // Проверяем возможность хода по вертикали
    for (int i = 0; i <= 2; i++) {
        if ((field_copy[i] + field_copy[i+3] + field_copy[i+6]) == 10) {
            //определяем пустую клетку для атаки
            if (field_copy[i] == 0){
                progress_move = i;
            } else if (field_copy[i+3] == 0) {
                progress_move = i+3;
            } else progress_move = i+6;
        }
    }

    return progress_move; //возвращаем индекс для победного хода
}






//Функция хода
//Игрок выбирает ячейку, куда будет помещен крестик

void x_move(void) {
    int position;
    printf("Krestiki move: (computer)\n");
    sleep(2);
    int def_move = bot_defend();
    int att_move = bot_attack();
    int pro_move = bot_progress();

    if (att_move != 9) { //проверяем можно ли победить
        position = att_move;
        field[position] = 'X';
        printf("Computer makes the final move!\n"
               "=================\n");
    } else if (def_move != 9) { // проверяем можно ли предотвратить победу игрока
        position = def_move;
        field[position] = 'X';
        printf("Computer will prevent you from winning ;)\n"
               "=================\n");
    } else if(pro_move != 9) { // проверяем можно ли поставить второй крестик в ряд
        position = pro_move;
        field[position] = 'X';
        printf("Computer goes to victory!\n"
               "=================\n");
    } else { // Так как нет нужны защитe,атаке,прогрессу то ходим на рандом
        srand(time(NULL));
        position = (rand()%10);
        printf("Computer confused, he plays random\n"
               "=================\n");
        //проверка на случай выпадения нуля в рандоме
        if (position == 0) {
            position = 5;
        }
        //на случай если компьютер уже один раз пролетел с ходом
        if (mistake_move > 0) {
            // Создаем Альтернативную матрицу, где нолики равны 1, а крестики равны 10
            int field_copy[9];
            // заполняем ее
            for (int i = 0; i <= 8; i++){
                if (field[i] == 'X') field_copy[i] = 10;
                else if (field[i] == 'O') field_copy[i] = 1;
                else field_copy[i] = 0;
            }

            //ищем свободную позицию
            for (int r = 0; r <= 8; r++){
                if (field_copy[r] == 0) {
                    position = r + 1; //используем свободную позицию
                }
            }
        }


        // проверка рандома на наличие свободной позиции
        if ((field[position - 1] == 'X')||(field[position - 1] == 'O')) {
            printf("Computer needs more time to think!\n");
            mistake_move += 1;
            x_move();
        } else {
            field[position - 1] = 'X';
        }
    }
}


//Идентичная функция хода, только для ноликов

void o_move(void) {
    int position;
    printf("Noliki move: (you)\n");
    scanf("%d",&position);
    if ((field[position - 1] == 'X')||(field[position - 1] == 'O')) {
        printf("Cell is busy!\n");
        o_move();
    } else {
        field[position - 1] = 'O';
    }
}


//Функция вывода состояния поля на экран

void output(char point[9]) {
    printf("  %c  |  %c  |  %c  \n"
           "–––––|–––––|–––––\n"
           "  %c  |  %c  |  %c  \n"
           "–––––|–––––|–––––\n"
           "  %c  |  %c  |  %c  \n"
           "=================\n"
           "=================\n",
           point[0], point[1], point[2],
           point[3], point[4], point[5],
           point[6], point[7], point[8]);
}


//Если функция win_check обнаружит необходимые последовательности для победы
//то функция who_win узнает кто конкретно победил

char who_win(char player) {
    if (player == 'O') {
        output (field);
        printf("NOLIKI WIN!");
        exit(1);
    } else {
        output (field);
        printf("KRESTIKI WIN!");
        exit(1);
    }
}


//Функция win_check проверяет необходимые последовательности для победы после каждого хода

void win_check(void) {

    // Проверяем диагональ
    if ((field[0] == field[4]) && (field[4] == field[8])) {
        who_win(field[0]);
    }

    // Проверяем другую диагональ
    if ((field[6] == field [4]) && (field [4] == field [2])) {
        who_win(field[6]);
    }

    // Проверяем все горизонтали
    for (int i = 0; i <= 6; i = i + 3) {
        if ((field[i] == field[i + 1]) && (field[i + 1] == field[i + 2])) {
            who_win(field[i]);
        }
    }

    // Проверяем все вертикали
    for (int i = 0; i <= 2; i++) {
        if ((field[i] == field[i + 3]) && (field[i + 3] == field[i + 6])) {
            who_win(field[i]);
        }
    }
}


//Главный цикл игры

int main() {

    // Инструкция
    printf("=================\n"
           "How to play:\n"
           "Every cell has an index.\n"
           "When it is your move, just write cell index.\n"
           "Example:\n"
           "Noliki move: (you)\n"
           "5\n"
           "=================\n"
           "You are playing against the computer!\n"
           "=================\n");


    for (int g = 0; g <= 4; g++) {
        output (field);
        x_move();
        win_check();

        // Если поле заполнится, то победила дружба
        if (g == 4) {
            printf("Friendship WIN!");
            exit(1);
        }

        output (field);
        o_move();
        win_check();
    }
    return 0;
}
