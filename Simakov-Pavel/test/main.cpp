#include <iostream>
#include <conio.h>
#include <string.h>

using namespace std;

class User
{
    public:
        string name;
        int answer;
        int correct;
        int incorrect;
    public:
        User();
        void Counter(bool x);
};

User::User()
{
    answer = 0;
    name = "";
    correct = 0;
    incorrect = 0;
}

void User::Counter(bool x)
{
    if(x) correct++;
    else incorrect++;
}

class Test
{
public:
    int number;
    string question;
    string ans1;
    string ans2;
    string ans3;
    int correct_ans;
    Test();
    void fill_question(int nmb);
    void print_question();
    bool check(int ans);
};

Test::Test()
{
    number = 0;
    correct_ans = 0;
    question = "";
    ans1 = "";
    ans2 = "";
    ans3 = "";
}

void Test::fill_question(int nmb)
{
    switch (nmb)
    {
        case 0:
        {
            question = "Light wind blowing on the coast and changing direction 2 times a day";
            ans1 = "Golfstream";
            ans2 = "Breeze";
            ans3 = "Monsoon";
            correct_ans = 2;
            break;
        }
        case 1:
        {
            question = "How long did the Hundred Years War last?";
            ans1 = "116 years";
            ans2 = "100 years";
            ans3 = "97 years";
            correct_ans = 1;
            break;
        }
        case 2:
        {
            question = "The vessels through which blood flows from the heart are called ...";
            ans1 = "Arteries";
            ans2 = "Capillaries";
            ans3 = "Veins";
            correct_ans = 1;
            break;
        }
        case 3:
        {
            question = "Diamond is a solid form of the element ...";
            ans1 = "Silicon";
            ans2 = "Phosphorus";
            ans3 = "Carbon";
            correct_ans = 3;
            break;
        }
        case 4:
        {
            question = "Plants are ...";
            ans1 = "Decomposers";
            ans2 = "Consumers";
            ans3 = "Producers";
            correct_ans = 3;
            break;
        }
    }
}

void Test::print_question()
{
    std::cout << question << std::endl;
    std::cout << "1. " << ans1 << std::endl;
    std::cout << "2. " << ans2 << std::endl;
    std::cout << "3. " << ans3 << std::endl;
}

bool Test::check(int ans)
{
    if (ans == correct_ans) return true;
    else return false;
}

int main() {
    User Examinee;
    std::cout << "Hello, how should I call you?" << std::endl;
    std::cin >> Examinee.name;
    std::cout << "let's start" << std::endl;
    Test Task;
    for (Task.number; Task.number < 5; Task.number++)
    {
        Task.fill_question(Task.number);
        Task.print_question();
        std::cin >> Examinee.answer;
        Examinee.Counter(Task.check(Examinee.answer));
    }
    if (Examinee.correct > 3) std::cout << "Good results, " << Examinee.name << std::endl;
    else std::cout << "You should be ashamed, " << Examinee.name << std:: endl;
    std::cout << "correct - " << Examinee.correct << ", incorrect - " << Examinee.incorrect << std::endl;
    return 0;
}
