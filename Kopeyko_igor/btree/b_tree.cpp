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
    std::cout << " ============= Б-дерево ===============" << std::endl;
    std::cout << "{Адрес узла}[указатель] ключ [указатель] ключ [указатель]" << std::endl;
    root->print(B_factor, nullptr, nullptr);
    std::cout << " ============= Конец ===============" << std::endl;
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

void BTree::Node::print_only_this(unsigned int B_factor, BTree::Node* root, BTree::Node* parent) {
    std::cout << "{" << this << "}";
    for (int i = 0; i < B_factor - 1; i++) {
        std::cout << "[" << pointers [i] << "]";
        std::cout << " " << keys[i] << " ";
    }
    std::cout << "["<< pointers[B_factor - 1] << "] ";

    std::cout << "__"<< TEMP_KEY << "__";//DEBUG
    std::cout << "<"<< TEMP_POINTER << "> \n ";
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
                //TEMP_KEY = -1;//новые строки
                break;
            }
            if (keys[i] == -1){
                keys[i] = temp_key;
                //TEMP_KEY = -1;//новые строки
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
                //TEMP_POINTER = nullptr; //новые строки
                break;
            }
            if (temp_pointer->keys[0] < pointers[i]->keys[0]) {

                for (int k = B_factor; k > i; k = k - 1) {
                    pointers[k] = pointers[k - 1];
                }
                pointers[i] = temp_pointer;
                //TEMP_POINTER = nullptr;//новые строки
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
    int a = 0;
    for(int i = 0; i < B_factor - 1; i++){
        if (key < keys[i]){
            //сдвинуть ключи и вставить наш.
            for (int j = B_factor - 3; j >= i; j = j - 1/*int j = i; j < B_factor - 2; j++*/){

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

BTree::Node * BTree::Node::find_this_parent(int B_factor, Node * active_node, Node * root){

    if(this == root){
        return nullptr;
    }

    //this это родителей которого мы ищем. Активный это тот с которого начинаем

    Node * needed_parent = nullptr;

    //проверим наличия ребенка с нужным адресом
    std::cout << "ПОИСК РОДИТЕЛЯ!" << std::endl;
    active_node->print_only_this(B_factor, nullptr, nullptr);

    for (int i = 0; i < B_factor; i++) {
        if (active_node->pointers[i] == this) {
            std::cout << "тут есть родитель!" << std::endl;
            return active_node;
        }
    }

    std::cout << "В этом узле подходящего указателя нет!" << std::endl;
    active_node->print_only_this(B_factor, nullptr, nullptr);




    //выберем в какой указатель переходить
    for (int k = 0; k < B_factor; k++){
        if (this->keys[0] < active_node->keys[k]) {
            std::cout << "Переходим ниже на основе сравнения!" << std::endl;
            std::cout << this->keys[0] << " < " << active_node->keys[k] << std::endl;

            needed_parent = this->find_this_parent(B_factor, active_node->pointers[k],root);

            break;
        }
        if ((active_node->keys[k] == -1)) { //если это последний цикл, переходим в последний узел
            std::cout << "Переходим ниже по последнему!" << std::endl;
            needed_parent = this->find_this_parent(B_factor, active_node->pointers[k],root);
            break;
        }
    }

    std::cout << "Искали родиетля в этом узле!" << std::endl;
    active_node->print_only_this(B_factor, nullptr, nullptr);
    std::cout << "Искали родиетля для этого узла!" << std::endl;
    this->print_only_this(B_factor, nullptr, nullptr);

    std::cout << "нашлииииии!" << needed_parent << std::endl;
    return needed_parent;
}







void BTree::Node::Node_segmentation_root (unsigned int B_factor, BTree::Node* active_node, int key, BTree::Node * root, BTree::Node * parent){
//пока опишем создания узла в случае если у родительского узла есть свободные места
    int free_pointer_count = count_free_pointer(B_factor);

    this->refresh(B_factor,root, nullptr); //new

    std::cout << "ROOT!" << std::endl;



    //создаем 2 узла
    Node* a = active_node->pointers[0];
    Node* b = active_node->pointers[1];

    active_node->pointers[0] = new BTree::Node (B_factor);
    active_node->pointers[1] = new BTree::Node (B_factor);

    std::cout << "Живы 1!" << std::endl;

     //если мы делим узел коренной и ничего не переносим наверх

        //определяем центр
        int center = (B_factor - 1) / 2;

        //заполняем первый до центра
        for (int i = 0; i < center; i++) {
            active_node->pointers[0]->keys[i] = active_node->keys[i];
        }

        //заполняем второй после центра
        for (int i = center + 1; i < (B_factor /*- 1*/); i++) {
            active_node->pointers[1]->keys[i - (center + 1)] = active_node->keys[i];
        }

    std::cout << "Живы 2!" << std::endl;

        //сохраняем центр и удаляем все лишнее
        active_node->keys[0] = active_node->keys[center];
    std::cout << "Живы 21!" << std::endl;
        for (int i = 1 /*был центр ну я сделал 1*/; i < B_factor/* - 1*/; i++) {
            active_node->keys[i] = -1;
        }
    std::cout << "Живы 22!" << std::endl;
        //если у узлов имеются ссылки
        if (free_pointer_count == 0) {
            std::cout << "Живы 23!" << std::endl;
            active_node->pointers[0]->pointers[0] = a; //было active_node->pointers[0]->pointers[0] = a;
            active_node->pointers[0]->pointers[1] = b; //было active_node->pointers[0]->pointers[1] = a;
            std::cout << "Живы 24!" << std::endl;

            std::cout << "Проверка!"  << center << std::endl;
            std::cout << active_node->pointers[0] << std::endl;
            std::cout << active_node->pointers[0]->pointers[1] << std::endl;
            std::cout << active_node->pointers[1] << std::endl;



            //заполняем первый до центра
            for (int i = 2; i <= center; i++) {
                std::cout << "Проверка ww!" << std::endl;
                //std::cout << active_node->pointers[0]/*->pointers[i]*/ << "   =   "  << active_node->pointers[i] << std::endl;
                active_node->pointers[0]->pointers[i] = active_node->pointers[i];
                std::cout << "Проверка!" << std::endl;
                active_node->pointers[i] = nullptr;
                std::cout << "Проверка!" << std::endl;
            }
            std::cout << "Живы 25!" << std::endl;
            //заполняем второй после центра
            for (int i = center + 1; i < B_factor /* 1 не было*/ +1; i++) {
                active_node->pointers[1]->pointers[i - (center + 1)] = active_node->pointers[i];
                active_node->pointers[i] = nullptr;
            }

        }

    std::cout << "Живы 3!" << std::endl;
    std::cout << "Новый узлы результат!" << std::endl;
    active_node->pointers[0]->print_only_this(B_factor,root,parent);
    active_node->pointers[1]->print_only_this(B_factor,root,parent);
    std::cout << "Живы 4!" << std::endl;

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
    std::cout << "МЫ В СЕГМЕНТАЦИИ!" << std::endl;

    std::cout << "Этот узел!" << std::endl;
    this->print_only_this(B_factor, root, parent);
    std::cout << "Все дерево!" << std::endl;
    root->print(B_factor,root, nullptr);
    std::cout << "отдельно резерв!" << std::endl;
    if (root->TEMP_POINTER != nullptr) {
        root->TEMP_POINTER->print(B_factor, root, nullptr);
    }
    std::cout << "отдельно другой резерв!" << std::endl;
    if (this->TEMP_POINTER != nullptr) {
        this->TEMP_POINTER->print(B_factor, root, nullptr);
    }

    std::cout << "Конец дерева!" << std::endl;

    int free_pointer_count = count_free_pointer(B_factor);
    int free_key_count = count_free_key(B_factor);
    int center = (B_factor - 1) / 2;

    std::cout << "Тут?" << std::endl;

    if (this == root){
        //std::cout << "Тут?" << std::endl;
        this->Node_segmentation_root(B_factor,this,key,root, nullptr);
        return;
    }
    std::cout << "Тут?" << std::endl;
    std::cout << parent << std::endl;


    if (parent->count_free_key(B_factor) > 0) { //если у родителей есть место
        std::cout << "Сегментация, раздел когда сверху есть места!" << std::endl;



        if(this->TEMP_KEY == -1){
            this->TEMP_KEY = key;
        }

        std::cout << "ЭТО ТЭТО11111!" << std::endl;
        this->print(B_factor,root,parent);

        //сначала добавляем резервные места в основу
        this->refresh(B_factor,root,parent);

        std::cout << "ЭТО ТЭТО!" << std::endl;
        this->print(B_factor,root,parent);
        parent->print(B_factor,root,parent);


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
            pointers[i/* - (center + 1)*/] = this->pointers[i] = nullptr;
        }




        parent->refresh(B_factor,root,nullptr); //средний распределили у родителей
        std::cout << "Наше дерево!" << std::endl;
        root->print(B_factor,root, nullptr);
        std::cout << "Конец!" << std::endl;


    } else {
        std::cout << "Сегментация, раздел когда сверху НЕТ места!" << std::endl;
        //сверху нет места, рекурсия

        std::cout << "Родитель этого узла!" << std::endl;
        root->print(B_factor,root, nullptr);

        if(this->TEMP_KEY == -1){
            this->TEMP_KEY = key;
        }

        this->refresh(B_factor,root,parent);


        parent->TEMP_POINTER = new BTree::Node (B_factor); //новый узел во временный адрес наверх

        parent->TEMP_KEY = this->keys[center];//центральный ключ во временный наверх
        this->keys[center] = -1;



        for (int i = center + 1; i < B_factor; i++) { //переносим ключи после центрального в новый узел
            parent->TEMP_POINTER->keys[i - (center + 1)] = this->keys[i];
            this->keys[i] = -1;
        }


        // переместим указатели от центрального в новый узел и обнулим их
        for (int i = center + 1; i <= B_factor; i++) {
            parent->TEMP_POINTER->pointers[i - (center + 1)] = this->pointers[i];
            this->pointers[i] = nullptr;
        }





        std::cout << "ИТОГ сегментации с полным верхом" << std::endl;
        std::cout << "Узел родиетель!" << std::endl;
        parent->print_only_this(B_factor, root, parent);
        std::cout << "Этот узел!" << std::endl;
        this->print_only_this(B_factor, root, parent);
        std::cout << "Новый узел!" << std::endl;
        parent->TEMP_POINTER->print_only_this(B_factor, root, parent);


        //Рекурсия

        std::cout << "У этого дауна ищем родиетелей!" << std::endl;
        parent->print_only_this(B_factor,root, nullptr);

        parent->Node_segmentation_round(B_factor, parent, key, root, parent->find_this_parent(B_factor,root,root));

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
    std::cout << "Зашли в добавление!" << std::endl;
    this->print(B_factor,root,parent);
    std::cout << "^^^ еще не трогали!" << std::endl;

    //Если нет указателей и есть пустые места

    if ((free_pointer_count == B_factor) && free_key_count){ //добавляем в этот узел
        //вводим новый ключ
        std::cout << "ДОбавить только в этот!" << std::endl;
        add_only_to_this(B_factor, key, free_key_count, root, parent);

        // Если есть пустые места, но есть указатели
    } else if ((free_key_count > 0) && (free_pointer_count < B_factor)) { // выбираем указатель на ребенка и активируем добавление в ребенка
        std::cout << "К детям!" << std::endl;
        this->add_to_any_child(B_factor, key, free_key_count, root);
    //}else if ((free_key_count == 0) && (free_pointer_count == 0) && (TEMP_KEY == -1) && (TEMP_POINTER == nullptr)) {
       //     this->add_to_any_child(B_factor, key, free_key_count, root);

    } else if (free_key_count == 0) { //если все места заняты, но есть пустые указатели
        std::cout << "Ключи заполнены! Этот узел:" << std::endl;
        this->print_only_this(B_factor, root, parent);
          //если узел кореенной
        if (this == root) {
            std::cout << "ЭТО корень!" << std::endl;

            if (((this->TEMP_KEY == -1) && (this->TEMP_POINTER == nullptr)) && (free_pointer_count != B_factor)) {

                std::cout << "пустые резервы, полные указатели! ИДем вниз" << std::endl;

                this->add_to_any_child(B_factor,key,free_key_count,root);
            } else {
                std::cout << "Делим корень!" << std::endl;
                this->Node_segmentation_root(B_factor, active_node, key, root, parent);
                this->add(key, B_factor, this, root, parent);
            }

            // если у родителей есть пустое место
        } else if ((free_key_count == 0) && (free_pointer_count == 0) && (TEMP_KEY == -1) && (TEMP_POINTER == nullptr)){
            std::cout << "Попал попал" << std::endl;
            this->add_to_any_child(B_factor, key, free_key_count, root);


        } else if (/*parent->count_free_key(B_factor)*/1) {

            std::cout << "круговая сегментация!" << std::endl;


            this->Node_segmentation_round(B_factor, this, key, root, parent);
            //this->Node_segmentation_move(B_factor,this,key,root,parent);

        }
            std::cout << "вылетел конкретно" << this << std::endl;

        std::cout << "вылетел" << this << std::endl;

    } else { //все указатели заняты, все ключи заняты
        std::cout << "ушел" << std::endl;

    }
    this->print(B_factor,root,parent);

    if ((this != root)) {
        if (parent->TEMP_POINTER != nullptr) {
            std::cout << "УЗЕЛ ВРеменныЙ  " << std::endl;
            parent->TEMP_POINTER->print_only_this(B_factor, root, parent);
        }
    }

}

int BTree::search(int key){
      return root->search(key, -1, B_factor, root, root);

}

int BTree::Node::search(int key, int level_down, int B_factor, Node * root, Node * active_node){
    //переберем ключи в этом узле
    level_down++;
    //std::cout << "\n Прибавили! " << level_down << std::endl;

    for (int i = 0; i < B_factor; i++) {
        if (key == this->keys[i]) {
            //std::cout << "\n Найден ключ!" << std::endl;
            return level_down;
        }
    }
    for (int i = 0; i < B_factor; i++) {
        if (key < this->keys[i]){
            level_down = pointers[i]->search(key, level_down,B_factor,root,active_node);
            //std::cout << "\n вернем!" << level_down << std::endl;
            return level_down;
        }
        if (-1 == this->keys[i]){
            level_down = pointers[i]->search(key, level_down,B_factor,root,active_node);
            //std::cout << "\n вернем!" << level_down << std::endl;
            return level_down;
        }
    }


    //Выберем узел ребенок для перехода
    return level_down;
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

