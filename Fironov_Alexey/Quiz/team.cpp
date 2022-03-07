#include "team.h"
#include <chrono>
#include <string>
#include <iostream>
#include "fstream"

Team::Team (std::string name, std::string captain)
{
    Team::set_team(name);
    Team::set_captain(captain);
}

Team::~Team()
{}
//==================================================================================
//-------------------------------Team_info------------------------------------------
void Team::set_team(std::string name)
{
    Team::name = name;
}

std::string Team::get_team()
{
    return Team::name;
}
//-------------------------------Captain_info---------------------------------------

void Team::set_captain (std::string captain_name)
{
    Team::captain = captain_name;
}

std::string Team::get_captain ()
{
    return Team::captain;
}
//-------------------------------Points_actions-------------------------------------
void Team::update_points_num (unsigned int current_points)
{
    Team::points_num = current_points;
}

unsigned int Team::get_points_num ()
{
    return Team::points_num;
}

//-----------------------------------Time-----------------------------------------
time_t Team::start_time (){
    auto now = std::chrono::system_clock::now();
    time_t start = std::chrono::system_clock::to_time_t(now);

    return start;
}

time_t Team::get_quiz_time(time_t start_duration)
{
    auto end = std::chrono::system_clock::now();
    time_t quiz_time = std::chrono::system_clock::to_time_t(end) - start_duration;

    return Team::quiz_time;
}

//---------------------------------Place--------------------------------------
unsigned int Team::get_max_points()
{
    //read out of file
    unsigned int max_points = 0;
    return max_points;
}

time_t Team::get_best_time()
{
    //read out of file
    time_t best_time = sizeof (time_t) - 1;
    return best_time;
}

//-----------------------------------------------------------------------------
void Team::result_calculation (time_t full_time, unsigned int points_num,
                        time_t fastest_time, unsigned int highest_score)
{
    if (points_num > 0){
        std::cout << "YOU WON! YOU DID IT!\n";
        std::cout << "Congratulations! You finished with time of " << full_time << " seconds!\n";
        std::cout << "You answered correct for " << points_num << " questions!\n";
        highest_score = points_num;
        //write into the file
    } else if (full_time < fastest_time) {
        std::cout << "May be you're not the correct one but YOU ARE THE FASTEST!\n";
        std::cout << "Congratulations! You finished with time " << full_time << "seconds!\n";
        std::cout << "You answered correct for " << points_num << " questions!\n";
        fastest_time = full_time;
        //write into the file
    } else {
        std::cout << "Sorry but You lose\n";
    }
}
