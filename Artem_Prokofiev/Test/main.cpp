#include <iostream>
#include <string>

int correct = 0;
int mistakes = 0;
int exp = 0;

class User{
public:
    std::string name;
    int age;
public: User();
    void print_manual();
};

User::User(){
    std::cout << "Введите Ваше имя\n";
    std::cin >> name;
    std::cout << name;
    std::cout << " Введите Ваш возраст\n";
    std::cin >> age;
    std::cout << "\n";
}

void User::print_manual() {
    std::cout << "Сейчас Вы пройдёте небольшой тест. Для выбора ответа \n"
                 "введите номер выбранного Вами варианта. Некорректные данные \n"
                 "в ответе приравниваются к ошибке. Будьте внимательны. Удачи.\n";
}

class Task {
public:
    std::string question;

    std::string answer01;
    std::string answer02;
    std::string answer03;
private:
    int correct_answer = 0;

public:
    void print_question1();
    void print_question2();
    void print_question3();
};


void Task::print_question1() {
    question = "Вопрос 1: 2+2=";
    answer01 = "1) 3";
    answer02 = "2) 4";
    answer03 = "3) 5";
    correct_answer = 2;

    std::cout << question << std::endl;
    std::cout << answer01 << std::endl;
    std::cout << answer02 << std::endl;
    std::cout << answer03 << std::endl;
    int answer;
    std::cout << "Введите номер выбранного ответа\n";
    std::cin >> answer;
    if (answer == correct_answer)
    {
        std::cout << "И это правильный ответ\n";
        correct++;
        exp = exp + 100;
    }
    else {
        std::cout << "Неверно(((\n";
        mistakes++;
    }
}

void Task::print_question2() {
    question = "Вопрос 2: 2+3=";
    answer01 = "1) 3";
    answer02 = "2) 4";
    answer03 = "3) 5";
    correct_answer = 3;

    std::cout << question << std::endl;
    std::cout << answer01 << std::endl;
    std::cout << answer02 << std::endl;
    std::cout << answer03 << std::endl;
    int answer;
    std::cout << "Введите номер выбранного ответа\n";
    std::cin >> answer;
    if (answer == correct_answer)
    {
        std::cout << "И это правильный ответ\n";
        correct++;
        exp = exp + 100;
    }
    else {
        std::cout << "Неверно(((\n";
        mistakes++;
    }
}

void Task::print_question3() {
    question = "Вопрос 3: 220/44=";
    answer01 = "1) 4";
    answer02 = "2) 6";
    answer03 = "3) 5";
    correct_answer = 3;

    std::cout << question << std::endl;
    std::cout << answer01 << std::endl;
    std::cout << answer02 << std::endl;
    std::cout << answer03 << std::endl;
    int answer;
    std::cout << "Введите номер выбранного ответа\n";
    std::cin >> answer;
    if (answer == correct_answer)
    {
        std::cout << "И это правильный ответ\n";
        correct++;
        exp = exp + 100;
    }
    else {
        std::cout << "Неверно(((\n";
        mistakes++;
    }
}

int main() {
    User Bob;
    Bob.print_manual();
    Task ONE;
    ONE.print_question1();
    Task TWO;
    TWO.print_question2();
    Task Three;
    TWO.print_question3();
    std::cout << "Имя:\t";
    std::cout << Bob.name;
    std::cout << "\n";
    std::cout << "Возраст:\t";
    std::cout << Bob.age;
    std::cout << "\n";
    std::cout << "Итого правильных ответов:\t";
    std::cout << correct;
    std::cout << "\n";
    std::cout << "Итого неправильных ответов:\t";
    std::cout << mistakes;
    std::cout << "\n";
    std::cout << "Итого очков:\t";
    std::cout << exp;
    return 0;
}
