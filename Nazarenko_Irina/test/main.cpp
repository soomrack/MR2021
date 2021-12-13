#include <iostream>
#include <conio.h>
using namespace std;
int correct=0;
int mistakes=0;

class Task {

public:

    int correct_answer;
private:

    string answer;
public:
    void Question(string question, string answer01, string answer02, string answer03, string correct_answer);

};



void Task::Question(string question, string answer01, string answer02, string answer03, string correct_answer){

    cout<<question<<endl;
    cout<<answer01<<endl;
    cout<<answer02<<endl;
    cout<<answer03<<endl;
    cin>>answer;

    if (answer==correct_answer)
    {cout<<"Correct"<<endl;
        correct++;}
    else {cout<<"Wrong"<<endl;
        mistakes++; };

}


class User {
public:
    string name;

public:
    void get_name();
    void hello();
    void Final_Score();
};

void User::Final_Score()
{
  cout<<"Totally correct:"<<correct<<endl;
  cout<<"Totally wrong:"<<mistakes<<endl;
};

void User::hello()
{ cout<<"Hello! Please, print your name."<<endl;};

void User:: get_name(){
cin>>name;
};


int main() {
    User player;
    player.hello();
    player.get_name();
    Task Question1;
    Question1.Question("2+2","1)4","2)8","3)3", "1");

    Task Question2;
    Question2.Question("8/2","4","8","3", "1");
    Task Question3;
    Question3.Question("33+77","100","110","8", "2");
    player.Final_Score();
}