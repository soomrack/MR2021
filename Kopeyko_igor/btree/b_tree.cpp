#include "b_tree.h"
#include <iostream>

#define TEMP_KEY keys[B_factor-1]
#define TEMP_POINTER pointers[B_factor]

//std::cout << "Hello, World!";
//std::cout << "Hello, World!" << std::endl;


BTree::Node::Node(){

}

BTree::Node::Node(unsigned int factor) {

    //создать массив ключей
    keys = new int [factor]; //имеется по одному резервному месту под ключ, под дату, под указатель
    //создать массив из даты
    data = new int [factor];
    //создать массив из указателей
    pointers = new Node* [factor + 1];

    keys[factor] = -1;

    pointers[factor+1] = nullptr;

    //каждому ключу дать номер -1
    for(int i = 0; i < factor; i++) {
        keys[i] = -1;
    }
    //каждому указателю дать nullptr
    for(int i = 0; i <= factor; i++) {
        pointers[i] = nullptr;
    }
}


void BTree::Node::root() {
    //заполняем узел с ключом "0"
    keys[0] = 0;
}

void BTree::print(){
    std::cout << "Б-дерево" << std::endl;
    std::cout << "{Адрес узла}[указатель] ключ [указатель] ключ [указатель]" << std::endl;
    root->print(B_factor, nullptr, nullptr);
}

void BTree::Node::print(unsigned int B_factor, BTree::Node* root, BTree::Node* parent){
    std::cout << "{" << this << "}";
    for (int i = 0; i < B_factor - 1; i++) {
        std::cout << "[" << pointers [i] << "]";
        std::cout << " " << keys[i] << " ";
    }
    std::cout << "["<< pointers[B_factor - 1] << "] ";

    std::cout << "__"<< TEMP_KEY << "__";//DEBUG
    std::cout << "<"<< TEMP_POINTER << "> \n ";

    for (int i = 0; i < B_factor; i++){
        if (pointers[i] != nullptr) {
            this->pointers[i]->print(B_factor, nullptr, nullptr);
        }
    }
}

int BTree::Node::count_free_key(int B_factor) { //возвращает количество пустых ключей (-1)
    int free_key_count = 0;
    for (int i = 0; i < B_factor - 1; i++ ) {
        free_key_count = free_key_count + (keys[i] == -1);
    }
    return free_key_count;
}

int BTree::Node::count_free_pointer(int B_factor) { //возвращает количество пустых указателей (nullptr)
    int free_pointer_count = 0;
    for (int i = 0; i < B_factor; i++){
        free_pointer_count = free_pointer_count + (pointers[i] == nullptr);
    }
    return free_pointer_count;
}

void BTree::Node::refresh(unsigned int B_factor, BTree::Node * root, BTree::Node * parent) {
    //функция установит ключ и указатель из резервной позиции в основную для соблюдения порядка
    //нормально работает только если узел переполнен
    //устанавливаем ключи




    int free_key_count = count_free_key(B_factor);
    int free_pointer_count = count_free_pointer(B_factor);

    int temp_key = this->TEMP_KEY;
    if (TEMP_KEY != -1) {
        for (int i = 0; i < B_factor; i++) {
            if (this->TEMP_KEY < keys[i]) {
                for (int k = B_factor - 1; k > i; k = k - 1) {
                    keys[k] = keys[k - 1];
                }
                keys[i] = temp_key;
                TEMP_KEY = -1;//новые строки
                break;
            }
            if (keys[i] == -1){
                keys[i] = temp_key;
                TEMP_KEY = -1;//новые строки
                break;
            }
        }
        if (free_key_count > 0) {
            TEMP_KEY = -1;
        }
    }



    //устанавливаем указатели
    if (TEMP_POINTER != nullptr) { //на случай если временного указателя нет
        Node * temp_pointer = this->TEMP_POINTER;
        for (int i = 0; i <= B_factor; i++) {
            if (pointers[i] == nullptr){

                pointers[i] = temp_pointer;
                TEMP_POINTER = nullptr; //новые строки
                break;
            }
            if (temp_pointer->keys[0] < pointers[i]->keys[0]) {

                for (int k = B_factor; k > i; k = k - 1) {
                    pointers[k] = pointers[k - 1];
                }
                pointers[i] = temp_pointer;
                TEMP_POINTER = nullptr;//новые строки
                break;
            }
        }
        if (free_pointer_count > 0) {
            TEMP_POINTER = nullptr; //ВЕРНУТЬ ИЗ КОММЕНТАРИЯ
        }
    }
}

