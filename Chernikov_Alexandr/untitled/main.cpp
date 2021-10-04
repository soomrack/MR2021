#include <iostream>
#include <string>

std::string template_zero = "zero", template_one = "one";

int str2number(std::string str){
    int result = 0;
    int i = 0;
    while (i < str.length()){
        bool template_is_correct = true;
        for (int j = 0; j < template_zero.length(); j++){
            if (str[i + j] != template_zero[j]) {
                template_is_correct = false;
                break;
            }
        }
        if (template_is_correct){
            result = 2*result + 0;
            i += template_zero.length();
            continue;
        }

        template_is_correct = true;
        for (int j = 0; j < template_one.length(); j++){
            if (str[i + j] != template_one[j]) {
                template_is_correct = false;
                break;
            }
        }
        if (template_is_correct){
            result = 2*result + 1;
            i += template_one.length();
            continue;
        }
    }
    return result;
}

int main() {
    std::string str1, str2;
    std::cin >> str1;
    std::cin >> str2;

    int number1 = str2number(str1);
    int number2 = str2number(str2);

    if (number1 > number2)
        std::cout << '>';
    if (number1 < number2)
        std::cout << '<';
    if (number1 == number2)
        std::cout << '=';
    return 0;
}
