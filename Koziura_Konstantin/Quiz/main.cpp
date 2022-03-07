#include <iostream>
#include <ctime>

class user {
public:
    user();
    void set_name();
    void get_name();
    void change_score(unsigned int points);
    void get_score();
private:
    std::string Name;
    unsigned int sum_score;
};

class question{
public:
    question();
    void set_question(std::string Que);
    void set_answers(std::string A1,std::string A2, std::string A3, std::string A4);
    void sent_questions();
    unsigned int qet_answer();
    void set_points(unsigned int points);
protected:
    std::string Question_str;
    unsigned int Points;
private:
    std::string RightAnswer;
    std::string Answers_array[4];

};

class Str_question:public question{
public:
    Str_question();
    void set_answers(std::string A);
    void sent_questions();
    unsigned int qet_answer();
private:
    std::string RightAnswer;
    //std::string Question_str;
    //unsigned int Points;
};

user::user(){
    sum_score = 0;
    Name = "";
}

void user::set_name() {
    std::cin>> Name;
}
void user::get_name() {
    std::cout<<Name<<"\n";
}

void user::change_score(unsigned int points) {
    sum_score+=points;
}

void user::get_score() {
    std::cout<<"Score: "<<sum_score;
}

question::question(){
    Question_str = "";
    RightAnswer="";
    Points = 0;
}

void question::set_question(std::string Que) {
    Question_str=Que;
}
void question::set_answers(std::string A1, std::string A2, std::string A3, std::string A4) {
    Answers_array[0] = A1;
    Answers_array[1] = A2;
    Answers_array[2] = A3;
    Answers_array[3] = A4;
    RightAnswer = A1;
}

void question::sent_questions() {

    srand(time(0));
    for (int i = 0; i < 4; ++i)
        std::swap(Answers_array[i], Answers_array[std::rand() % 4]);

    std::cout<<"Q:"<<Question_str<<"\n";
    for (int i = 0; i < 4; ++i) {
        std::cout<<i+1<<"."<<Answers_array[i]<<"\n";
    }
    std::cout<<"\n";
}

void question::set_points(unsigned int points) {
    Points=points;
}

unsigned int question::qet_answer() {
    char i=0;
    std::cout<<"Please enter the number of right answer\n";
    while(i<49 || i>52) {
        std::cin >> i;
    }
    i-=49;
    if (Answers_array[i] == RightAnswer){
        std::cout<<"You are right!\n\n";
        return Points;
    }
    else
    {
        std::cout<<"You have made mistake\n\n";
        return 0;
    }

}

Str_question::Str_question() {
    Points=0;
    Question_str = "";
    RightAnswer = "";
}

void Str_question::set_answers(std::string A) {
    RightAnswer = A;
}

void Str_question::sent_questions() {
    std::cout<<"Q:"<<Question_str<<"\n\n";
}

unsigned int Str_question::qet_answer(){
    std::string Answer;
    std::cout<<"Please enter the right answer by text\n";
    std::cin>>Answer;

    if (Answer == RightAnswer){
        std::cout<<"You are right!\n\n";
        return Points;
    }
    else
    {
        std::cout<<"You have made mistake\n\n";
        return 0;
    }
}

int main() {
    user player;
    std::cout<<"Please enter your username\n";
    player.set_name();
    //system("cls");

    std::cout<<"Hello, ";
    player.get_name();
    std::cout<<"I want you to answer a few questions\n\n";

    question q1;
    q1.set_question("What should be used if the mechanism does not move, but should?");
    q1.set_answers("WD40","Tape", "Nothing","Blue electrical tape");
    q1.set_points(100);

    q1.sent_questions();
    player.change_score(q1.qet_answer());

    Str_question q2;
    q2.set_question("BLUE pill or RED pill?");
    q2.set_points(300);
    q2.set_answers("None");

    q2.sent_questions();
    player.change_score(q2.qet_answer());

    std::cout<<"Quiz end!\n";
    player.get_score();

    return 0;
}

