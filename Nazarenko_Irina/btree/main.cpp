#include <iostream>
#include <cmath>


const int t = 2;
class Node;
class BTree;

class Node {
private:
    int *key;
    int *data;
    Node ** child;
    int count;
    int countSons;
    Node * parent;
    unsigned int max_key_id; //current number of keys in the node
    bool full;
    bool leaf;
public:
    Node(int bfactor);

    Node(const Node &node);

    Node(const Node &&node) noexcept ;

    virtual~ Node();

    friend class BTree;
};



class BTree {
private:
    int current_root;
    Node *root;
    unsigned int bfactor;
public:
    BTree();

    BTree(const BTree &tree);
    BTree(const BTree &&tree);

    virtual ~BTree();
    friend class Node;

public:
void* search(const int key);
void add(const int key, const int data);
void add(const int key, const int data, Node *ptr);
void print();
void print(Node *current_node);
private:
    void* search (const int key, const Node* root);

};

BTree::BTree() {
    bfactor  = 2;
    root=nullptr;

}


Node::Node(int bfactor){
    int a=ceil(2*(bfactor-2)/3);
    key = new int[a];
    data = new int [a];
    child = new *Node[a];



}

Node::~Node() {
    free(key);
    free(child);

}

Node::Node(const Node &node) {

}

Node::Node(const Node &&node) noexcept {

};


/*void* BTree::search(const int key) {
    return search(key,root);
};

void* BTree::search(const int key, const Node* root){
    if(root==nullptr) return nullptr;
    unsigned int k=0;
    while((k<root->max_key_id)and (key<root->key[k])) k++;
    if (k<= root->max_key_id) return(search(key, &root->child[k]));
    if(key==root->key[k]) {
        return root->data[k];
    }
        return search(key, root->child[k]);
        current_root=root;

    }


}
*/



void BTree::add(const int key, const int data) {
    unsigned int k=0;
    if(root==nullptr) {
        root = new Node(bfactor);
        root->key[0] = key;
        root->max_key_id =key;
        for (int j = 1; j <= (2 * ceil((2 * bfactor - 1) / 3) - 1); j++) root->key[j] = 0;
        root->count = 1;
        root->countSons = 0;
        root->leaf = true;
        root->full=false;
    }
    Node *current_node = root;
    while (key<=current_node->max_key_id){
        for (int i=0; i<=  2*ceil((2*bfactor-2)/3)-1; i++) {
            if (current_node->key[i]!=0){
                current_node=current_node->child[i];
            }
        }

        if (key==*current_node->key)
        {
            printf("такой ключ уже существует");
        }
    if (key==*current_node->key){
        printf("такой ключ уже существует");
    }


    current_node->key++;
    if (current_node->full)
    {

    }
    }

    {

    }

}

void BTree::add(const int key, const int data, Node *ptr) {

}

BTree::~BTree() {

}


void BTree::print() {
    Node *current_node = root;
    if (current_node->full) {
        for (int j = 0; j <= (2 * ceil((2 * bfactor - 1) / 3) - 1); j++) {
            printf("%d", current_node->key[j]);
        }

    }
    else{
        for (int j = 0; j <= current_node->count; j++) {
            printf("%d", current_node->key[j]);
        }

    }
        if(!current_node->leaf){
            for (int j = 0; j <= (2 * ceil((2 * bfactor - 1) / 3) - 1);j++)
            print(current_node->child[j]);
        }

}


void BTree::print(Node *current_node) {


}


int main(void){
    BTree Tree;
    Tree.add(2, 34);
    Tree.print();
}


