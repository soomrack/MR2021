#include <stdio.h>
int field_size();
void completion();
void visual();
void rules();
void play();
int check();
void congratulation(int victory);
int krestik(int step);
int nolik(int step);
void syntax(int *a, int *b);

int i=0, j=0;
int size;
int pole[20][20];


int main() {
    int contin;
do {
    size=field_size();
    completion();
    rules();
    visual();
    play();
    printf ("\n\nЖелаете продолжить?\n(нажмите 2 - для выхода, любое другое число - для продолжения)\n");
    scanf ("%d", &contin);
} while (contin!=2);
    printf ("До свидания!\n");
    return 0;
}

int field_size()
{ int word;
    printf ("Какой размер поля вы хотите? (введите 3 для стандартной игры)\n");
    word = scanf("%d",&size);
    while ((word != 1) || size>20 || size<3)  {
        if (word != 1) scanf("%*s");
        printf("Некорректный ввод!\n");
        printf("Повторите ввод: ");
        word = scanf("%d",&size);
    }
   return size;
}
void completion()   //Первоначальное заполнение поля пустными клетками
{

    for (i=0;i<size;i++) {
        for (j = 0; j < size; j++)
            pole[i][j]=0;
    }

}

void visual()   // Отображает поле
{

    for (int t=0;t<size;t++) printf ("==");
    printf ("=\n");
    for (i=0;i<size;i++) {
        for (j = 0; j < size; j++)
        {

            if (pole[i][j]==0) printf("| ");
            if (pole[i][j]==1) printf("|X");
            if (pole[i][j]==2) printf("|0");
        }
        printf ("|\n");
        for (int t=0;t<size;t++) printf ("==");
        printf ("=\n");
    }

}

void rules()     //Правила
{
    printf ("Добро пожаловать в игру!\n");
    printf ("Правила игры: первым ходит крестик.\nПроизводится ввод с клавиатуры двух чисел через пробел.\nСперва вводится номер строки, затем номер столбца\n");
    printf ("Затем ход передаётся второму игроку (нолику)\n");
}
void play()      //Ход игры
{

int step, victory;
 victory=0;

    for (step=1;victory!=1 && victory!=2 && victory!=3;step++) {
       victory=krestik(step);
       if (victory==1 || victory==3) break;
        victory=nolik(step);
    }
    congratulation(victory);
}

int krestik(int step)    //Ход крестика
{

    int victory,row, col;
    printf("%d ход - крестик\n", step);
    printf("Выберите клетку: ");
    syntax (&row, &col);
    pole[row-1][col-1]=1;
    visual();
    victory = check();
    return victory;
}

void syntax(int *a, int *b)     //Контроль вводимых данных
{

    int  word, roww, coll ;
    word = scanf("%d %d",&roww, &coll);
    while ((word != 2) || roww>size || roww<=0 || coll>size || coll<=0 || pole[roww-1][coll-1]!=0) {
        if (word != 2) scanf("%*s");
        printf("Ошибка ввода!\n");
        printf("Повторите ввод: ");
        word = scanf("%d %d",&roww, &coll);
    }
    *a=roww;
    *b=coll;
}


int nolik(int step)     //Ход нолика
{

    int victory,row, col;
    printf("%d ход - нолик\n", step);
    printf("Выберите клетку: ");
    syntax (&row, &col);
    pole[row-1][col-1]=2;
    visual();
    victory = check();
    return victory;
}


int check()      //Проверка на победу/ничью
{

    int victory = 0, c=0;
    for (i = 0; i < size; i++) {             //Проверка по горизонтали
        for (j = 0; j < size-2; j++) {
            if (pole[i][j] == 1 && pole[i][j + 1] == 1 && pole[i][j + 2] == 1) {
                victory = 1;
                break;
            }
            if (pole[i][j] == 2 && pole[i][j + 1] == 2 && pole[i][j + 2] == 2) {
                victory = 2;
                break;
            }
        }

    }
    for (j = 0; j < size; j++) {             //Проверка по вертикали
        for (i = 0; i < size-2; i++) {
            if (pole[i][j] == 1 && pole[i+1][j] == 1 && pole[i+2][j] == 1) {
                victory = 1;
                break;
            }
            if (pole[i][j] == 2 && pole[i+1][j] == 2 && pole[i+2][j] == 2) {
                victory = 2;
                break;
            }}

      }

    for (i = 0; i < size; i++) {             //Проверка по одной диагонали
        for (j = 0; j < size; j++) {
            if (pole[i][j] == 1 && pole[i+1][j+1]==1 && pole[i+2][j+2]==1)
            {
                victory = 1;
                break;
            }
            if (pole[i][j] == 2 && pole[i+1][j+1]==2 && pole[i+2][j+2]==2)
            {
                victory = 2;
                break;
            }
        }
        }


    for (i = 0; i < size; i++) {             //Проверка по другой диагонали
        for (j = 0; j < size; j++) {
            if (pole[i][j] == 1 && pole[i + 1][j - 1] == 1 && pole[i + 2][j - 2] == 1)
            {
                victory = 1;
                break;
            }
            if (pole[i][j] == 2 && pole[i + 1][j - 1] == 2 && pole[i + 2][j - 2] == 2)
            {
                victory = 2;
                break;
            }
        }
    }



    for (j = 0; j < size; j++) {            //Проверка на ничью
        for (i = 0; i < size; i++) {
            if (pole[i][j] != 0 && victory == 0) c++;

        }
        }
    if (c==size*size) victory=3;

    return victory;
}

void congratulation(int victory)        //Поздравление победителя / объявление ничьей
{
    if (victory==1) printf ("Поздравляем крестик с победой!\n");
    if (victory==2) printf ("Поздравляем нолик с победой!\n");
    if (victory==3) printf ("Ничья!\n");
}
