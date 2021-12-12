#include <iostream>
#include "text.h"

using namespace std;

class Test{
public:
    unsigned int score;
    void show_text(int num);
    void show_res();

private:
    void get_res(){
        score = score % 3;
    };

    void read_res(){
        int a;
        cin >> a;
        if(a < 3)  score += a;
        else{
            cout << "Твой ответ 2" << endl;
        }
    };
};

void Test::show_text(int num) {
    cout << qe[num] << endl;
    for(int i = 1; i < 3; ++i){
        cout << i << " : " <<answ[num][i] << endl;
    }
    read_res();
}

void  Test::show_res() {
    get_res();
    cout << res[score] << endl;
}


int main() {
    unsigned int count = 0;
    system("chcp 65001");
    Test Quiz;

    while(number_of_questions - count > 1){
        Quiz.show_text(count);
        count++;
    }

    Quiz.show_res();
    std::cout << "end!" << std::endl;
    return 0;
}
