#pragma once
#include <iostream>
#include <stack>
#include <string>
#include <stdlib.h>

//this class converts an expression to RPN
class Interpretation
{
public:
    char actual_symbol;          //the current symbol
    std::string str_input;       //input string
    std::string str_output;      //output string
    int inp_index;               //the index of the input string

    char get_next_char(std::string);         //get the next symbol from input string
    static bool isDigit(char symb);        //checking numbers
    static int prior(char symb);           //get the priority of the symbol

public:
    void convert(std::string);           //convert to PPN
    void calculate(std::string);
    std::string get_str_output()const;   //get the output string
};

