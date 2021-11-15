#include <iostream>
using namespace std;

int score = 0;

class player {
    public:
        void set_name();
        void check_player();
        string get_name();
        int get_years_with_sm();
    private:
        string player_name;
        int familiar_with_sm;
        const int sm_age = 17;
};

class question {
    private:
        string question_text;
        string answer1;
        string answer2;
        string answer3;
        string answer4;
    public:
        void set_question(string,string,string,string,string);
        void ask_question();
        void add_score();
};

void player :: set_name() {
    string name;
    cout << "Input your name: ";
    cin >> name;
    player_name = name;
}

void player :: check_player() {
    bool next_step = false;
    int years = 0;
    cout << "How many years have you been familiar with Smesharki?" << endl;
    while (next_step == false) {
        cin >> years;
        if (years > sm_age) {
            cout << "Don't try to trick me! Input real value:";
            next_step = false;
        }
        else {
            familiar_with_sm = years;
            next_step = true;
        }
    }
}

string player :: get_name() {
    return player_name;
}

int player :: get_years_with_sm() {
    return familiar_with_sm;
}

void question :: set_question(string q, string a1, string a2, string a3, string a4) {
    question_text = q;
    answer1 = a1;
    answer2 = a2;
    answer3 = a3;
    answer4 = a4;
}

void question :: ask_question() {
    cout << question_text << endl;
    cout << "1)" << answer1 << endl;
    cout << "2)" << answer2 << endl;
    cout << "3)" << answer3 << endl;
    cout << "4)" << answer4 << endl;
    add_score();
}

void question :: add_score() {
    bool next_step = false;
    int choice = 0;
    while (next_step == false) {
        next_step = true;
        cin >> choice;
        switch (choice) {
            case 1:
                score += 1;
                break;
            case 2:
                score += 2;
                break;
            case 3:
                score += 3;
                break;
            case 4:
                score += 4;
                break;
            default:
                cout << "Something went wrong" << endl << "try again!";
                next_step = false;
        }
    }
}

void get_the_answer() {
    if (5 <= score && score <= 8) {
        cout << "You are Barash - Romantic, melancholic, poet";
    }
    if (9 <= score && score <= 12) {
        cout << "You are Krosh - Hyperactivity of destruction and parties";
    }
    if (13 <= score && score <= 16) {
        cout << "You are Kopatich - Honey, garden, muscles";
    }
    if (17 <= score && score <= 20) {
        cout << "You are Niysha - Bodypositive queen of the friendzone";
    }
}

int main() {
    player man;

    man.set_name();
    man.check_player();

    cout << endl << man.get_name() << ", you have been familiar with Smeshariki"
    << " for " << man.get_years_with_sm() << " years" << endl
    << "It's the time to find out who you are from Smeshariki!" << endl
    << endl << "Let's get started!" << endl << endl;

    question q1;
    question q2;
    question q3;
    question q4;
    question q5;

    q1.set_question("Your comrades going on a dangerous and distant journey."
                    "They are calling you to come with them. What will you do?",
                     "I'm a little scared. I'll go, of course, but I need to take"
                     " a book and a first aid kit",
                     "Haha, I thought of all this myself",
                     "I'll take everyone, but who will be left with my garden",
                     "I'll go, but I'm afraid of getting my beautiful new dress dirty");

    q2.set_question("What will you do on your trip?",
                    "Read, think about something, or compose a poem",
                    "Play a portable console",
                    "Tell friends an informative and fascinating story",
                    "Watch Instagram, or something on YouTube");

    q3.set_question("The car you were driving with your friends broke down on the road."
                    "What do we do now?",
                    "It's good that I brought everything to survive in this area",
                    "Yeah, we didn't see that one coming. All right, we'll think of something.",
                    "I'll try to fix it. Everything can be fixed if you're smart",
                    "That's terrible. This is a failure. Oh, my God.");

    q4.set_question("You and your friends are making your way through a dense forest."
                    "One lags behind and gets lost. What to do?",
                    "I'll try to find myself, because I'm the one who's lost",
                    "Is anyone missing? I thought everyone was here",
                    "Immediately organize a rescue operation",
                    "This is a nightmare. I don't like this trip anymore.");

    q5.set_question("You were attacked by the local natives. They are very hostile."
                    "What's the best course of action?",
                    "It's a tricky situation. We'd better think this through.",
                    "I'll try to negotiate with these, what do you call them?",
                    "We need to take these natives, give them the snot",
                    "Let's run. More like hide. Behind that tree.");

    q1.ask_question();
    q2.ask_question();
    q3.ask_question();
    q4.ask_question();
    q5.ask_question();

    get_the_answer();

    return 0;
}
