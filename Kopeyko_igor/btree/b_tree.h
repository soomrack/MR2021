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
    void count_tree(); //Вывод числа ключей в дереве
    void print_keys_in_string(); //Вывод ключей дерева в порядке возрастания
    void add(int key);
    void print(); //Вывод дерева (каждый узел в новую строку)
    int search(int key);
    void delete_key(int key);

    virtual ~BTree() = default;

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
    void root(); //Присваивает ключ со значением ноль в кореной узел
    void print(unsigned int B_factor, Node* root, Node* parent); //Выводит этот узел и всех его детей
    void print_only_this(unsigned int B_factor, Node* root, Node* parent); //DEBUG Выводит только конкретный узел
    int count_tree(unsigned int B_factor, Node* root); //Вспомогательная функция счета числа ключей
    int print_keys_in_string(unsigned int B_factor); //Вспомогательная функция вывода ключей в строку в порядке возрастания
    void add(int key, unsigned int B_factor, Node * active_node, Node * root, Node * parent);
    void Node_segmentation_root (unsigned int B_factor, Node* active_node, int key, Node * root, Node * parent); //Разделение на 2 узла при переполнении в случае если это корень
    void Node_segmentation_round (unsigned int B_factor, Node* active_node, int key, Node * root, Node * parent); //Разделение на 2 узла в большинстве случаев (с рекурсией)

    Node* search(int key, int level_down, int B_factor, Node * root, Node * active_node, Node* node_with_key); //Возвращает адрес узла, в котором найден ключ

    int count_keys(int B_factor); //Считает число ключей в конкретном узле
    int count_pointers(int B_factor); //Считает число указателей в конкретном узле

    void remove_free_pointer(int B_factor); //Сдвигает ключи при образовании свободного пространства (ключ был удален)
    void remove_free_place( int B_factor); //Сдвигает указатели при образовании свободного пространства
    int ask_brother_key(int key, int B_factor, Node * node_with_key, Node* parent, Node * root); //Запрос свободных ключей у братьев без указателей
    int merge_nodes_brothers(int key, int B_factor, Node* node_with_key, Node* parent, Node* root, int parent_status); //Сливаие братьев без указателей в один узел
    int ask_brother_key_with_pointers(int key, int B_factor, Node* node_with_key, Node*parent, Node* root); //Запрос ключей у братьев с указателми
    int lift_up_left (int key, int B_factor, Node * root, Node * parent, Node * node_with_key, int key_index); //Запрос свободного ключа у самого нижнего узла слева от выбранного
    int lift_up_right (int key, int B_factor, Node * root, Node * parent, Node * node_with_key, int key_index); //Запрос свободного ключа у самого нижнего ключа справа от выбранного
    void merge_nodes_brothers_with_pointers(int key, int B_factor, Node* node_with_key, Node* parent, Node* root, int parent_status); //Сливание братьев с указателями в один узел
    void steal_down_key(int key, int B_factor, Node* node_with_key, Node* parent, Node* root, int key_index); //Забираем насильно ключ снизу у нижнего узла, теперь нижней узел будет искать себе ключ
    void change_root(Node* new_root, Node* root, int B_factor); //Объявить новый корень

    void del_key_only_this(int key, int B_factor, Node * node_with_key); //Удалить ключ в рамках этого узла
    void delete_key(int key, int B_factor, Node * root, Node * parent, Node * node_with_key, int is_used); //Удалять ключ в этом узле или ниже

    Node* find_this_parent (int B_factor, Node * active_node, Node * root); //Найти радоителя этого узла

    int count_free_key(int B_factor); //Подсчет числа свободных мест для ключей в узле
    int count_free_pointer(int B_factor); //Подсчет числа свободных мест для указателей в узле
    void refresh(unsigned int B_factor, Node * root, Node * parent); //Установить ключ и указатель из резервной позиции в основную для соблюдения порядка
    void add_to_any_child (unsigned int B_factor, int key, int free_key_count, Node * root); //Добавить ключ к узлам ниже
    void add_only_to_this (unsigned int B_factor, int key, int free_key_count, Node * root, Node * parent); //Добавить ключ в этот узел

    virtual ~Node();

    friend class BTree;
};

#endif //BTREE_B_TREE_H