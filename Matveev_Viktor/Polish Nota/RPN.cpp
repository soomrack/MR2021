#include "RPN.h"

bool Interpretation::isDigit(char symb)
{
    return (symb >= '0' && symb <= '9');
}

int Interpretation::prior(char symb)
{
    switch (symb)
    {
        case '(':
            return 1;
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
            return 3;
        case 'z':
            return -1;
        default:
            return 0;
    }
}

char Interpretation::get_next_char(std::string scrl_str)
{
    if(inp_index < scrl_str.size())
    {
        return (actual_symbol = scrl_str[inp_index++]);
    }
    else
    {
        return (actual_symbol = '\0');
    }
}

std::string Interpretation::get_str_output() const
{
    return str_output;
}

void Interpretation::convert(std::string orig_str)
{
    int prev_oper = 0;
    int new_bracket = 0;
    inp_index = 0;

    std::stack <char> stack4operators;
    str_input = orig_str;
    str_output.clear();

    if((!isDigit(str_input[0])) && str_input[0] != '(')
    {
        throw std::runtime_error ("Syntax error! Something wrong with the first symbol");
    }

    while(get_next_char(str_input) != '\0')
    {
        if(isDigit(actual_symbol))
        {
            str_output += actual_symbol;
            prev_oper = 0;
            continue;
        }


        switch (actual_symbol)
        {
            case '(':
                stack4operators.push(actual_symbol);
                new_bracket++;
                prev_oper = 0;
                break;
            case '*': case '/': case '+': case '-':
                if(inp_index == str_input.size())
                {
                    throw std::runtime_error ("Syntax error! Your last symbol - operator?!");
                }

                if(stack4operators.empty())
                {
                    prev_oper = 1;
                    stack4operators.push(actual_symbol);
                    break;
                }

                else if((!prev_oper) && (!stack4operators.empty()))
                {
                    prev_oper = 1;
                    while(prior(actual_symbol) <= prior(stack4operators.top()))
                    {
                        str_output += stack4operators.top();
                        stack4operators.pop();
                        if (stack4operators.empty())
                        {
                            stack4operators.push(actual_symbol);
                            break;
                        }
                    }

                    if(prior(actual_symbol) > prior(stack4operators.top()))
                    {
                        stack4operators.push(actual_symbol);
                    }
                    break;
                }

                else
                {
                    throw std::runtime_error ("Syntax error! You got 2 operators going sequence.");
                }

            case ')':
                if(prev_oper)
                {
                    throw std::runtime_error ("Syntax error! You got ')' after operator!");
                }
                else
                    while((actual_symbol = stack4operators.top())!= '(' && new_bracket>0)
                    {
                        str_output += actual_symbol;
                        stack4operators.pop();
                    }
                new_bracket--;
                break;
            default:
                throw std::runtime_error ("Error! Invalid symbol in the string.");
        }
    }

    while(!stack4operators.empty())
    {
        if(stack4operators.top() == '(')
        {
            stack4operators.pop();
            continue;
        }
        str_output += stack4operators.top();
        stack4operators.pop();
    }

    if(new_bracket)
    {
        throw std::runtime_error ("Error. Wrong number of brackets.");
    }

    std::cout << str_output << "\n";


    std::stack <int> stack4calculation;
    int f_num = 0;
    int s_num = 0;
    int temp = 0;
    inp_index = 0;

    while(get_next_char(str_output) != '\0')
    {
        if(isDigit(actual_symbol))
        {
            temp = actual_symbol - '0';
            stack4calculation.push(temp);
            continue;
        }
        else if(!isDigit(actual_symbol))
        {
            switch (actual_symbol)
            {
                case '+':
                    f_num = stack4calculation.top();
                    stack4calculation.pop();
                    s_num = stack4calculation.top();
                    stack4calculation.pop();
                    temp = f_num + s_num;
                    stack4calculation.push(temp);
                    break;
                case '-':
                    s_num = stack4calculation.top();
                    stack4calculation.pop();
                    f_num = stack4calculation.top();
                    stack4calculation.pop();
                    temp = f_num - s_num;
                    stack4calculation.push(temp);
                    break;
                case '*':
                    f_num = stack4calculation.top();
                    stack4calculation.pop();
                    s_num = stack4calculation.top();
                    stack4calculation.pop();
                    temp = f_num * s_num;
                    stack4calculation.push(temp);
                    break;
                case '/':
                    s_num = stack4calculation.top();
                    stack4calculation.pop();
                    f_num = stack4calculation.top();
                    stack4calculation.pop();
                    temp = f_num / s_num;
                    stack4calculation.push(temp);
                    break;
            }
        }
    }
    int answer = 0;
    answer = stack4calculation.top();
    stack4operators.pop();
    std::cout << answer << "\n";
}

int main()
{
    Interpretation Test;
    Test.convert("4/2*6-4");
    return 0;
}