void BTree::Node::add_to_any_child (unsigned int B_factor, int key, int free_key_count, BTree::Node * root) {
    //переходим по указателю
    for (int k = 0; k < (B_factor -1) - free_key_count; k++){
        if (key < keys[k]) {
            this->pointers[k]->add( key, B_factor, pointers[k], root, this);
            break;
        }
        if (((B_factor - 2) - free_key_count) == k) { //если это последний цикл, переходим в последний узел
            this->pointers[k+1]->add( key, B_factor, pointers[k+1] , root, this);

            break;
        }
    }
}

void BTree::Node::add_only_to_this (unsigned int B_factor, int key, int free_key_count, BTree::Node * root, BTree::Node * parent) {
    for(int i = 0; i < B_factor - 1; i++){
        if (key < keys[i]){
            //сдвинуть ключи и вставить наш.
            for (int j = i; j < B_factor - 2; j++){
                keys[j + 1] = keys[j];
            }
            keys[i] = key;
            break;
        }
        if (keys[i] == -1) { //вставить наш следующим
            keys[i] = key;
            break;
        }
    }
}







void BTree::Node::Node_segmentation_root (unsigned int B_factor, BTree::Node* active_node, int key, BTree::Node * root, BTree::Node * parent){
//пока опишем создания узла в случае если у родительского узла есть свободные места
    int free_pointer_count = count_free_pointer(B_factor);



    //создаем 2 узла
    Node* a = active_node->pointers[0];
    Node* b = active_node->pointers[1];

    active_node->pointers[0] = new BTree::Node (B_factor);
    active_node->pointers[1] = new BTree::Node (B_factor);

     //если мы делим узел коренной и ничего не переносим наверх

        //определяем центр
        int center = (B_factor - 1) / 2;

        //заполняем первый до центра
        for (int i = 0; i < center; i++) {
            active_node->pointers[0]->keys[i] = active_node->keys[i];
        }

        //заполняем второй после центра
        for (int i = center + 1; i < (B_factor - 1); i++) {
            active_node->pointers[1]->keys[i - (center + 1)] = active_node->keys[i];
        }

        //сохраняем центр и удаляем все лишнее
        active_node->keys[0] = active_node->keys[center];
        for (int i = 1; i < B_factor - 1; i++) {
            active_node->keys[i] = -1;
        }
        //если у узлов имеются ссылки
        if (free_pointer_count == 0) {
            active_node->pointers[0]->pointers[0] = a;
            active_node->pointers[0]->pointers[1] = b;

            //заполняем первый до центра
            for (int i = 2; i <= center; i++) {
                active_node->pointers[0]->pointers[i] = active_node->pointers[i];
                active_node->pointers[i] = nullptr;
            }
            //заполняем второй после центра
            for (int i = center + 1; i < B_factor; i++) {
                active_node->pointers[1]->pointers[i - (center + 1)] = active_node->pointers[i];
                active_node->pointers[i] = nullptr;
            }

        }
}

/*
void BTree::Node::Node_segmentation_move (unsigned int B_factor, BTree::Node* active_node, int key, BTree::Node * root, BTree::Node * parent) {
    int free_pointer_count = count_free_pointer(B_factor);
    /*
    for (int i = 0; i < B_factor; i++){
        free_pointer_count = free_pointer_count + (parent->pointers[i] == nullptr);
        //если указателя узла нулевые
    }


    parent->pointers[B_factor - free_pointer_count] = new BTree::Node (B_factor); //вставляем в верхний узел ссылку на новый
    int center = (B_factor - 1) / 2;

    parent->keys[(B_factor - 1) - free_pointer_count] = this->keys[center]; //переносим центральный ключ наверх

    //переносим ключи от центра в новый узел
    for (int i = center + 1; i < B_factor -1; i++) {
        parent->pointers[B_factor - free_pointer_count]->keys[i - (center + 1)] = active_node->keys[i];
    }

    //удаляем лишние ключи
    for (int i = center; i < (B_factor - 1); i++) {
        keys[i] = -1;
    }

    //переносим указатели
    for (int i = center + 1; i < B_factor; i++) {
        parent->pointers[B_factor - free_pointer_count]->pointers[i - (center + 1)] = this->pointers[i];
    }


}
*/


