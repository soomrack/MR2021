#pragma once
#ifndef QUIZ_TEAM_H
#define QUIZ_TEAM_H
#include "string"



class Team {
    public:

//========================Destructor===========================
        ~Team();

//=====================Constructor=============================
        Team(std::string, std::string);

//----------------------Procedures-----------------------------
        void set_team (std::string);

        std::string get_team();

        void set_captain (std::string);

        std::string get_captain();

        void update_points_num (unsigned int);
        unsigned int get_points_num ();

        time_t start_time();
        time_t get_quiz_time (time_t start);

        unsigned int get_max_points ();
        time_t get_best_time ();

        void result_calculation (time_t full_time, unsigned int points_num,
                                 time_t best_time, unsigned int max_points);

//-------------------------Variables------------------------------------
   protected:
        std::string name;          // Team name
        std::string captain;       // Captain Name
        //std::string team_deputy_one;  First Deputy Name
        //std::string team_deputy_two;  Second Deputy Name
        unsigned int points_num;   // Number of correct answers
        double quiz_time;          // Time of answering
};

#endif //QUIZ_TEAM_H
