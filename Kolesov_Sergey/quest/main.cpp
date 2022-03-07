#include <iostream>
#include <cstring>

class quest{
public:
    int result = 0;
    char question[255];
    char real_answer;
    char answer;
    char answers[4][255];
    void ask_question(){
        std::cout << question << std::endl;
        for (int i = 0; i < 4; i++) {
            std::cout << (char) ((int) 'A' + i) << " : " << answers[i] << std::endl;
        }
        std::cin >> answer;
        if (answer == real_answer){
            std::cout << "Excelent" << std::endl;
            result = 1;
        }
        else{
            std::cout << "Wrong" << std::endl;
            std::cout << "The true answer is "<< real_answer << std::endl;
        }
        std::cout << " " << std::endl;
    };
};

int main() {
    quest test[5];

    strcpy(test[0].question,   "How many sides does an isosceles triangle have?");
    strcpy(test[0].answers[0], "1");
    strcpy(test[0].answers[1], "2");
    strcpy(test[0].answers[2], "3");
    strcpy(test[0].answers[3], "4");
    test[0].real_answer =      'C';

    strcpy(test[1].question,   "Which of the suggested is edible?");
    strcpy(test[1].answers[0], "Brick wall");
    strcpy(test[1].answers[1], "Pineapple");
    strcpy(test[1].answers[2], "Wheels");
    strcpy(test[1].answers[3], "Kettle");
    test[1].real_answer =      'B';

    strcpy(test[2].question,   "At what temperature does the paper burn?");
    strcpy(test[2].answers[0], "451 F");
    strcpy(test[2].answers[1], "999 F");
    strcpy(test[2].answers[2], "451 C");
    strcpy(test[2].answers[3], "100 C");
    test[2].real_answer =      'C';

    strcpy(test[3].question,   "What do people often wear in winter?");
    strcpy(test[3].answers[0], "underpants");
    strcpy(test[3].answers[1], "singlet");
    strcpy(test[3].answers[2], "panama");
    strcpy(test[3].answers[3], "shorts");
    test[3].real_answer =      'A';

    strcpy(test[4].question,   "What is customary to drink at 5 o'clock?");
    strcpy(test[4].answers[0], "coffee");
    strcpy(test[4].answers[1], "tequila");
    strcpy(test[4].answers[2], "mineral water");
    strcpy(test[4].answers[3], "earl gray with milk");
    test[4].real_answer =      'D';

    std::cout << "Please answer with one character from A to D" << std::endl;
    std::cout << "switch the keyboard layout to English" << std::endl;
    std::cout << " " << std::endl;

    for (int i = 0; i < 5; i++){
        test[i].ask_question();
    }
    int score = 0;
    for (int i = 0; i < 5; i++){
        score += test[i].result;
    }
    std::cout << "Your final score is " << score << std::endl;
    return 0;
}
