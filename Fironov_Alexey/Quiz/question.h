#pragma once
#ifndef QUIZ_QUESTION_H
#define QUIZ_QUESTION_H
#include "string"
#include "team.h"
/*
class Question_Head
{
    public:
//---------------------procedures--------------------------------------------
        void save ();                            //Save team question results into file
        void set_text (std::string);             //Question body
        void set_correct_answer (std::string);   //True answer
        void set_team_answer  (std::string);     //Function to get team's answer
//----------------------variables--------------------------------------------
    private:
        unsigned int question_number;       // Question serial number variable
        std::string question_body;          // Main text of the question
        std::string correct_answer;         // Correct answer for round-button question
        std::string team_answer;            // Answer for round-button question
        double time;                        // Team answering time

};*/

class String_Question
{
//============================Destructor=====================================
    public:

        void save ();                            //Save team question results into file
        ~String_Question();

//============================Constructor====================================

        String_Question (unsigned int);

//---------------------procedures--------------------------------------------
        void set_text (std::string);             //Question body
        std::string set_correct_answer (std::string);//True answer
        unsigned int set_team_answer ();         //Function to get team's answer

//----------------------variables--------------------------------------------
    private:
        unsigned int question_number;       // Question serial number variable
        std::string question_body;          // Main text of the question
        std::string correct_answer;        // Correct answer for round-button question
        std::string team_answer;            // Answer for round-button question
        time_t duration;                    // Team answering time

};

class Fixed_Question    // Question with fixed answers (Round-Button type)
{
    public:
//============================Destructor=====================================

        void save ();                            //Save team question results into file
        ~Fixed_Question();

//============================Constructor====================================

        Fixed_Question (unsigned int);

public:
//---------------------procedures--------------------------------------------
    void set_text (std::string);             //Question body
    unsigned int set_correct_answer (unsigned int);  //True answer
    unsigned int set_team_answer ();     //Function to get team's answer
    void set_answers (std::string ans_one,std::string ans_two,   //Four places for answers
                      std::string ans_three, std::string ans_four);
//----------------------variables--------------------------------------------
    std::string answer [4];             // Variations of several answer variations

private:
    unsigned int question_number;       // Question serial number variable
    std::string question_body;          // Main text of the question
    unsigned int correct_answer;        // Correct answer for round-button question
    std::string team_answer;            // Answer for round-button question
    time_t duration;                        // Team answering time

};

#endif //QUIZ_QUESTION_H