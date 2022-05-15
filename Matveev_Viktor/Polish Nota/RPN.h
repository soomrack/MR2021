#pragma once
#include <iostream>
#include <stack>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <cmath>
#include <ctime>

//this class converts an expression to RPN
class Interpretation
{
public:
    std::string expression; //incoming equation
	std::string prepared; //equation after some magic
	std::string ready4convertion; //and another magic
    std::string rp_string; //equation in RPN

public:
	//Magic - the first pass along the string to get rid of the unary minus
	//You can start right from "convert", if your string dont have unary minus
	std::string prepare(std::string);
	//use this method if your string has some places with more than one "^"
	//You can start right from "convert", if your string dont have many "^"
	std::string multiple_degrees(std::string);
	//normal2PPN - conversion from usual math to polish math.
	//Just as was said you can start from this, if your string dont have unary minus
    std::string convert(std::string);
	//Just calculation. But only for polish math))) Dont try to calculate usual math here
    float calculate(std::string);

public:
	Interpretation();
	Interpretation(const Interpretation& other);
	Interpretation(Interpretation&& other) noexcept;
	~Interpretation();

private:
	int input_id;//the index of the input string
	char actual_symbol;
	char prev_symbol;
	char next_symbol;

private:
	static bool is_digit(char symb);//checking for numbers
	static int get_prior(char symb);
	char get_next_char(std::string);
	char get_prev_char(std::string);
	char reflect_next_smb(std::string);
};