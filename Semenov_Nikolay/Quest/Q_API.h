#ifndef Q_API_Q_API_H
#define Q_API_Q_API_H

#include <string>
#include <list>
#include <vector>

class User {
public:
    User() {score = 0;};
    ~User() {};
public:
    void print_stat();
    int score;
};

struct Answer {
    bool is_correct;
    std::string answer;
};

class Ticket {
public:
    Ticket() { question = "None"; };
    Ticket(const Ticket& ticket);
    ~Ticket() {};
public:
    void add_question(const std::string question);
    void add_answer(const std::string answer, const bool is_correct);
    int run(User &student);
private:
    std::string question;
    std::list<Answer> answers;
};

class Quest {
private:
    std::vector<Ticket> tickets;
    virtual void print_hello();
    virtual void print_farewell();
public: Quest() {};
    ~Quest() {};
public:
    int run(User &student);
    void add_ticket(const Ticket ticket);
};

#endif