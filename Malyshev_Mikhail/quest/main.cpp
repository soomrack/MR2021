#include <iostream>
#include <conio.h>
#include <string>
using namespace std;

int count_score;

class User {
public:
	string name;
public:
	void get_name();
	void score();
};

void User::get_name() {
	cout << "hello, before we start, plese enter your name" << endl;
	cin >> name;
}

void User::score() {
	cout << name << ", you scored " << count_score << endl;
}


class Question {
	public:
		string answer;
	private:
		string correct_answer;
	public:
		void options(string quest, string opt1, string opt2, string opt3, string opt4, string correct_answer);

};


void Question::options(string quest, string opt1, string opt2, string opt3, string opt4, string correct_answer) {
	cout << quest << endl;
	cout << opt1 << endl;
	cout << opt2 << endl;
	cout << opt3 << endl;
	cout << opt4 << endl;
	cin >> answer;

	if (answer == correct_answer) {
		cout << "yes" << endl;
		count_score++;
	}
	else {
		cout << "no" << endl;
	}

}

int main()
{
	User User1;
	User1.get_name();

	Question Question1;
	Question1.options("6 - 9 = ?", "1) 4", "2) -3", "3) 1", "4) 6", "2");

	Question Question2;
	Question2.options("how many strings does a guitar have?", "1) 1", "2) 5", "3) 6", "4) 13", "3");

	Question Question3;
	Question3.options("sine 30 degrees", "1) 1/2", "2) 0", "3) 1", "4) -1/2", "1");

	User1.score();
}
