#include <iostream>
#include <string>
using namespace std;
bool getting_answer(char right_answer);

void greeting_print(){
    string user;
    cout << "We're glad to see you!\n" << "In order to start, please, write your name." << endl;
}

class Questions{
private:
    string title;
    char right_answer;
public:
    Questions(string new_title, char answer) {
        title = new_title;
        right_answer = answer;
        Print_question();
    }
    char GetRightAnswer() {
        return right_answer;
    }
    void Print_question() {
        cout << title << "\n" << endl;
    }
    void answers_print(string answer1, string answer2, string answer3) {
        cout << answer1 << "\t" << answer2 << "\t" << answer3 << "\nEnter your answer below" << endl;
    }
};

class User{
private:
    string name;
    int points = 0;
public:
    void get_name() {
        cin >> name;
    }
    void changing_score(bool check) {
        if (check) {
            points++;
        }
    }
    void final_score() {
        cout << name << "\'s score: " << points << endl;
        if (points <= 1) {
            cout << "Maybe, literature is just not your cup of tea" << endl;
        }
        else if (points <= 3) {
            cout << "You did well" << endl;
        }
        else if (points == 4) {
            cout << "You\' re good enough in classical literature" << endl;
        }
        else if (points == 5) {
            cout << "Great! We\'re really proud of you!" << endl;
        }
    }
};

bool getting_answer(char right_answer) {
    char user_answer;
    cin >> user_answer;
    if (toupper(user_answer) == right_answer) {
        return true;
    }
    else {
        return false;
    }
}

int main() {
    greeting_print();
    User player;
    player.get_name();

    Questions first("Who is the author of the book \"The great Gatsby\"?", 'B');
    first.answers_print("A) William Faulkner", "B) F.Scott Fitzgerald", "C) George Orwell");
    player.changing_score(getting_answer(first.GetRightAnswer()));

    Questions second("Who is the author of \"Divine Comedy\"?", 'B');
    second.answers_print("A) Goethe", "B) Dante", "C) Shakespeare");
    player.changing_score(getting_answer(second.GetRightAnswer()));

    Questions third("Who wrote \"Brave New World\"?", 'A');
    third.answers_print("A) Aldous Huxley", "B) Hermann Hesse", "C) Thomas Mann");
    player.changing_score(getting_answer(third.GetRightAnswer()));

    Questions fourth("Who is the author of the book \"The winter of our discontent\"?", 'C');
    fourth.answers_print("A) Jack Kerouac", "B) F.Scott Fitzgerald", "C) John Steinbeck");
    player.changing_score(getting_answer(fourth.GetRightAnswer()));

    Questions fifth("Who wrote \"Martin Eden\"?", 'B');
    fifth.answers_print("A) William Faulkner", "B) Jack London", "C) Aldous Huxley");
    player.changing_score(getting_answer(fifth.GetRightAnswer()));

    player.final_score();
    return 0;
}
