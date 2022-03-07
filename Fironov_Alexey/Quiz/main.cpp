#include <iostream>
#include <string>
#include "team.h"
#include "question.h"

//Formula Student Quiz

int main() {

//-----------------------------Team_initialization--------------------------------------
    std::cout << "Please enter your team\n";
    std::string name;
    std::getline(std::cin, name);

    std::cout << "Now enter your captain name\n";
    std::string captain;
    std::getline(std::cin, captain);

    unsigned int answers = 0;
    double team_time = 0;
    Team *team = new Team(name, captain);

//----------------------------End_of_initialization-------------------------------------
    time_t time_start = team->start_time();

//-----------------------------Question_base_header-------------------------------------
/*
 * Question *question = new Question (q_num);
 */
//----------------------------Question_base_footer---------------------------------------
/*
 * q_num++;
 */


    unsigned int num = 1; //Set the number of the first question
    std::cout << "Now you have to answer several questions\n\n";

//--------------------------------First_question-----------------------------------------
    Fixed_Question *question_1 = new Fixed_Question(num);

    question_1->set_text("How many cones are placed on a Skidpad track?");
    question_1->set_answers("58", "63", "59", "54");
    question_1->set_correct_answer(1);

    unsigned int temp = (team->get_points_num()) + (question_1->set_team_answer());
    team->update_points_num(temp);

//--------------------------------------------------------------------------------------
    delete question_1;
    num++;

//---------------------------------Second_question--------------------------------------
    String_Question *question_2 = new String_Question(num);

    question_2->set_text("Mass: 2,4 kg; specific heat capacity 900 J/kgK; heating power 2000W.\n"
                         "Calculate the time in seconds [s] necessary to heat up this ideal block\n"
                         "to 80 deg C starting at25 deg C./n Round to nearest integer.\n");
    question_2->set_correct_answer("59");

    temp = (team->get_points_num()) + (question_2->set_team_answer());
    team->update_points_num(temp);

//--------------------------------------------------------------------------------------
    delete question_2;
    num++;
//--------------------------------------------------------------------------------------

    std::cout << "The quiz has been ended!\n";

    team -> result_calculation ( team ->get_quiz_time(time_start), team -> get_points_num(),
                                 team -> get_best_time(), team -> get_max_points());

    delete team;
    return 0;
}