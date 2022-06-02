#include <iostream>
#include <ctime>
#include <fstream>
#include "aho_corasick.h"
#include "aho_corasick.cpp"

using namespace std;

int main() {
    Prefix_tree dict;
    string str = "aabccbbbabcdaddcd";

    dict.add_str_to_tree("abc");
    dict.add_str_to_tree("bbb");
    dict.add_str_to_tree("add");
    dict.add_str_to_tree("cd");
    dict.add_str_to_tree("c");
    dict.add_str_to_tree("abcd");

    dict.find_all_pos(str);
    return 0;
}


/*

    //ifstream input("text_100k.txt");
    ifstream input("text_100k_~alf.txt");
    string str_input;
    getline(input, str_input);
    input.close();


    clock_t t1 = clock();
    Prefix_tree dictionary;

    // k = 10
    string str_dict;
    ifstream dict("dictionary.txt");

    while(getline(dict, str_dict )) {
        if ((str_dict[str_dict.size() - 1]) == '\r') {
            str_dict = str_dict.substr(0, str_dict.size()-1);
        }
        dictionary.add_str_to_tree(str_dict);
    }
    dict.close();

    dictionary.find_all_pos(str_input);

    // time evaluation
    clock_t t2 = clock();
    double time = (double)(t2 - t1) / CLOCKS_PER_SEC;
    cout << "Time: " << time << " s" << endl;
    time = time * 1000.0;
    cout << "Time: " << time << " ms" << endl;

 */