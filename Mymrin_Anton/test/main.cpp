#include <iostream>

using namespace std;

int score=0;

class User {
public:
    string user_name;
public:
    void input_name();
    static void user_score();
};

class Question {
public:
    int answer;
private:
    int correct_answer;
public:
    void set_question(string question, string a1, string a2, string a3, string a4,int correct);
    int user_answer();
};

void User::input_name() {
    cout << "your name?"<< endl;
    cin >> user_name;
    cout << "you are "<< user_name <<"!"<< endl;
}

void Question::set_question(string q, string a1, string a2, string a3, string a4,int correct) {
    cout<<"vopros: "<<q<<endl;
    cout<<"1) "<<a1<<endl;
    cout<<"2) "<<a2<<endl;
    cout<<"3) "<<a3<<endl;
    cout<<"4) "<<a4<<endl;
    correct_answer=correct;
}

int Question::user_answer() {
    cout << "otvet?"<<endl;
    cin >> answer ;
    if (answer==correct_answer){
        cout << "correct!"<<endl;
        score++;
    } else{
        cout << "wrong)"<<endl;
    }
    return score;
}

void User::user_score() {
    cout<<"your score is "<<score;
    if (score==3)
        cout<<"! COOL!!!"<<endl;
    else cout<<"... no cool(("<<endl;
}
int main() {
   User user;
   user.input_name();

   Question q0;
   q0.set_question("2+2","2","22","4","5",3);
   q0.user_answer();
   Question q1;
   q1.set_question("who says woof?","chicken","worm reducer","fish","dog",4);
   q1.user_answer();
   Question q2;
   q2.set_question("what is your name?",user.user_name,"nagibator2009","NaN","Barack Obama",1);
   q2.user_answer();
   user.user_score();

    return 0;
}
