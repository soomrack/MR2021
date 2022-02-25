#include <iostream>
#include "aho_corasick.h"
#include "aho_corasick.cpp"

using namespace std;

int main() {
    bohr_ini();   

    add_str_to_bohr("abc");
    add_str_to_bohr("bbb");
    add_str_to_bohr("add");
    add_str_to_bohr("cd");
    add_str_to_bohr("c");
    add_str_to_bohr("abcd");
    find_all_pos("aabccbbbabcdaddcd");
}
