#include "Q_API.h"
#include <iostream>
#include <set>

Ticket::Ticket(const Ticket& ticket) {
    question = ticket.question;
    answers = ticket.answers;
}

void Ticket::add_question(const std::string question) {
    this->question = question;
    return;
}

void Ticket::add_answer(const std::string answer, const bool is_correct) {
    Answer struct_answer;
    struct_answer.is_correct = is_correct;
    struct_answer.answer = answer;
    this->answers.push_back(struct_answer);
    return;
}

int Ticket::run(User &student) {
    std::cout << "\n" << question << "\n";
    int n = 0;
    std::set<int> correct_n;
    for (std::list<Answer>::iterator current_answer = answers.begin(); current_answer != answers.end(); current_answer++) {
        n++;
        if (current_answer->is_correct) {
            correct_n.insert(n);
        }
        std::cout << n << ". " << current_answer->answer << "\n";
    }

    std::cout << "Enter number of correct answer." << "\n\n";
    std::string response;
    std::cin >> response;
    bool result = correct_n.find(std::stoi(response)) != correct_n.end();
    if (result) {
        student.score++;
    }
    return 0;
}

void Quest::add_ticket(const Ticket ticket) {
    this->tickets.push_back(ticket);
}

void Quest::print_hello() {
    std::cout << "\n " << "Start new Quest." << "\n";
    return;
}

void Quest::print_farewell() {
    std::cout << "\n " << "Quest finished." << "\n";
    return;
}

int Quest::run(User &student) {
    print_hello();
    for (std::vector<Ticket>::iterator current_ticket = tickets.begin();
         current_ticket != tickets.end();
         current_ticket++) {
        current_ticket->run(student);
    }
    print_farewell();
    return 0;
}

void User::print_stat() {
    std::cout << "\n " << "You've answered correctly " << score << "/5 times"<<"\n";
    return;
}
