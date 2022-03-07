#include <iostream>
using namespace std;
char answer;
int n;
int main() {
	cout << "Match the right answer\n";
	cout << "1) To stop something from being active, either temporarily or permanently\n";
	cout << "A)Append  B)Break up  C)Depend D)Suspend\n";
	cout << "Choose the right answer\n";
	cin  >> answer;
	if (answer == 'D') {
		cout << "That's right!\n";
		n++;
	}
	else {
		cout << "That's wrong! Try your best!\n";

	}
	cout << "2) A particular time, especially when something happens or has happened:\n";
	cout << "A)Timeframe  B)Schedule  C)Occasion D)Layout\n";
	cout << "Choose the right answer\n";
	cin >> answer;
	if (answer == 'C') {
		cout << "That's right!\n";
		n++;
	}
	else {
		cout << "That's wrong! Try your best!\n";
	}
	cout << "3) A flat shape with four 90° angles and four sides, with opposite sides of equal length\n";
	cout << "A)Square  B)Rectangle  C)Triangle D)Circle\n";
	cout << "Choose the right answer\n";
	cin >> answer;
	if (answer == 'B') {
		cout << "That's right!\n";
		n++;
	}
	else {
		cout << "That's wrong! Try your best!\n";
	}
	cout << "4) Not severe or forceful enough, especially in criticizing or punishing someone who has done something wrong:\n";
	cout << "A)Forceful  B)Adorable  C)Dwelling  D)Mild\n";
	cout << "Choose the right answer\n";
	cin >> answer;
	if (answer == 'D') {
		cout << "That's right!\n";
		n++;
	}
	else {
		cout << "That's wrong! Try your best!\n";
	}
	cout << "5) Being the only existing one of its type or, more generally, unusual, or special in some way:\n";
	cout << "A)Unique  B)Skillful  C)Admirable D)Respectable\n";
	cout << "Choose the right answer\n";
	cin >> answer;
	if (answer == 'A') {
		cout << "That's right!\n";
		n++;
	}
	else {
		cout << "That's wrong! Try your best!\n";
	}
	
	cout << "Your score is ";
	cout <<  n << " out of 5";
}