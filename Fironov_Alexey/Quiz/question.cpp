#include <iostream>
#include <chrono>
#include "question.h"
#include <string>
#include "fstream"


//======================================Constructors===========================================

Fixed_Question::Fixed_Question (unsigned int number)
{
    Fixed_Question::question_number = number;
}

Fixed_Question::~Fixed_Question()
{
    Fixed_Question::save();
}

//--------------------------------------------------------------------------------------------
String_Question::String_Question (unsigned int number)
{
    String_Question::question_number = number;
}

String_Question::~String_Question()
{
    String_Question::save();
}
//========================================Methods=============================================
//--------------------------------Set_Text_&_Question_Number----------------------------------

void Fixed_Question::set_text (std::string quest_text) {
    Fixed_Question::question_body = quest_text;
    std::cout <<quest_text << "\n";
}

void String_Question::set_text (std::string quest_text) {
    String_Question::question_body = quest_text;
    std::cout <<quest_text << "\n";
}
//============================================Answers==========================================
//----------------------------------------Fixed_Question---------------------------------------
void Fixed_Question::set_answers(std::string ans_1, std::string ans_2,
                                   std::string ans_3,std::string ans_4)
{
    Fixed_Question::answer[0] = ans_1;
    Fixed_Question::answer[1] = ans_2;
    Fixed_Question::answer[2] = ans_3;
    Fixed_Question::answer[3] = ans_4;
    std::cout <<Fixed_Question::answer[0] <<"\n" << Fixed_Question::answer[1] << "\n"
              <<Fixed_Question::answer[2] <<"\n" << Fixed_Question::answer[3] << "\n\n";
}

unsigned int Fixed_Question::set_correct_answer (unsigned int correct_answer)
{
    Fixed_Question::correct_answer = correct_answer;
    return Fixed_Question::correct_answer;
}

std::string String_Question::set_correct_answer (std::string correct_answer)
{
    String_Question::correct_answer = correct_answer;
    return String_Question::correct_answer;
}
//---------------------------------------Set_Answer-------------------------------------------
unsigned int Fixed_Question::set_team_answer ()
{
    auto now = std::chrono::system_clock::now();
    time_t start = std::chrono::system_clock::to_time_t(now);
//---------------------------------------------------------------------------------------------
        std::cout<<"Please enter your answer\n";
        char i = 0;
        while(i<49 || i>52) {
        std::cin >> i;
        }
        i-=49;
    if (Fixed_Question::answer[i] == Fixed_Question::answer[Fixed_Question::correct_answer - 1])
    {
        std::cout<<"You are right!\n\n";
        //------------------
        auto end = std::chrono::system_clock::now();
        time_t question_duration = (std::chrono::system_clock::to_time_t(end) - start);
        Fixed_Question::duration = question_duration;
        //------------------
        return 1;
    }
    else
    {
        std::cout/*<<"You have made mistake\n\n" */<< Fixed_Question::answer[i] << "    " << Fixed_Question::answer[Fixed_Question::correct_answer - 1];
        //------------------
        auto end = std::chrono::system_clock::now();
        time_t question_duration = (std::chrono::system_clock::to_time_t(end) - start);
        Fixed_Question::duration = question_duration;
        //------------------
        return 0;
    }

//---------------------------------------------------------------------------------------------

}
//=============================================================================================
unsigned int String_Question::set_team_answer () {
    auto now = std::chrono::system_clock::now();
    time_t start = std::chrono::system_clock::to_time_t(now);
//---------------------------------------------------------------------------------------------
    std::cout << "Please enter your answer\n";
    std::cin >> String_Question::team_answer;

    if (String_Question::team_answer == String_Question::correct_answer) {
        std::cout << "You are right!\n\n";
        //------------------
        auto end = std::chrono::system_clock::now();
        time_t question_duration = (std::chrono::system_clock::to_time_t(end) - start);
        String_Question::duration = question_duration;
        //------------------
        return 1;
    } else {
        std::cout << "You have made mistake\n\n";
        //------------------
        auto end = std::chrono::system_clock::now();
        time_t question_duration = (std::chrono::system_clock::to_time_t(end) - start);
        String_Question::duration = question_duration;
        //------------------
        return 0;
        String_Question::duration = question_duration;
    }
}
//----------------------------------------Save----------------------------------------
void Fixed_Question::save ()
{
    std::ofstream fout("questions.txt", std::ios::app);

    fout <<"You have spent"<<Fixed_Question::duration<<"seconds for question number "<<Fixed_Question::question_number
         <<": "<<Fixed_Question::question_body<<"\n"<<"  Answers:\n";

    for (int i = 0; i < 3; ++i) {
        fout <<"   "<<(i+1)<<") " <<Fixed_Question::answer[i]<<"\n";
    }

    fout <<"   Your answer: "<<Fixed_Question::team_answer<<" "<<Fixed_Question::team_answer
    <<"   The correct answer: "<<Fixed_Question::correct_answer;
    fout << std::endl;
    fout.close();
}

void String_Question::save ()
{
    std::ofstream fout("questions.txt", std::ios::app);

    fout <<"You have spent"<<String_Question::duration<<"seconds for question number "<<String_Question::question_number
    <<": "<<String_Question::question_body<<"\n"<<"  Your answer:"<<String_Question::team_answer<<
    "   The correct answer: "<<String_Question::correct_answer;

    fout << std::endl;
    fout.close();
}