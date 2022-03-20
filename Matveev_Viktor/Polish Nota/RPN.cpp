#include "RPN.h"

Interpretation::Interpretation()  = default;

Interpretation::Interpretation(const Interpretation & other)
{
	expression = other.expression;
	prepared = other.prepared;
	rp_string = other.rp_string;

	input_id = other.input_id;
	actual_symbol = other.actual_symbol;
	prev_symbol = other.prev_symbol;

}

Interpretation::Interpretation(Interpretation && other) noexcept
{
	expression = other.expression;
	prepared = other.prepared;
	rp_string = other.rp_string;
	input_id = other.input_id;
	actual_symbol = other.actual_symbol;
	prev_symbol = other.prev_symbol;

	other.input_id = 0;
	other.actual_symbol = '\0';
	other.prev_symbol = '\0';
	other.expression = "\0";
	other.prepared = "\0";
	other.rp_string = "\0";
}

Interpretation::~Interpretation() = default;

bool Interpretation::is_digit(char symb)
{
    return (symb >= '0' && symb <= '9');
}

int Interpretation::get_prior(char symb)
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
        case '^':
            return 4;
        default:
            return 0;
    }
}

char Interpretation::get_next_char(std::string go_throw_str)
{
    if(input_id < go_throw_str.size())
    {
        return (actual_symbol = go_throw_str[input_id++]);
    }
    else
    {
        return (actual_symbol = '\0');
    }
}

char Interpretation::get_prev_char(std::string go_throw_str)
{
	return (prev_symbol = go_throw_str[input_id]);
}

std::string Interpretation::prepare(std::string expression)
{
	int prev_oper = 0;
	int bracket_num = 0;
	input_id = 0;
	while(get_next_char(expression) != '\0')
	{
		if(is_digit(actual_symbol))
		{
			prepared += actual_symbol;
			prev_oper = 0;
			if (get_prev_char(prepared) == '-')
			{
				prepared += ')';
				bracket_num--;
			}
			continue;
		}
		switch (actual_symbol)
		{
			case '+': case '*': case '/': case '^':
				prepared += actual_symbol;
				prev_oper = 1;
				continue;
			case '-':
				if (prev_oper == 0)
				{
					prepared += actual_symbol;
					prev_oper = 1;
					continue;
				}
				prepared += '(';
				bracket_num++;
				prepared += '0';
				prepared += actual_symbol;
				prev_oper = 1;
				continue;
			case '(':
				prepared += actual_symbol;
				bracket_num++;
				continue;
			case ')':
				while (bracket_num > 0)
				{
					prepared += actual_symbol;
					bracket_num--;
				}
				continue;

		}

	}

	return prepared;
}

