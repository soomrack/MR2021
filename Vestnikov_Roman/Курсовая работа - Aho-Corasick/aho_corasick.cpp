#include "aho_corasick.h"

Prefix_tree::Prefix_tree() {
    tree.push_back(make_tree_vertex(0, '$'));
}

pr_tree_vertex Prefix_tree::make_tree_vertex(int p, char c) {
    pr_tree_vertex v;  //create tree
    memset(v.next_vertex, 255, sizeof(v.next_vertex));  //255 = -1
    memset(v.auto_move, 255, sizeof(v.auto_move));
    v.flag = false;
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
        if (tree[num].next_vertex[ch] == -1) {  //-1 - the sign of the absence of an rib
            tree.push_back(make_tree_vertex(num, ch));
            tree[num].next_vertex[ch] = tree.size() - 1;
        }
        num = tree[num].next_vertex[ch];
    }
    tree[num].flag = true;
    pattern.push_back(str);
    tree[num].pat_num = pattern.size() - 1;
}

bool Prefix_tree::is_string_in_tree(const string &s) {
    int num = 0;
    for (int i = 0; i < s.length(); i++) {
        char ch = s[i] - 'a';
        if (tree[num].next_vertex[ch] == -1) {
            return false;
        }
        num = tree[num].next_vertex[ch];
    }
    return true;
}

int Prefix_tree::get_suff_link(int v) {
    if (tree[v].suff_link == -1)
        if (v == 0 || tree[v].par == 0)  //if 'v' is the root or the parent of 'v' is the root
            tree[v].suff_link = 0;
        else
            tree[v].suff_link = get_auto_move(get_suff_link(tree[v].par), tree[v].symb);
    return tree[v].suff_link;
}

int Prefix_tree::get_auto_move(int v, char ch) {
    if (tree[v].auto_move[ch] == -1)
        if (tree[v].next_vertex[ch] != -1)
            tree[v].auto_move[ch] = tree[v].next_vertex[ch];
        else if (v == 0)
            tree[v].auto_move[ch] = 0;
        else
            tree[v].auto_move[ch] = get_auto_move(get_suff_link(v), ch);
    return tree[v].auto_move[ch];
}

int Prefix_tree::get_suff_link_comp(int v) {
    if (tree[v].suff_link_comp == -1) {
        int u = get_suff_link(v);
        if (u == 0)  //either 'v' is the root, or the suf. link 'v' points to the root
            tree[v].suff_link_comp = 0;
        else if (tree[u].flag) {
            tree[v].suff_link_comp = u;
        } else tree[v].suff_link_comp = get_suff_link_comp(u);
    }
    return tree[v].suff_link_comp;
}

void Prefix_tree::check(int v, int i) {
    for (int u = v; u != 0; u = get_suff_link_comp(u)) {
        if (tree[u].flag) {
            cout << i - pattern[tree[u].pat_num].length() + 1 << " " << pattern[tree[u].pat_num] << endl;
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
