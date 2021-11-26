#include <iostream>
#include <string.h>

#define COUNTQUESTION 5
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
		question = "You cross a bridge over a river that flows from right to left. \n"
				   "All oncoming cars are going north.In which direction does the river flow ? ";
		correct_answer = "East";
		break;
	}
	case 2:
	{
		question = "Continue the sequence of numbers: 41, 34, 28, 23, 19...";
		correct_answer = "16";
		break;
	}
	case 3:
	{
		question = "How many pairs of paws do 3 pigeons and 4 dogs have in total?";
		correct_answer = "11";
		break;
	}
	case 4:
	{
		question = "If 1+1=10, how much is 1+10?";
		correct_answer = "11";
		break;
	}
	}
}

void Test::print_question() {
	cout<< endl << question<< endl<<endl;
}

User User1;
void greeting() {
	cout << "Yours name" << endl;
	cin >> User1.name;
	cout << "Let's go!" << endl;
	cout << "Please, enter the answers from the keyboard :)" << endl;
}

void test() {
	Test Test1;
	for (int i = 1; i < COUNTQUESTION; i++)
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
		cout << "\nyou're good!" << endl;
	}
	else
	{
		cout << "\nwork harder!" << endl;
	}
	cout << "correct answers= " << User1.correct_answer << endl;
	cout << "incorrect answers= " << User1.incorrect_answer << endl;
}

int main(void)
{
	greeting();
	test();
	get_results();
}