#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <cstdarg>


class Question{
public:
    virtual void print_question() = 0;
    virtual bool check_answer(std::string &answer) = 0;
};

class ChoiceQuestion: public Question{
public:
    ChoiceQuestion(std::string &question_text, std::vector<std::string> &variants, int right_num);
    ChoiceQuestion(const char* question_text, int right_num, int num_of_variants, ...);

    void print_question() override;
    bool check_answer(std::string &answer) override;
private:
    std::string question_text;
    std::vector<std::string> variants;
    int right_num;
    std::vector<int> variant_numbers;
};


class TextQuestion: public Question{
public:
    TextQuestion(std::string &question_text, std::string &right_answer);
    TextQuestion(const char* question_text, const char* right_answer);

    void print_question() override;
    bool check_answer(std::string &answer) override;
private:
    std::string question_text;
    std::string right_answer;
};

class Test{
public:
    Test();
    void add_choice_question(const char* question_text, int right_num, int num_of_variants, ...);
    void add_text_question(const char* question_text, const char* right_answer);
    std::list<Question*> question_ptr_list;
};

class User{
public:
    User();
    void complete_test(Test test);
private:
    int amount_of_right_answers;
};



ChoiceQuestion::ChoiceQuestion(std::string &question_text, std::vector<std::string> &variants, int right_num){
    ChoiceQuestion::variants = variants;
    ChoiceQuestion::right_num = right_num;
    ChoiceQuestion::question_text = question_text;

    ChoiceQuestion::variant_numbers.resize(variants.size());
    for(int i = 0; i < variant_numbers.size(); i++){
        variant_numbers[i] = i + 1;
    }
}

ChoiceQuestion::ChoiceQuestion(const char* question_text, int right_num, int num_of_variants, ...){
    ChoiceQuestion::right_num = right_num;
    ChoiceQuestion::question_text = question_text;
    ChoiceQuestion::variants.resize(num_of_variants);

    va_list argptr;
    va_start (argptr, num_of_variants);
    for (int i = 0; i < num_of_variants; i++){
        variants[i] = va_arg(argptr,const char*);
    }
    va_end(argptr);

    ChoiceQuestion::variant_numbers.resize(variants.size());
    for(int i = 0; i < variant_numbers.size(); i++){
        variant_numbers[i] = i + 1;
    }
}

void ChoiceQuestion::print_question() {
    std::shuffle(variant_numbers.begin(),
            variant_numbers.end(),
            std::mt19937(std::random_device()()));

    std::cout << question_text << std::endl;
    int j;
    for (int i = 0; i < variants.size(); i++){
        j = variant_numbers[i];
        std::cout << i + 1 << ". "<< variants[j - 1] << std::endl;
    }
}

bool ChoiceQuestion::check_answer(std::string &answer){
    int chosen_num = std::stoi(answer);
    if ( right_num == variant_numbers[chosen_num - 1]){
        return true;
    }
    return false;
}


TextQuestion::TextQuestion(std::string &question_text, std::string &right_answer){
    TextQuestion::question_text = question_text;
    TextQuestion::right_answer = right_answer;
}

TextQuestion::TextQuestion(const char* question_text, const char* right_answer){
    TextQuestion::question_text = question_text;
    TextQuestion::right_answer = right_answer;
}

void TextQuestion::print_question(){
    std::cout << question_text << std::endl;
}
bool TextQuestion::check_answer(std::string &answer){
    if ( answer == right_answer){
        return true;
    }
    return false;
}


Test::Test(){
    ;
}

void Test::add_choice_question(const char* question_text, int right_num, int num_of_variants, ...){
    std::string question_text_string = question_text;
    std::vector<std::string> variants;
    variants.resize(num_of_variants);

    va_list argptr;
    va_start (argptr, num_of_variants);
    for (int i = 0; i < num_of_variants; i++){
        variants[i] = va_arg(argptr,const char*);
    }
    va_end(argptr);

    ChoiceQuestion* choice_question_ptr = new ChoiceQuestion(question_text_string, variants, right_num);
    question_ptr_list.push_back(choice_question_ptr);
}

void Test::add_text_question(const char* question_text, const char* right_answer){
    TextQuestion* text_question_ptr = new TextQuestion(question_text, right_answer);
    question_ptr_list.push_back(text_question_ptr);
}


User::User(){
    amount_of_right_answers = 0;
}

void User::complete_test(Test test){
    amount_of_right_answers = 0;
    std::string answer;
    bool is_right_answer;

    for(std::list<Question*>::iterator it = test.question_ptr_list.begin();
        it != test.question_ptr_list.end(); it++){

        (*it)->print_question();
        std::cin >> answer;
        is_right_answer = (*it)->check_answer(answer);

        if (is_right_answer){
            amount_of_right_answers++;
        }
    }
    std::cout << "Your result ";
    std::cout << amount_of_right_answers << '/';
    std::cout << test.question_ptr_list.size() << std::endl;
}


int main() {
    Test test;
    test.add_choice_question("The first temporary question. Where a number three is written?",
                             3,4,
                             "One",
                             "Two",
                             "Three",
                             "Four");
    test.add_text_question("The second temporary question. Write the number pi.",
                           "3.14");
    test.add_choice_question("The third temporary question. Which planet is ours?",
                             3,4,
                             "Mercury",
                             "Venus",
                             "Earth",
                             "Mars");
    User user;
    user.complete_test(test);

    return 0;
}
