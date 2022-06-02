#ifndef RTREE_LIBRARY_H
#define RTREE_LIBRARY_H

#include <string>
#include <vector>
#include <stack>

class r_tree;
class rectangle;
class Irt_node;
class rt_node;
class leaf_rt_node;
struct splitNodes;

//imt_exception--------
class imt_exception : public std::exception {
    std::string statement;
public:
    imt_exception(const std::string statement) : statement(statement) {};

    const char *what() const noexcept override { return &(*statement.begin()); }
};

//point---------------
class point {
public: 
    double x;
    double y;

    point(const double x = 0, const double y = 0) : x(x), y(y) {};

    point(const point &other) : x(other.x), y(other.y) {};

    point(const point &&other) : x(other.x), y(other.y) {};

    point &operator=(const point &other);

    point &operator=(const point &&other);

    virtual ~point() = default;

    bool operator==(const point &other) const;
    bool operator!=(const point &other) const { return !operator==(other); }

private:
    bool _isInRectangle(const rectangle& rec);
    friend class rectangle;
};

//rectangle----------
class rectangle {
public:
    point l_point;
    point r_point;

    rectangle(const point left_point, const point right_point) : l_point(left_point), r_point(right_point) {
        _normalize();
    };

    rectangle(const double frst_x = 0, const double frst_y = 0, const double sec_x = 0, const double sec_y = 0) :
            rectangle(point(frst_x, frst_y), point(sec_x, sec_y)) {
        _normalize();
    };

    rectangle(const rectangle &other) : l_point(other.l_point), r_point(other.r_point) {
        _normalize();
    };

    rectangle(const rectangle &&other) : l_point(other.l_point), r_point(other.r_point) {
        _normalize();
    };

    virtual ~rectangle() = default;

    bool areCrossedWith(const rectangle& other) const;

    std::vector<point> getAllPoints() const;

    rectangle getOverlapRecWith(const rectangle& other) const;

    double getOverlapSizeWith(const rectangle& other) const;

    double area() const;

    bool operator==(const rectangle &other) const;

    rectangle& operator=(const rectangle& other);

    rectangle operator+(const rectangle& other);

private:
    void _normalize();

    rectangle _tryExtendTo(const rectangle& other) const;

    void _extendTo(const rectangle& other);

    double _increasingArea(const rectangle& other) const;

    friend class r_tree;
    friend class Irt_node;
    friend class leaf_rt_node;
};

//Irt_node---------------
//Parrent class for nodes
class Irt_node {
protected:
    std::vector<rectangle> child_mbr_v;
    rectangle mbr;

public:
    Irt_node(const size_t branch_fcr) { child_mbr_v.reserve(branch_fcr); }

    Irt_node(const Irt_node &other) : child_mbr_v(other.child_mbr_v) {};

    Irt_node(const Irt_node &&other) : child_mbr_v(other.child_mbr_v) {};

    virtual ~Irt_node() = default;

    bool operator==(const Irt_node &other) const;

protected:
    bool _isLeaf() const;

    bool _isFull(const size_t branch_fctr) const;

    bool _isOverloaded(const size_t branch_fctr) const;

    rectangle _getMbr() const;

    void _updateMbr();

    bool _childsAreLeafs() const;

    double _getOverlappingSize(std::vector<Irt_node*> &nodes) const;

    double _wastedArea() const;

    friend class r_tree;
    friend class rt_node;
};

//rt_node---------------
class rt_node : public Irt_node {
    std::vector<Irt_node*> child_v;

public:
    rt_node(const size_t branch_fcr) : Irt_node(branch_fcr) { child_v.reserve(branch_fcr); }

    rt_node(const rt_node &other) : Irt_node(other), child_v(other.child_v) {};

    rt_node(const rt_node &&other) : Irt_node(other), child_v(other.child_v) {};

    void _insertSameAge(const rt_node &other);

    void _eraseEntry(Irt_node* child);

    void _updateEntryMbr(Irt_node* child);

    rt_node& operator=(const rt_node &other);

    virtual ~rt_node() = default;

private:
    friend class r_tree;
    friend class Irt_node;
};

//leaf_rt_node---------
class leaf_rt_node : public Irt_node {
    std::vector<void*> data_v;

public:
    leaf_rt_node(const size_t branch_fcr) :  Irt_node(branch_fcr) { data_v.reserve(branch_fcr); };

    leaf_rt_node(leaf_rt_node &other) : Irt_node(other), data_v(other.data_v) {};

    leaf_rt_node(leaf_rt_node &&other) : Irt_node(other), data_v(other.data_v) {};

    void _insertSameAge(const leaf_rt_node &other);

    leaf_rt_node& operator=(const leaf_rt_node &other);

    virtual ~leaf_rt_node() = default;

private:
    
    friend class r_tree;
    friend class Irt_node;
};



//r-tree------------
class r_tree {  
    Irt_node *root = nullptr;
    size_t height = 0;
    const size_t min_child_num;
    const size_t branch_fctr; 

public:
    r_tree(const size_t min_child_num = 2, const size_t branch_fctr = 4);

    ~r_tree() { clear(); }

    void insert(void *const data, const rectangle insertingArea);

    std::vector<void*> search(const rectangle searchArea) const;

    void remove(void *const data, const rectangle searchArea);

    void clear();

private:
    Irt_node* _chooseLeaf(Irt_node* curr_I,
                          void *const data,
                          const rectangle &insertingArea,
                          std::stack<Irt_node*> &ancestry) const;

    Irt_node* _chooseSubTree(Irt_node* curr_I, const rectangle &insertingArea) const;

    splitNodes _doInsert(Irt_node* leaf_I, void *const data, const rectangle &insertingArea);

    splitNodes _split(Irt_node* node);

    splitNodes _splitLeaf(Irt_node* node);

    splitNodes _splitNode(Irt_node* node);

    splitNodes _adjustTree(Irt_node* node, splitNodes result, std::stack<Irt_node*> &ancestry, bool &rootWasSplited);

    size_t _getSubtreeHeight(rt_node* localRoot) const;
    
    void _condenseTree(Irt_node* node, std::stack<Irt_node*> &ancestry, std::stack<Irt_node*> &orphanedSet);

    void _reinsertOrphanedSet(Irt_node* curr_I);

    void _insertChildSplited(Irt_node *parrent, Irt_node *child);

    void _clearSplitNodes(splitNodes &sn) const; 

    std::pair<int, int> _pickSeedsId(std::vector<rectangle> &rec_v) const;

    std::vector<leaf_rt_node*> _searchCrossedLeafs(const rectangle searchArea) const;

    bool _wasSplited(const splitNodes &result) const;

    int _pickNextId(Irt_node* group1, Irt_node* group2, std::vector<rectangle> &toAssert) const;
};






struct splitNodes 
{
    splitNodes(Irt_node* first = nullptr, Irt_node* second = nullptr) : 
        first(first) , second(second) {};
    Irt_node* first;
    Irt_node* second;
};


#endif //RTREE_LIBRARY_H
