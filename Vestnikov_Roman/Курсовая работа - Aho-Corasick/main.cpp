#include <iostream>
#include <ctime>
#include <fstream>
#include "aho_corasick.h"
#include "aho_corasick.cpp"

using namespace std;

int main() {

    ifstream text("text.txt");
    string str;
    getline(text, str);

    clock_t t1 = clock();

    Prefix_tree dictionary;

    // k = 10
    // prefix tree creation
    dictionary.add_str_to_tree("gcdbjgfbccaadijdaihhffbhedaagafajedcfcjihgghaajbfg");
    dictionary.add_str_to_tree("ihbdejhghffcagchhgffjheiajgfdfccaifaaggbahdgcijhcb");
    dictionary.add_str_to_tree("agibiibfgdcbdecfdeddihdaiehafefibdgfdbhdcddbihibgg");
    dictionary.add_str_to_tree("fhgcgfihfjajbjafceiijddhffjcabjedediggedbjijfbidig");

    dictionary.add_str_to_tree("hchcgfbjbbddhij");
    dictionary.add_str_to_tree("cidijeejhcgfaae");
    dictionary.add_str_to_tree("icjhdciahhahdjg");
    dictionary.add_str_to_tree("cfigfcfcdjaegfb");

    dictionary.add_str_to_tree("abjibibejd");
    dictionary.add_str_to_tree("ijdgcdhbbi");
    dictionary.add_str_to_tree("chgjgddggg");
    dictionary.add_str_to_tree("aaicjefafi");

    dictionary.add_str_to_tree("aceaf");
    dictionary.add_str_to_tree("cbdbg");
    dictionary.add_str_to_tree("bachb");
    dictionary.add_str_to_tree("acgcj");

    dictionary.add_str_to_tree("ciia");
    dictionary.add_str_to_tree("bbgd");
    dictionary.add_str_to_tree("cbjb");
    dictionary.add_str_to_tree("ciig");

    dictionary.add_str_to_tree("aef");
    dictionary.add_str_to_tree("efc");
    dictionary.add_str_to_tree("ebg");
    dictionary.add_str_to_tree("cef");

    /*add_str_to_bohr("ac");
    dictionary.add_str_to_tree("be");
    dictionary.add_str_to_tree("dg");
    dictionary.add_str_to_tree("ff");*/

    /*dictionary.add_str_to_tree("c");
    dictionary.add_str_to_tree("e");
    dictionary.add_str_to_tree("h");
    dictionary.add_str_to_tree("i");*/

    dictionary.find_all_pos(str);

    clock_t t2 = clock();

    // time evaluation
    double time = (double)(t2 - t1) / CLOCKS_PER_SEC;
    cout << "Time: " << time << endl;

    return 0;
}
