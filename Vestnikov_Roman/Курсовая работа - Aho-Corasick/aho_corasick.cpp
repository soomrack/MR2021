#include "aho_corasick.h"

Prefix_tree::Prefix_tree() {
    vertex.push_back(make_tree_vertex(0, '$'));
}

pr_tree_vertex Prefix_tree::make_tree_vertex(int p, char c) {
    pr_tree_vertex v;  //create tree
    memset(v.next_vertex, 255, sizeof(v.next_vertex));  //255 = -1
    memset(v.auto_move, 255, sizeof(v.auto_move));
    v.leaf = false;
    v.suff_link = -1;  //initially, there is no suf. link
    v.suff_link_comp = -1;
    v.par = p;
    v.symb = c;
    return v;
}

void Prefix_tree::add_str_to_tree(const string &str) {
    int num = 0;  //starting from the root
    for (int i = 0; i < str.length(); i++) {
        char ch = str[i] - 'a';  //get the number in the alphabet
        if (vertex[num].next_vertex[ch] == -1) {  //-1 - признак отсутствия ребра
            vertex.push_back(make_tree_vertex(num, ch));
            vertex[num].next_vertex[ch] = vertex.size() - 1;
        }
        num = vertex[num].next_vertex[ch];
    }
    vertex[num].leaf = true;
    pattern.push_back(str);
    vertex[num].pat_num = pattern.size() - 1;
}

bool Prefix_tree::is_string_in_tree(const string &s) {
    int num = 0;
    for (int i = 0; i < s.length(); i++) {
        char ch = s[i] - 'a';
        if (vertex[num].next_vertex[ch] == -1) {
            return false;
        }
        num = vertex[num].next_vertex[ch];
    }
    return true;
}

int Prefix_tree::get_suff_link(int v) {
    if (vertex[v].suff_link == -1)
        if (v == 0 || vertex[v].par == 0)  //if 'v' is the root or the parent of 'v' is the root
            vertex[v].suff_link = 0;
        else
            vertex[v].suff_link = get_auto_move(get_suff_link(vertex[v].par), vertex[v].symb);
    return vertex[v].suff_link;
}

int Prefix_tree::get_auto_move(int v, char ch) {
    if (vertex[v].auto_move[ch] == -1)
        if (vertex[v].next_vertex[ch] != -1)
            vertex[v].auto_move[ch] = vertex[v].next_vertex[ch];
        else if (v == 0)
            vertex[v].auto_move[ch] = 0;
        else
            vertex[v].auto_move[ch] = get_auto_move(get_suff_link(v), ch);
    return vertex[v].auto_move[ch];
}

int Prefix_tree::get_suff_link_comp(int v) {
    if (vertex[v].suff_link_comp == -1) {
        int u = get_suff_link(v);
        if (u == 0)  //либо "v" - это корень, либо суф. ссылка "v" указывает на корень
            vertex[v].suff_link_comp = 0;
        else if (vertex[u].leaf) {
            vertex[v].suff_link_comp = u;
        } else vertex[v].suff_link_comp = get_suff_link_comp(u);
    }
    return vertex[v].suff_link_comp;
}

void Prefix_tree::check(int v, int i) {
    for (int u = v; u != 0; u = get_suff_link_comp(u)) {
        if (vertex[u].leaf) {
            cout << i - pattern[vertex[u].pat_num].length() + 1 << " " << pattern[vertex[u].pat_num] << endl;
        }
    }
}

void Prefix_tree::find_all_pos(const string &s) {
    int u = 0;
    for (int i = 0; i < s.length(); i++) {
        u = get_auto_move(u, s[i] - 'a');
        check(u, i + 1);
    }
}
