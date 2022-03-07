#include <vector>
#include <cstring>

using namespace std;

#ifndef ALGORITHM_AHO_CORASICK_H
#define ALGORITHM_AHO_CORASICK_H

const int k = 26;  //alphabet size

struct bohr_vertex {
    int next_vertex[k];  //vertex number
    int pat_num;  //sample line number
    bool flag;  //the bit indicating whether our vertex is the original string

    int suff_link;  //suffix link
    int g_suff_link;  //"good" suffix link

    int auto_move[k];  //auto_move - memorizing the transition of the automaton
    int par;  //par - the vertex-parent in the tree
    char symb;  //the symbol on the rim from par to this vertex
};

bohr_vertex make_bohr_vertex(int p, char c);
void bohr_ini();
void add_str_to_bohr(const string &s);
int get_auto_move(int v, char ch);
int get_suff_link(int v);
int get_suff_link_good(int v);
void check(int v, int i);
void find_all_pos(const string &s);

#endif //ALGORITHM_AHO_CORASICK_H
