#ifndef BTREE_B_TREE_H
#define BTREE_B_TREE_H

class BTree;
class Node;


class BTree {

private:
    unsigned int B_factor;
    Node* root;
public:
    BTree();
    BTree(int B_factor);
    void count_tree(); //вывод числа ключей в дереве
    void print_keys_in_string();
    void add(int key);
    void print();
    int search(int key);
    void delete_key(int key);
    friend class Node;
};


class Node {
private:
    int *keys;
    int *data;
    Node **pointers;
private:
    Node();
    Node(unsigned int factor);
private:
    void root();
    void set(int keys[], Node* pointers[]); //DEBUG
    void print(unsigned int B_factor, Node* root, Node* parent);
    void print_only_this(unsigned int B_factor, Node* root, Node* parent); //DEBUG
    int count_tree(unsigned int B_factor, Node* root);
    int print_keys_in_string(unsigned int B_factor);
    void add(int key, unsigned int B_factor, Node * active_node, Node * root, Node * parent);
    void Node_segmentation_root (unsigned int B_factor, Node* active_node, int key, Node * root, Node * parent);
    void Node_segmentation_round (unsigned int B_factor, Node* active_node, int key, Node * root, Node * parent);

    Node* search(int key, int level_down, int B_factor, Node * root, Node * active_node, Node* node_with_key);

    int count_keys(int B_factor);
    int count_pointers(int B_factor);

    void remove_free_pointer(int B_factor);
    void remove_free_place( int B_factor);
    int ask_brother_key(int key, int B_factor, Node * node_with_key, Node* parent, Node * root);
    int merge_nodes_brothers(int key, int B_factor, Node* node_with_key, Node* parent, Node* root, int parent_status);
    int ask_brother_key_with_pointers(int key, int B_factor, Node* node_with_key, Node*parent, Node* root);
    int lift_up_left (int key, int B_factor, Node * root, Node * parent, Node * node_with_key, int key_index);
    int lift_up_right (int key, int B_factor, Node * root, Node * parent, Node * node_with_key, int key_index);
    void merge_nodes_brothers_with_pointers(int key, int B_factor, Node* node_with_key, Node* parent, Node* root, int parent_status);
    void steal_down_key(int key, int B_factor, Node* node_with_key, Node* parent, Node* root, int key_index);
    void change_root(Node* new_root, Node* root, int B_factor);

    void del_key_only_this(int key, int B_factor, Node * node_with_key);
    void delete_key(int key, int B_factor, Node * root, Node * parent, Node * node_with_key, int is_used);

    Node* find_this_parent (int B_factor, Node * active_node, Node * root);

    int count_free_key(int B_factor);
    int count_free_pointer(int B_factor);
    void refresh(unsigned int B_factor, Node * root, Node * parent);
    void add_to_any_child (unsigned int B_factor, int key, int free_key_count, Node * root);
    void add_only_to_this (unsigned int B_factor, int key, int free_key_count, Node * root, Node * parent);

    friend class BTree;
};

#endif //BTREE_B_TREE_H