void BTree::Node::Node_segmentation_round (unsigned int B_factor, BTree::Node* active_node, int key, BTree::Node * root, BTree::Node * parent) {
    int free_pointer_count = count_free_pointer(B_factor);
    int free_key_count = count_free_key(B_factor);
    int center = (B_factor - 1) / 2;

    if (parent->count_free_key(B_factor) > 0) { //если у родителей есть место


        if(this->TEMP_KEY != key){
            this->TEMP_KEY = key;
        }

        //сначала добавляем резервные места в основу
        this->refresh(B_factor,root,parent);


        parent->TEMP_POINTER = new BTree::Node (B_factor); //вставляем в верхний узел ссылку на новый


        parent->TEMP_KEY = this->keys[center]; //средний увели к родителям
        keys[center] = -1;



        for (int i = center + 1; i < (B_factor); i++) {
            parent->TEMP_POINTER->keys[i - (center + 1)] = this->keys[i];
            //parent->TEMP_POINTER->keys[i - (center + 1)] = 99;
            this->keys[i] = -1;
        }
        for (int i = center + 1; i <= B_factor; i++) {
            parent->TEMP_POINTER->pointers[i - (center + 1)] = this->pointers[i];
            pointers[i - (center + 1)] = this->pointers[i] = nullptr;
        }




        parent->refresh(B_factor,root,nullptr); //средний распределили у родителей


    } else {
        //сверху нет места, рекурсия

        if(this->TEMP_KEY != key){
            this->TEMP_KEY = key;
        }

        this->refresh(B_factor,root,parent);


        parent->TEMP_POINTER = new BTree::Node (B_factor); //новый узел во временный адрес наверх

        parent->TEMP_KEY = this->keys[center];//центральный ключ во временный наверх
        this->keys[center] = -1;



        for (int i = center + 1; i < B_factor -1; i++) { //переносим ключи после центрального в новый узел
            TEMP_POINTER->keys[i - (center + 1)] = this->keys[i];
            this->keys[i] = -1;
        }


        // переместим указатели от центрального в новый узел и обнулим их
        for (int i = center + 1; i < B_factor; i++) {
            TEMP_POINTER->pointers[i - (center + 1)] = this->pointers[i];
            this->pointers[i] = nullptr;
        }
    }

}






void BTree::Node::set(int keys_in[], Node **pointers_in) {
    keys = keys_in;
    pointers = pointers_in;
}

BTree::BTree() {
    B_factor = 4;
    root = new Node (B_factor);
    root->root();
}

void BTree::add(int key) {
    root->add(key, B_factor, root, root, nullptr);
}

void BTree::Node::add(int key, unsigned int B_factor, Node * active_node, Node * root, Node * parent) {
    int free_pointer_count = count_free_pointer(B_factor);
    int free_key_count = count_free_key(B_factor);

    //Если нет указателей и есть пустые места

    if ((free_pointer_count == B_factor) && free_key_count){ //добавляем в этот узел
        //вводим новый ключ
        add_only_to_this(B_factor, key, free_key_count, root, parent);

        // Если есть пустые места, но есть указатели
    } else if ((free_key_count > 0) && (free_pointer_count < B_factor)) { // выбираем указатель на ребенка и активируем добавление в ребенка
        this->add_to_any_child(B_factor, key, free_key_count, root);
    //}else if ((free_key_count == 0) && (free_pointer_count == 0) && (TEMP_KEY == -1) && (TEMP_POINTER == nullptr)) {
       //     this->add_to_any_child(B_factor, key, free_key_count, root);

    } else if (free_key_count == 0) { //если все места заняты, но есть пустые указатели
          //если узел кореенной
        if (this == root) {
            this->Node_segmentation_root(B_factor, active_node, key, root, parent);
            this->add(key, B_factor, this, root, parent);

            // если у родителей есть пустое место
        } else if ((free_key_count == 0) && (free_pointer_count == 0) && (TEMP_KEY == -1) && (TEMP_POINTER == nullptr)){
            this->add_to_any_child(B_factor, key, free_key_count, root);


        } else if (parent->count_free_key(B_factor)) {


            this->Node_segmentation_round(B_factor, this, key, root, parent);
            //this->Node_segmentation_move(B_factor,this,key,root,parent);

        }
    } else { //все указатели заняты, все ключи заняты

    }
}












/*

class Node;
class Node {
private:
    int* keys;
    void* data;
    Node* child;

    Node(); //конструтор
    Node(const int key; const void* data); //конструктор с ключом и данными
    Node(const Node &node); //конструктор копий
    Node(const Node &&node); //конструтор переноса (будет очень важен)
    virtual ~Node(); //деструктор
    friend class Btree;

};




//должны быть следующие функции

// изображение дерева??? (вывод всех узлов в список)

// ребалансировка дерева

// функции обработки действия пользователя

// В деструктере данные не удаляем (сказад препод)

*/

