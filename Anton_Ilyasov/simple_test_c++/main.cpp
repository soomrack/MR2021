#include <iostream>
#include <string.h>

#define COUNTQUESTION 4
using namespace std;

class User
{
public:
	string name;
	string answer;
	int correct_answer;
	int incorrect_answer;
	User();
};

User::User() {
	name = "";
	answer = "";
	correct_answer = 0;
	incorrect_answer = 0;
}

class Test
{
public:
	string question;
	string correct_answer;
	Test();
	void fill_question(int number);
	void print_question();
};

Test::Test() {
	question = "";
	correct_answer = "";
}

void Test::fill_question(int number) {
	switch (number)
	{
	case 1:
	{
		question = "Вы пересекаете мост через реку, которая течет справа налево. \n"
			"Все встречные машины едут на север. В каком направлении течет река? ";
		correct_answer = "восток";
		break;
	}
	case 2:
	{
		question = "Введите следующее число: 41, 34, 28, 23, 19...";
		correct_answer = "16";
		break;
	}
	case 3:
	{
		question = "Сколько пар лап всего у 3 голубей и 4 собак?";
		correct_answer = "11";
		break;
	}
	case 4:
	{
		question = "Если 1+1=10, то чему равно 1+10?";
		correct_answer = "11";
		break;
	}
	}
}

void Test::print_question() {
	cout << endl << question << endl << endl;
}

User User1;
void greeting() {
	cout << "Введите ваше имя" << endl;
	cin >> User1.name;
	cout << "Поехали!" << endl;
	cout << "Пожалуйста, вводите ответ с клавиатуры с маленькой буквы :)" << endl;
}

void test() {
	Test Test1;
	for (int i = 1; i <= COUNTQUESTION; i++)
	{
		Test1.fill_question(i);
		Test1.print_question();
		cin >> User1.answer;
		if (User1.answer == Test1.correct_answer)
		{
			User1.correct_answer++;
		}
		else
		{
			User1.incorrect_answer++;
		}
	}
}

void get_results() {
	if (User1.correct_answer >= 3)
	{
		cout << "\nВы молодец!" << endl;
	}
	else
	{
		cout << "\nНу что ж, работайте над собой!" << endl;
	}
	cout << "Правильных ответов = " << User1.correct_answer << endl;
	cout << "Неправильных ответов = " << User1.incorrect_answer << endl;
}

int main(void)
{
	setlocale(LC_ALL, "ru");
	greeting();
	test();
	get_results();
}