#include <vector>
#include <cstring>

using namespace std;

#ifndef ALGORITHM_AHO_CORASICK_H
#define ALGORITHM_AHO_CORASICK_H

const int k = 26;  // alphabet size

struct pr_tree_vertex {
    int next_vertex[k];  // vertex number
    int pat_num;  // sample line number
    bool flag;  // the bit indicating whether our vertex is the original string

    int suff_link;  // suffix link
    int suff_link_comp;  // "compressed" suffix link

    int auto_move[k];  // memorizing the transition of the automaton
    int par;  // the vertex-parent in the tree
    char symb;  // the symbol on the rim from par to this vertex
};

class Prefix_tree{
public:
    Prefix_tree();
    ~Prefix_tree() = default;
public:
    void check(int v, int i);
    void find_all_pos(const string &s);
    void add_str_to_tree(const string &s);
private:
    vector<pr_tree_vertex> tree;
    vector<string> pattern;
private:
    pr_tree_vertex make_bohr_vertex(int p, char c);
    int get_suff_link_comp(int v);
    int get_auto_move(int v, char ch);
    int get_suff_link(int v);
    bool is_string_in_tree(const string &s);
};

#endif //ALGORITHM_AHO_CORASICK_H
