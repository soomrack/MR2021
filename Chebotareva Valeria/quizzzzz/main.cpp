#include <iostream>
#include <string.h>

using namespace std;
int answer;
int score;

class User {
public:
    string name;
    void Name();
    void Score();
};

void User::Name() {
    cout << "What is your name?" << endl;
    cin >> name;
}

void User::Score() {
    if (score >= 3) {
        cout << "Well done, "<<name<< "!!! Your score:" << score << endl;
    } else {
        cout << "lets try one more time))) Your score:" << score << endl;
    }
}

class Question {
public:
    string question;
    string a;
    string b;
    string c;
    string d;
    int correct_answer;


    void print_question(string question, string a, string b, string c, string d, int correct_answer);
};

void Question::print_question(string question, string a, string b, string c, string d, int correct_answer) {
    cout << question << endl;
    cout << "1." << a << endl;
    cout << "2." << b << endl;
    cout << "3." << c << endl;
    cout << "4." << d << endl;
    cout << "\n" << "What is your answer?(in number)" << endl;
    cin >> answer;
    if (answer == correct_answer) {
        cout << "\n" << "Correct!" << endl;
        score++;
    } else {
        cout << "\n" << "Wrong :(" << endl;
    }
}

int main() {
    User User1;
    User1.Name();
    Question Question1;
    Question1.print_question("2*2*2=", "IDK", "8", "9", "6", 2);

    Question Question2;
    Question2.print_question("какое растение самое красивое", "кактус valera", "лук", "одуванчик", "алоэ", 1);

    Question Question3;
    Question3.print_question("Как называется инструмент который помогает фиксикам работать?", "отвертка", "молоток",
                       "помагатор", "перфоратор", 3);
    Question Question4;
    Question4.print_question("Как зовут собаку которую дразнят фиксики?", "Ворчун", "Злючка", "Шарик", "Кусачка", 4);

    Question Question5;
    Question5.print_question("понравился ли Вам тест?", "очень очень очень понравился!", "нормально",
                       "просто ужас!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", "да!!!", 1);

    User1.Score();
    return 0;
}