std::string Interpretation::convert(std::string middle_str)
{
    int prev_oper = 0;
    int new_bracket = 0;
    input_id = 0;

    std::stack <char> stack4convert;
	std::stack <char> stack4operators;
    rp_string.clear();

    if((!is_digit(middle_str[0])) && middle_str[0] != '(')
    {
	    rp_string = "";
		return ("Syntax error! Something wrong with the first symbol");
    }

    while(get_next_char(middle_str) != '\0')
    {
        if(is_digit(actual_symbol))
        {
            rp_string += actual_symbol;
            prev_oper = 0;
            continue;
        }

        switch (actual_symbol)
        {
            case '(':
                stack4convert.push(actual_symbol);
                new_bracket++;
                prev_oper = 0;
                break;

			case '*': case '/': case '+': case '-': case '^':
                if(input_id == middle_str.size())
                {
	                return ("Syntax error! Your last symbol - operator?!");
                }
                if(stack4convert.empty())
                {
                    prev_oper = 1;
                    stack4convert.push(actual_symbol);
                    break;
                }
				if((!prev_oper) && (!stack4convert.empty()))
                {
                    prev_oper = 1;
                    while(get_prior(actual_symbol) <= get_prior(stack4convert.top()))
                    {
                        rp_string += stack4convert.top();
                        stack4convert.pop();
                        if (stack4convert.empty())
                        {
                            stack4convert.push(actual_symbol);
                            break;
                        }
                    }

                    if(get_prior(actual_symbol) > get_prior(stack4convert.top()))
                    {
                        stack4convert.push(actual_symbol);
                    }
                    break;
                }
		        return ("Syntax error! You got 2 operators going sequence.");
            case ')':
                if(prev_oper)
                {
	                return ("Syntax error! You got ')' after operator!");
                }
		        while((actual_symbol = stack4convert.top())!= '(' && new_bracket>0)
		        {
			        rp_string += actual_symbol;
			        stack4convert.pop();
		        }
		        new_bracket--;
				stack4convert.pop();
                break;
            default:
	            return ("Error! Invalid symbol in the string.");
        }
    }

	char final_pop;
    /*while(!stack4convert.empty())
    {
	    final_pop = stack4convert.top();
	    stack4convert.pop();
	    if(final_pop == '(')
	    {
		    continue;
	    }
		stack4operators.push(final_pop);
    }*/
	while (!stack4convert.empty())
	{
		final_pop = stack4convert.top();
		stack4convert.pop();
		if(final_pop == '(')
		{
			continue;
		}
		if(stack4convert.empty())
		{
			rp_string += final_pop;
			continue;
		}
		if (get_prior(final_pop) >= get_prior(stack4convert.top()))
		{
			rp_string += final_pop;
			continue;
		}
		if (get_prior(final_pop) < stack4convert.top())
		{
			rp_string += stack4convert.top();
			stack4convert.pop();
			stack4convert.push(final_pop);
		}
	}

    if(new_bracket)
    {
	    return ("Error. Wrong number of brackets.");
    }
	return rp_string;
}

float Interpretation::calculate(std::string rp_string)
{
	if((!is_digit(rp_string[0])) && rp_string[0] != '(')
	{
		rp_string = "";
		std::cout << "Calculation terminated! Something wrong with the first symbol";
		return 0.0;
	}
	std::stack <float> stack4calculation;
	float f_num = 0.0;
	float s_num = 0.0;
	float temp = 0.0;
	input_id = 0.0;

	while(get_next_char(rp_string) != '\0')
	{
		if(is_digit(actual_symbol))
		{
			temp = float(actual_symbol - '0');
			stack4calculation.push(temp);
			continue;
		}
		else if(!is_digit(actual_symbol))
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
					if (s_num == 0)
					{
						rp_string = "";
						std::cout << "Calculation terminated! You've tried to divide by 0";
						return 0.0;
					}
					temp = f_num / s_num;
					stack4calculation.push(temp);
					break;
				case '^':
					s_num = stack4calculation.top();
					stack4calculation.pop();
					f_num = stack4calculation.top();
					stack4calculation.pop();
					temp = pow(f_num, s_num);
					stack4calculation.push(temp);
			}
		}
	}
	float answer = 0.0;
	answer = stack4calculation.top();
	stack4calculation.pop();
	return answer;
}


int main()
{
	std::string test_prep;
	std::string test_str;
	float test_answ;

	clock_t t1 = clock();

	for(int i = 0; i <= 12500; i++)
	{
		Interpretation Test;
		test_prep = Test.prepare("1/(7-(1+1))*3-(2+(1+1))*1/(7-(2+1))*3-(2+(1+1))*(1/(7-(1+1)))^-3-((2+(1+1)))+1/(7-((1+1)))*3-((2+(1+1)))");
		//std::string test_prep = Test.prepare("(8+2*5)/(1+3*2-4)");
		//std::cout << "Prepared string > "<< test_prep << "\n";
		test_str = Test.convert(test_prep);
		//std::cout << "String in RPN > " << test_str << "\n";
		test_answ = Test.calculate(test_str);
	}

	clock_t t2 = clock();
	double runtime = (double)(t2 - t1) / CLOCKS_PER_SEC;
	std::cout << "Prepared string > "<< test_prep << "\n";
	std::cout << "String in RPN > " << test_str << "\n";
	std::cout << "Your answer > "<< test_answ << "\n";
	std::cout << "Runtime > " << runtime << "\n";
	return 0;
}