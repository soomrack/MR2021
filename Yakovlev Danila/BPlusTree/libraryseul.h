//
// Created by Мотылек on 13.05.2022.
//
#ifndef TOKIO3_LIBRARYSEUL_H
#define TOKIO3_LIBRARYSEUL_H
//б+ дерево в отличие от б дерева
//значения только в листьях, а в узлах копии
//листья содержат ссылки дна соседа побольше (не помню есть ли в простом б)

#include <iostream>
#include <cstring>
#include <vector>

#define MAX 2147483647
#define MIN -2147483648

using namespace std;

class BPTree;
class Node;

class Node{
    friend class BPTree;
private:                                //для узла
    int max_ref_child_id;                  //заполненность
    vector <Node*> child_array;              // массив со ссылками на детей
    int *key_copy;                       //массив копий ключей
    int size_array;                     //размер массивов, равный бфактору
private:                                //для листа
    bool leaf;                     //лист если тру
    Node* neighbour;               //ссылка на соседа
    int key_data;                  //значение в листе
private:
    Node(int data_leaf_or_bfactor,bool leaf_or_node);
    Node(const Node &node); //конструктор копирования
    Node(Node &&node) noexcept;//конструктор перемещений
    ~Node();//деструктор
};

class BPTree{
    friend class Node;
private:
    int b_factor;               //ветвистость = 2t-1 так как нумерация с нуля
    int t;                      //нумерация с 1
    Node* root;                //ссылка на текущий корень дерева
    Node* newroot;              //временный корень, так как у меня там что-то все ломается при делении корня
private:                            //вспомогательные плюшки
    int H;                     //высота дерева
    bool Hplus;                 //высота изменилась
    Node* *ptr_path_array;     //массив ссылок узлов от корня до нужного листа
public:
    BPTree(int t);
    ~BPTree();
public:
    bool search(int leaf); //работает
    void* add(int leaf); //работает
    void* del(int leaf); //пока концепция
    void print(); // работает
private://search
    bool search(int leaf, Node* ref_node, int floor);
private://add
    int search_place_for_add(int leaf, Node* &ref_node, int floor, int floors_for_separation);
    void* node_separation(Node* &ref_node,Node* &ref_parent_node, int floor, int leaf);
    int search_for_the_first_leaf_of_this_branch(Node* ref_node, int floor);
private://add and dell
    Node* search_neighbour_left(int leaf, Node* &ref_node, int floor);
    Node* search_neighbour_right(int leaf, Node* &ref_node, int floor);
private://dell
    bool search_place_for_del(int leaf, Node* &ref_node, int floor);
    void* tree_edits_after_deletion(Node* &ref_node,Node* &ref_parent_node, int floor);
private://print
    Node* search_once_leaf(Node* ref_node, int floor);
    Node* print_leaf(Node* ref_leaf);
};

#endif //TOKIO3_LIBRARYSEUL_H
