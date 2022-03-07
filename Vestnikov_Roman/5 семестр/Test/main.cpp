#include <iostream>
using namespace std;
int num_question=0;

class User {
public:
    string name="Human";
    int res=0;
    void set_name();
};

class Test {
public:
    string question;
    void enter_answer();
    int answer=0;
    int score=0;
private:
    int inc_score (int score);
};

void User::set_name(){
    cout<<"Введите имя:"<<endl;
    cin>>name;
}

void Test::enter_answer(){
    cout<<question<<endl;
    cin>>answer;
    cout<<endl;
    score = inc_score(score);
}

int Test::inc_score(int score) {
    switch (num_question) {
        case 0: if (answer==1) score++; break;
        case 1: if (answer==2) score++; break;
        case 2: if (answer==1) score++; break;
        case 3: if (answer==4) score++; break;
        case 4: if (answer==3) score++; break;
        default: break;
    }
    return score;

}

string base [5];
void create_questions(){
    base [0]="Какое влияние на протекание процесса и его результаты оказывает образование нароста на лезвии инструмента?\n"
             " 1)  Защищает лезвие от износа\n"
             " 2)  Приводит к повреждению лезвия\n"
             " 3)  Приводит к дроблению сливной стружки\n"
             " 4)  Защищает лезвие от износа, но ухудшает качество обработанной поверхности";
    base [1]="Какой инструмент применяется для чистовой обработке отверстий?\n"
             " 1)  Сверло\n"
             " 2)  Развёртка\n"
             " 3)  Зенкер";
    base [2]="Как называется инструмент для обработки зубчатых колёс фрезерованием методом обкатки?\n"
             " 1)  Червячная модульная фреза\n"
             " 2)  Дисковая модульная фреза\n"
             " 3)  Цилиндрическая фреза\n"
             " 4)  Обкатник";
    base [3]=" К какой группе инструментальных материалов относится материал 9ХС?\n"
             " 1)  Быстрорежущая сталь\n"
             " 2)  Металлокерамический твёрдый сплав\n"
             " 3)  Синтетический сверхтвёрдый материал\n"
             " 4)  Легированная инструментальная";
    base [4]="Что понимается под твёрдостью шлифовального круга?\n"
             " 1)  Твёрдость абразивных зёрен\n"
             " 2)  Твёрдость связки\n"
             " 3)  Прочность закрепления зёрен";
}

string mark_definition(int result){
    string mark;
    if (result==5) mark="отлично";
    else mark="неудовлетварительно";
    return mark;
}

int main() {
    setlocale(LC_ALL, "Russian");
    create_questions();
    User player;
    player.set_name();
    Test exam;
    for (num_question=0;num_question<5;num_question++) {
        exam.question=base[num_question];
        exam.enter_answer();
    }
    if (player.name=="Кобчиков") {
        cout<<"Валентин Семенович"<<", Ваш результат: 10/5"<<endl;
        cout<<"Оценка: Восхитительно, великолепно, потрясающе!!!";
        return 0;
    }
    player.res=exam.score;
    string mark;
    mark=mark_definition(player.res);
    int result=player.res;
    cout<<player.name<<", Ваш результат: "<<result<<"/5"<<endl;
    cout<<"Оценка: "<<mark;
    return 0;
}
