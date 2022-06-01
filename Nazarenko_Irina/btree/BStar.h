#include <iostream>     //std::cout, std::endl
#include <fstream>      //std::ofstream, std::ifstream
#include <cmath>        //floor, ceil
#include <algorithm>    //std::random_shuffle
#include <list>         //std::list
#include <queue>        //std::queue
#include <vector>       //std::vector
#include <array>        //std::array

#ifndef UNTITLED23_BSTAR_H
#define UNTITLED23_BSTAR_H

class Node;
class BStarTree
{

public:

    BStarTree (int order);   // BStarTree with bfactor
    ~BStarTree();
    void empty();   //to delete all keys
    bool add(double val);
    bool erase(double val);
    bool find(double val) const;
    void print() const;
    unsigned maxKeysNNode() const { return maxKeysNormalNode; }
    unsigned maxKeysRNode() const { return maxKeysRootNode; }
    unsigned minKeysNNode() const { return minKeysNormalNode; }
    unsigned minKeysRNode() const { return minKeysRootNode; }
private:
    const int ORDER; //order of the tree
    unsigned id; //id of the next element of the tree.
    Node* root;
    unsigned maxKeysNormalNode;
    unsigned maxKeysRootNode;
    unsigned minKeysNormalNode;
    unsigned minKeysRootNode;
    unsigned keysSplitChild1;
    unsigned keysSplitChild2;
    unsigned keysSplitChild3;
    void handleOverload(Node* overloadedNode);
    void handleUnderload(Node* underloadedNode);
    bool find(double val, Node*& node) const;
    Node* findPlaceAdd(double val) const;
    Node* findPlaceErase(double val) const;
    bool searchSpace(Node* node);
    bool searchSpaceErase(Node* node);
    bool isLeftmost(Node* node) const;
    bool isRightmost(Node* node) const;
    bool areLeftSiblingsFull(Node* node) const;
    bool areRightSiblingsFull(Node* node) const;
    bool areLeftSiblingsAtMinimum(Node* node) const;
    bool areRightSiblingsAtMinimum(Node* node) const;
    auto rotateLeft(Node* node);
    auto rotateRight(Node* node);
    void rotateLeftAdd(Node* node);
    void rotateRightAdd(Node* node);
    void rotateLeftErase(Node* node);
    void rotateRightErase(Node* node);
    void splitRoot();
    void splitLeft(Node* node);
    void splitRight(Node* node);
    void mergeRootChildren(Node* nodeChildren);
    void merge(Node* node);
    Node* getGreaterMinor(Node* node, double val) const;
    auto getIterator(Node* node) const;
};



class Node
{
public:
    //use the default of the following
    Node() = default; //constructor
    virtual ~Node() = default;
    Node(BStarTree const * tree, Node* ancestor = nullptr):tree(tree), ancestor(ancestor) {}

    //******************Pure virtual function***********************************
    virtual bool isOverloaded() const = 0;
    virtual bool isFull() const = 0;
    virtual bool isUnderloaded() const = 0;
    virtual bool isAtMinimum() const = 0;
    virtual bool isRoot() const = 0;
    void print() const;
    void addItem(double item);
    void addChild(Node* child);
    double popFrontKey();
    double popBackKey();
    Node* popFrontChild();
    Node* popBackChild();
    void putKeys(std::list<double>& takeList, int limit);
    void putChildren(std::list<Node*>& takeList, int limit);
    unsigned getId() const { return id; }
    std::size_t getNumKeys() const { return keysList.size(); }
    Node* getAncestor() const { return ancestor; }
    std::list<double> const & keys() const { return keysList; }
    std::list<double>& keys() { return keysList; }
    std::list<Node*> const & children() const { return childList; }
    std::list<Node*>& children() { return childList; }
    bool isLeaf() { return this->children().empty(); }

protected:
    unsigned id; //id to identify nodes
    BStarTree const * tree; //pointer to the tree
    std::list<double> keysList;     // Pointer for allocating dynamic memory store
    std::list<Node*> childList;
    Node* ancestor;

};


bool compareKeyNodes(Node* nodeA, Node* nodeB);










class NormalNode : public Node                   // Node is the base class, all public and
{                                                   // protected members of Node can be accessed
public:                                             // by NormalNode

    //use the default of the following
    NormalNode() = default; //constructor
    virtual ~NormalNode() = default;

    NormalNode(BStarTree const * tree, Node* ancestor = nullptr, unsigned id = 0);

    void setAncestor(Node* newAncestor) { this->ancestor = newAncestor; }

    //Definitions of Node class pure virtual functions

    virtual bool isOverloaded() const;
    virtual bool isFull() const;
    virtual bool isUnderloaded() const;
    virtual bool isAtMinimum() const;
    bool isRoot() const { return false; }
};










class RootNode : public Node                      // Node is the base class, all public and
    // protected members of Node can be accessed
    // by RootNode
{
public:

    //use the default of the following
    RootNode() = default; //constructor
    virtual ~RootNode() = default;
    RootNode(BStarTree const * tree, Node* ancestor = nullptr, unsigned id = 0);

    virtual bool isOverloaded() const;
    virtual bool isFull() const;
    virtual bool isUnderloaded() const;
    virtual bool isAtMinimum() const;
    bool isRoot() const { return true; }
};



void menu();
void addMenu(BStarTree& tree);
void eraseMenu(BStarTree& tree);
void findMenu(BStarTree& tree);




#endif //UNTITLED23_BSTAR_H
