#ifndef BTREE_B_TREE_H
#define BTREE_B_TREE_H

class BTree {
public:
    class Node {
    public:
        int *keys;
        int *data;
        Node **pointers;

        //int temp_key;
        //Node *temp_pointer;
    public:
        Node();
        Node(unsigned int factor);
    public:
        void root();
        void set(int keys[], Node* pointers[]);
        void print(unsigned int B_factor, Node* root, Node* parent);
        void add(int key, unsigned int B_factor, Node * active_node, Node * root, Node * parent);
        void Node_segmentation_root (unsigned int B_factor, Node* active_node, int key, Node * root, Node * parent);
        void Node_segmentation_move (unsigned int B_factor, Node* active_node, int key, Node * root, Node * parent);
        void Node_segmentation_round (unsigned int B_factor, Node* active_node, int key, Node * root, Node * parent);

        int count_free_key(int B_factor);
        int count_free_pointer(int B_factor);
        void refresh(unsigned int B_factor, BTree::Node * root, BTree::Node * parent);
        void add_to_any_child (unsigned int B_factor, int key, int free_key_count, BTree::Node * root);
        void add_only_to_this (unsigned int B_factor, int key, int free_key_count, BTree::Node * root, BTree::Node * parent);

        friend class Btree;
    };

public:
    unsigned int B_factor;
    Node* root;
public:
    BTree();
//public:
    void add(int key);
    void print();
    //void show_info();
    friend class Node;
};






/*
class Node {
private:
    int* keys;
    void* data;
    Node* child;

    //Node(); //конструтор
    //Node(const int key; const void* data); //конструктор с ключом и данными
    //Node(const Node &node); //конструктор копий
    //Node(const Node &&node); //конструтор переноса (будет очень важен)
    //virtual ~Node(); //деструктор
    //friend class Btree;

};

class Btree {
private:
    //Node *root;

//public:
    //Btree();
   // Btree(const Btree &tree)//конструктор копий
    //Btree(const Btree &&tree)
    //virtual ~Btree();

    //void* search(const int key) =0;
    //int add(const int key, const void* data) =0;
    //int del(const int key) =0;   //=0 делает функцию абстрактной

//private:
    //void del_subtree(Node *root);
    //void* search(const int key, const Node* root);
};
*/






#endif //BTREE_B_TREE_H
