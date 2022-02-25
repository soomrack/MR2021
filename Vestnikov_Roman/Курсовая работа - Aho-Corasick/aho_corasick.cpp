#include "aho_corasick.h"

vector<bohr_vertex> bohr;
vector<string> pattern;

bohr_vertex make_bohr_vertex(int p, char c) {
    bohr_vertex v;  //create bohr
    memset(v.next_vertex, 255, sizeof(v.next_vertex));  //255 = -1
    memset(v.auto_move, 255, sizeof(v.auto_move));
    v.flag = false;
    v.suff_link = -1;  //initially, there is no suf. link
    v.g_suff_link = -1;
    v.par = p;
    v.symb = c;
    return v;
}

void bohr_ini() {
    //adding a single vertex - the root
    bohr.push_back(make_bohr_vertex(0, '$'));
}

void add_str_to_bohr(const string &str) {
    int num = 0;  //starting from the root
    for (int i = 0; i < str.length(); i++) {
        char ch = str[i] - 'a';  //get the number in the alphabet
        if (bohr[num].next_vertex[ch] == -1) {  //-1 - the sign of the absence of an rib
            bohr.push_back(make_bohr_vertex(num, ch));
            bohr[num].next_vertex[ch] = bohr.size() - 1;
        }
        num = bohr[num].next_vertex[ch];
    }
    bohr[num].flag = true;
    pattern.push_back(str);
    bohr[num].pat_num = pattern.size() - 1;
}

bool is_string_in_bohr(const string &s) {
    int num = 0;
    for (int i = 0; i < s.length(); i++) {
        char ch = s[i] - 'a';
        if (bohr[num].next_vertex[ch] == -1) {
            return false;
        }
        num = bohr[num].next_vertex[ch];
    }
    return true;
}

int get_suff_link(int v) {
    if (bohr[v].suff_link == -1)
        if (v == 0 || bohr[v].par == 0)  //if 'v' is the root or the parent of 'v' is the root
            bohr[v].suff_link = 0;
        else
            bohr[v].suff_link = get_auto_move(get_suff_link(bohr[v].par), bohr[v].symb);
    return bohr[v].suff_link;
}

int get_auto_move(int v, char ch) {
    if (bohr[v].auto_move[ch] == -1)
        if (bohr[v].next_vertex[ch] != -1)
            bohr[v].auto_move[ch] = bohr[v].next_vertex[ch];
        else if (v == 0)
            bohr[v].auto_move[ch] = 0;
        else
            bohr[v].auto_move[ch] = get_auto_move(get_suff_link(v), ch);
    return bohr[v].auto_move[ch];
}

int get_suff_link_good(int v) {
    if (bohr[v].g_suff_link == -1) {
        int u = get_suff_link(v);
        if (u == 0)  //either 'v' is the root, or the suf. link 'v' points to the root
            bohr[v].g_suff_link = 0;
        else if (bohr[u].flag) {
            bohr[v].g_suff_link = u;
        } else bohr[v].g_suff_link = get_suff_link_good(u);
    }
    return bohr[v].g_suff_link;
}

void check(int v, int i) {
    for (int u = v; u != 0; u = get_suff_link_good(u)) {
        if (bohr[u].flag) {
            cout << i - pattern[bohr[u].pat_num].length() + 1 << " " << pattern[bohr[u].pat_num] << endl;
        }
    }
}

void find_all_pos(const string &s) {
    int u = 0;
    for (int i = 0; i < s.length(); i++) {
        u = get_auto_move(u, s[i] - 'a');
        check(u, i + 1);
    }
}
