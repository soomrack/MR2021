#include "b_tree.h"
#include <iostream>



#define DEBUG_TREE root->print(B_factor, nullptr, nullptr);


#define TEMP_KEY keys[B_factor-1]
#define TEMP_POINTER pointers[B_factor]

#define USED 1
#define NOT_USED 0

#define PARENT_HAS_ONE_KEY 1
#define PARENT_HAS_MORE_KEYS 2
#define PARENT_ROOT_HAS_ONE 3



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

    std::cout << "ИЩЕМ РОДИТЕЛЯ ДЛЯ "<< this << std::endl;
    this->print_only_this(B_factor,root, nullptr);

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
        if (this->keys[0] <= active_node->keys[k]) {
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

BTree::Node* BTree::search(int key){
      return root->search(key, 0, B_factor, root, root, nullptr);

}

//static BTree::Node::Node** pointers_array[] = {nullptr};

BTree::Node* BTree::Node::search(int key, int level_down, int B_factor, Node * root, Node * active_node, Node* node_with_key){
    //переберем ключи в этом узле
    //Node** Pointers_array[] = {nullptr, nullptr};
    std::cout << "Hello, World!" << std::endl;
    print_only_this(B_factor,root, nullptr);

    //Node* node_with_key = nullptr;

    level_down++;
    //std::cout << "\n Прибавили! " << level_down << std::endl;

    for (int i = 0; i < B_factor; i++) {
        if (key == this->keys[i]) {
            //std::cout << "\n Найден ключ!" << std::endl;
            node_with_key = this;
            return node_with_key;//level_down;
        }
    }
    if (pointers[0] == nullptr) {
        std::cout << "\n НЕ НАЙДЕН ключ!" << std::endl;
        return nullptr;
    }
    for (int i = 0; i < B_factor; i++) {
        if (key < this->keys[i]){
            node_with_key = pointers[i]->search(key, level_down,B_factor,root,active_node, nullptr);
            //std::cout << "\n вернем!" << level_down << std::endl;
            return node_with_key;//level_down;
        }
        if (-1 == this->keys[i]){
            node_with_key = pointers[i]->search(key, level_down,B_factor,root,active_node, nullptr);
            //std::cout << "\n вернем!" << level_down << std::endl;
            return node_with_key;//level_down;
        }
    }


    //Выберем узел ребенок для перехода
    return node_with_key;//level_down;
}







//УДАЛЕНИЕ УЗЛА

int BTree::Node::count_keys(int B_factor) {
    return ((B_factor-1) - this->count_free_key(B_factor));
}

int BTree::Node::count_pointers(int B_factor) {
    return (B_factor - this->count_free_pointer(B_factor));
}

void BTree::Node::remove_free_pointer(int B_factor){
    for (int i = 0; i < B_factor - 1; i++){
        if(this->pointers[i] == nullptr){
            for (int k = i; k < B_factor - 1; k++){
                this->pointers[k] = this->pointers[k + 1];
            }
            this->pointers[B_factor-1] = nullptr;
        }
    }
}


void BTree::Node::remove_free_place(int B_factor ){
    for (int i = 0; i < B_factor - 2; i++){
        if(this->keys[i] == -1){
            for (int k = i; k < B_factor - 2; k++){
                this->keys[k] = this->keys[k + 1];
            }
            this->keys[B_factor-2] = -1;
        }
    }
}


void BTree::Node::del_key_only_this(int key, int B_factor, Node * node_with_key){
    for(int i = 0; i < B_factor - 1; i++){
        if(node_with_key->keys[i] == key){
            node_with_key->keys[i] = -1;
            break;
        }
    }
    node_with_key->remove_free_place(B_factor);
    //node_with_key->refresh(B_factor, nullptr, nullptr);
}

int BTree::Node::ask_brother_key(int key, int B_factor, Node * node_with_key, Node* parent, Node * root){
    int parent_keys_amount = parent->count_keys(B_factor);
    int node_with_key_index = -1;

    //узнаем каким по порядку идет наш узел
    for (int i = 0; i < B_factor; i++){
        if(parent->pointers[i] == node_with_key){
            node_with_key_index = i;
        }
    }
    std::cout << "Правый брат вот " << parent->pointers[node_with_key_index + 1] << std::endl;


    //обратимся к левому брату
    if (node_with_key_index > 0){
        int left_brother_key_amount = parent->pointers[node_with_key_index - 1]->count_keys(B_factor);
        if (/*parent->pointers[node_with_key_index - 1]->count_keys(B_factor)*/left_brother_key_amount > 1){
            std::cout << "Левый брат" << std::endl;
            //возьмем отсюда крайний ключ правый и отправим родителю в резерв
            parent->TEMP_KEY = parent->pointers[node_with_key_index - 1]->keys[left_brother_key_amount - 1];
            std::cout << "Ключ отправили родителю"<< parent->pointers[node_with_key_index - 1]->keys[left_brother_key_amount - 1] << std::endl;
            std::cout << "Число ключей левого братат "<< left_brother_key_amount << std::endl;
            parent->pointers[node_with_key_index - 1]->keys[left_brother_key_amount - 1] = -1;

            node_with_key->TEMP_KEY = parent->keys[node_with_key_index - 1];
            parent->keys[node_with_key_index - 1] = -1;
            parent->remove_free_place(B_factor);
            parent->refresh(B_factor, root, nullptr);

            node_with_key->refresh(B_factor,root,parent);
            node_with_key->del_key_only_this(key,B_factor,node_with_key); //закоментим, потому что перекинем проблему
            return 1;
        }
    }
    //обратимся к правому брату

    if (parent->pointers[node_with_key_index + 1] != nullptr){ //обратимся к правому брату
        std::cout << "Правый брат??" << std::endl;
        if (parent->pointers[node_with_key_index + 1]->count_keys(B_factor) > 1) {
            std::cout << "Правый брат!" << std::endl;
            int right_brother_key_amount = parent->pointers[node_with_key_index + 1]->count_keys(B_factor);

            //возьмем отсюда крайний ключ левый и отправим к родителю в резерв
            parent->TEMP_KEY = parent->pointers[node_with_key_index + 1]->keys[0];
            parent->pointers[node_with_key_index + 1]->keys[0] = -1; //вместо него -1
            parent->pointers[node_with_key_index + 1]->remove_free_place(B_factor); //уберем пробел
            parent->refresh(B_factor,root, nullptr);


            node_with_key->TEMP_KEY = parent->keys[node_with_key_index];
            parent->keys[node_with_key_index] = -1;
            parent->remove_free_place(B_factor);
            parent->refresh(B_factor,root, nullptr);

            node_with_key->refresh(B_factor,root,parent);
            node_with_key->del_key_only_this(key,B_factor,node_with_key); //закоментим потому что перекинем проблему
        } else {
            //братья бомжи
            std::cout << "Братья без ключей ( по одному)" << std::endl;
            return 0;
        }
    } else {
        //братья бомжи
        std::cout << "Братья без ключей (по одному)" << std::endl;
        return 0;
    }

}

int BTree::Node::merge_nodes_brothers(int key, int B_factor, Node* node_with_key, Node* parent, Node* root, int parent_status) {

    if (1) {
        //тут уже  мы знаем что братьев можно сливать
        std::cout << "Скрещиваем братьев без ключей!" << std::endl;
        std::cout << this << std::endl;
        this->print_only_this(B_factor,root,parent);
        int node_with_key_index = -1;

        //узнаем каким по порядку идет наш узел
        for (int i = 0; i < B_factor; i++) {
            if (parent->pointers[i] == node_with_key) {
                node_with_key_index = i;
            }
        }

        //cначала проверям левого брата, потом правого
        if (node_with_key_index > 0) {
            std::cout << "Попытка с левым!" << std::endl;
            int left_brother_key_amount = parent->pointers[node_with_key_index - 1]->count_keys(B_factor);
            if (1) {
                //будем скрещивать с левым
                node_with_key->del_key_only_this(key, B_factor, node_with_key); //удалили ключ

                parent->pointers[node_with_key_index] = nullptr; //удалили указатель

                parent->pointers[node_with_key_index - 1]->TEMP_KEY = parent->keys[node_with_key_index -1]; //левому брату скидываем ключ от родител

                if (parent_status == PARENT_HAS_MORE_KEYS) { //удаляем ключ если сверху много
                    parent->keys[node_with_key_index - 1] = -1;
                }

                key = parent->keys[node_with_key_index - 1];
                std::cout << "Отныне ключ равен " << key << std::endl;


                parent->pointers[node_with_key_index - 1]->refresh(B_factor, root, parent);
                parent->remove_free_place(B_factor);
                parent->remove_free_pointer(B_factor);
                std::cout << "????????!" << std::endl;
                DEBUG_TREE

                if (parent_status == PARENT_HAS_ONE_KEY){ //перекидываем проблему
                    std::cout << "????????!" << std::endl;
                    parent->delete_key(parent->keys[node_with_key_index - 1],B_factor,root, parent->find_this_parent(B_factor,root,root),parent,USED);
                }
                else if (parent_status == PARENT_ROOT_HAS_ONE){
                    change_root(parent->pointers[0], root, B_factor);
                    //root = parent->pointers[0];
                }
                return key;

            }
        }
        std::cout << "ПРодолжаем!" << std::endl;


        if (parent->pointers[node_with_key_index + 1] != nullptr) { //обратимся к правому брату
            std::cout << "Правый брат??" << std::endl;
            if (1) {
                std::cout << "Правый брат!" << std::endl;
                node_with_key->del_key_only_this(key, B_factor, node_with_key); //удалили ключ

                parent->pointers[node_with_key_index] = nullptr; //удалили указатель

                parent->pointers[node_with_key_index + 1]->TEMP_KEY = parent->keys[node_with_key_index]; //правому брату скидываем ключ от родител

                if (parent_status == PARENT_HAS_MORE_KEYS) {
                    parent->keys[node_with_key_index] = -1;
                }


                parent->pointers[node_with_key_index + 1]->refresh(B_factor, root, parent);
                parent->remove_free_place(B_factor);
                parent->remove_free_pointer(B_factor);

                if (parent_status == PARENT_HAS_ONE_KEY){
                    std::cout << "Рекурсия" << std::endl;
                    parent->delete_key(parent->keys[node_with_key_index],B_factor,root, parent->find_this_parent(B_factor,root,root),parent,USED);
                }

                else if (parent_status == PARENT_ROOT_HAS_ONE){
                    change_root(parent->pointers[0], root, B_factor);
                    //root = parent->pointers[0];
                }


                return key;

                //int right_brother_key_amount = parent->pointers[node_with_key_index + 1]->count_keys(B_factor);

                //будем скрещивать с правым
            }
        }
    }
}





int BTree::Node::lift_up_left (int key, int B_factor, Node * root, Node * parent, Node * node_with_key, int key_index) {
    std::cout << "мы в левом подьемем!"<< std::endl;

    if (this == node_with_key){
        std::cout << " Этот узел:  "<< this << "идем по индексу" << key_index << std::endl;
        return this->pointers[key_index]->lift_up_left(key,B_factor,root,this,node_with_key,key_index);

    } else if(this->pointers[0] != nullptr){ //отправляем вниз
        std::cout << " Этот узел:  "<< this << std::endl;
       return this->pointers[this->count_pointers(B_factor) - 1]->lift_up_left(key,B_factor,root,this,node_with_key,key_index);
   } else {
       std::cout << "дошли до нижнего, проверка!"<< std::endl;
        std::cout << " Этот узел:  "<< this << std::endl;
       if (this->count_keys(B_factor) > 1) {
           std::cout << "передаем наверх!"<< this->keys[this->count_keys(B_factor) - 1] << "адрес узла" << this << std::endl;
           node_with_key->TEMP_KEY = this->keys[this->count_keys(B_factor) - 1];
           this->keys[this->count_keys(B_factor) - 1] = -1;
           node_with_key->refresh(B_factor, root, nullptr);
           return 1;
       } else {
           return 0;
       }
   }
}

int BTree::Node::lift_up_right (int key, int B_factor, Node * root, Node * parent, Node * node_with_key, int key_index) {
    if (this == node_with_key) {
        std::cout << "это узел с ключем!"<< std::endl;
        std::cout << " Этот узел:  "<< this << std::endl;
        return this->pointers[key_index +1]->lift_up_right(key, B_factor, root, this, node_with_key, key_index);

    } else if(this->pointers[0] != nullptr){ //отправляем вниз
        std::cout << " Этот узел::  "<< this << std::endl;
        return this->pointers[0]->lift_up_right(key,B_factor,root,this,node_with_key,key_index);
    } else {
        std::cout << " будет проверка  "<< this << std::endl;
        if (this->count_keys(B_factor) > 1) {
            node_with_key->TEMP_KEY = this->keys[0];
            std::cout << "вверх отдаем этот!" << this->keys[0]<< std::endl;
            this->keys[0] = -1;
            this->remove_free_place(B_factor);
            //this->refresh(B_factor,root, nullptr);
            node_with_key->refresh(B_factor, root, nullptr);
            return 1;
        } else {
            return 0;
        }
    }
}

void BTree::Node::steal_down_key(int key, int B_factor, Node* node_with_key, Node* parent, Node* root, int key_index){
    /*
    std::cout << " ТОЛЬКО ЗАШЛИ В ФУНКЦЮ" << key_index << std::endl;
    std::cout << " Этот узел:  "<< this << "идем по индексу" << key_index << std::endl;
    std::cout << " Узел с ключом:  "<< node_with_key << " ***" << key_index << std::endl;
     */
    //Node * safe_node_with_key = node_with_key;

    if (this == node_with_key){
        /*
         * std::cout << " Этот узел:  "<< this << "идем по индексу" << key_index << std::endl;*/

        std::cout << " Узел с ключом:  "<< node_with_key << " (тут нормальный адрес)" << std::endl;
        std::cout << " Это че за адрес:  "<< this->pointers[key_index] << " ????" << std::endl;

        //this->pointers[key_index]->steal_down_key(key,B_factor,root,this, node_with_key,key_index);
        this->pointers[key_index]->steal_down_key(key,B_factor,node_with_key,this,root,key_index);

    } else if(this->pointers[0] != nullptr){ //отправляем вниз
        /*
         std::cout << " Этот узел:  "<< this << std::endl;

        std::cout << " Узел с ключом:  "<< node_with_key << " (уже другой мать его)" << std::endl;
         */

        this->pointers[this->count_pointers(B_factor) - 1]->steal_down_key(key,B_factor,node_with_key,this,root,key_index);
    } else {
        std::cout << "дошли до нижнего, проверка!"<< std::endl;
        /*std::cout << " Этот узел:  "<< this << "(уже другой мать его) "<< std::endl;
         */
        std::cout << " Узел с ключом:  "<< node_with_key << " (уже другой мать его)" << key_index << std::endl;

        if (1) {
            //std::cout << "передаем наверх!"<< this->keys[this->count_keys(B_factor) - 1] << "адрес узла" << this << std::endl;
            node_with_key->TEMP_KEY = this->keys[this->count_keys(B_factor) - 1];
            //this->keys[this->count_keys(B_factor) - 1] = -1; //НЕ БУДЕМ ОБНУЛЯТЬ КЛЮЧ, ЧТОБЫ НАЙТИ РОДИТЕЛЯ
            key = this->keys[this->count_keys(B_factor) - 1];
            std::cout << "КЛЮЧ КЛЮЧ КЛЮЧ  !  "<< this->keys[this->count_keys(B_factor) - 1] << std::endl;

            node_with_key->refresh(B_factor, root, nullptr);
            std::cout << "ЭТОТ УЗЕЛ ПОСЛЕ ТОГО КАК МЫ ЗАБАРАЛИ КЛЮЧ СНИЗУ!"<< std::endl;
            node_with_key->print_only_this(B_factor,root,parent);
        }

        //теперь перекидываем роблему ??? главное чтобы он не удалил ключ повторно
        std::cout << "Перекидываем проблему! Наш узел с чужим ключом"<< std::endl;
        node_with_key->print_only_this(B_factor,root,parent);

        std::cout << "отсюда взяли ключ"<< std::endl;
        this->print_only_this(B_factor,root,parent);



        this->delete_key(key, B_factor, root, this->find_this_parent(B_factor,root,root), this, USED);





    }
    std::cout << " Конец функции" << key_index << std::endl;
    //std::cout << " Этот узел:  "<< this << "идем по индексу" << key_index << std::endl;
    //std::cout << " Узел с ключом:  "<< node_with_key << " ***" << key_index << std::endl;



}



int BTree::Node::ask_brother_key_with_pointers(int key, int B_factor, Node* node_with_key, Node* parent, Node* root){
    //найдем индекс нашего узла сверху
    std::cout << "Функция ask_brother_key_with_pointers" << std::endl;
    std::cout << "Этот узел" << this << std::endl;
    this->print_only_this(B_factor,root,parent);

    std::cout << "Родитель нашаго узла" << this << std::endl;
    parent->print_only_this(B_factor,root,parent);




    int node_index = -1;
    for (int i = 0; i < B_factor; i++){
        if(parent->pointers[i] == this){
            node_index = i;
        }
    }

    std::cout << "Индекс узла у родителя" << node_index << std::endl;


    if (node_index > 0) {//спрашиваем левого брата

        std::cout << "Спросим у левого" << std::endl;

        int left_brother_key_amount = parent->pointers[node_index - 1]->count_keys(B_factor);
        Node* left_brother = parent->pointers[node_index - 1];
        if (left_brother_key_amount > 1){

            std::cout << "У левого Есть! берем" << std::endl;
            //берем ключ у левого
            //parent->pointers[node_index - 1]


            //возьмем отсюда крайний ключ правый и отправим родителю в резерв
            parent->TEMP_KEY = left_brother->keys[left_brother_key_amount - 1];
            //std::cout << "Ключ отправили родителю"<< parent->pointers[node_with_key_index - 1]->keys[left_brother_key_amount - 1] << std::endl;
            //std::cout << "Число ключей левого братат "<< left_brother_key_amount << std::endl;
            left_brother->keys[left_brother_key_amount - 1] = -1;

            this->TEMP_KEY = parent->keys[node_index - 1];
            parent->keys[node_index - 1] = -1;
            parent->remove_free_place(B_factor);
            parent->refresh(B_factor, root, nullptr);

            this->TEMP_POINTER = left_brother->pointers[left_brother_key_amount];
            left_brother->pointers[left_brother_key_amount] = nullptr;


            this->refresh(B_factor,root,parent);
            this->del_key_only_this(key,B_factor,node_with_key); //даже если  ключа у нас нет, она все равно не должна удалять
            return 1;





        }

    }

    std::cout << "Продолжаем" << std::endl;

    if (parent->pointers[node_index + 1] != nullptr) { //спрашиваем правого брата
        std::cout << "Спросим у правого" << std::endl;
        int right_brother_key_amount = parent->pointers[node_index + 1]->count_keys(B_factor);
        Node* right_brother = parent->pointers[node_index + 1];
        if (right_brother_key_amount > 1){

            std::cout << "У правого есть! берем" << std::endl;
            //берем ключ у правого

            this->del_key_only_this(key,B_factor,node_with_key);
            this->TEMP_KEY = parent->keys[0];

            parent->keys[0] = -1;
            parent->remove_free_place(B_factor);
            parent->TEMP_KEY = right_brother->keys[0];
            right_brother->keys[0] = -1;

            parent->refresh(B_factor, root, nullptr);

            this->TEMP_POINTER = right_brother->pointers[0];

            right_brother->pointers[0] = nullptr;
            right_brother->remove_free_place(B_factor);
            right_brother->remove_free_pointer(B_factor);

            this->refresh(B_factor,root,parent);          //ЭТОТ ОТСОРТИРОВАЛИ





//??????

            //parent->remove_free_place(key,B_factor,node_with_key);
            //parent->refresh(B_factor, root, nullptr);

            //this->TEMP_POINTER = right_brother->pointers[0];
            //right_brother->pointers[0] = nullptr;
            //right_brother->remove_free_place(key,B_factor,node_with_key);
            //right_brother->remove_free_pointer(B_factor)


            //this->refresh(B_factor,root,parent);
            //this->del_key_only_this(key,B_factor,node_with_key); //даже если  ключа у нас нет, она все равно не должна удалять


            //дальше ок
            //right_brother->remove_free_place(key,B_factor,node_with_key);
            //right_brother->remove_free_pointer(B_factor);

            return 1;









        }

    }
    return 0;

}


void BTree::Node::change_root(Node* new_root, Node* root, int B_factor){
    //передаем ключи
    for (int i = 0; i < B_factor -1; i++){
        root->keys[i] = new_root->keys[i];
    }

    //передаем указатели
    for (int i = 0; i < B_factor; i++){
        root->pointers[i] = new_root->pointers[i];
    }
}











void BTree::Node::merge_nodes_brothers_with_pointers(int key, int B_factor, Node* node_with_key, Node* parent, Node* root, int parent_status){
    std::cout << "Скрещиваем братьев c ключами!" << std::endl;
    int node_with_key_index = -1;

    //узнаем каким по порядку идет наш узел
    for (int i = 0; i < B_factor; i++) {
        if (parent->pointers[i] == node_with_key) {
            node_with_key_index = i;
        }
    }

    std::cout << "Нашли индекс узла!  " << node_with_key_index << std::endl;


    if (node_with_key_index > 0) { //работаем с левым
        std::cout << "Работаем с левым братом!  " << std::endl;
        Node* left_brother = parent->pointers[node_with_key_index -1];

        this->del_key_only_this(key,B_factor,node_with_key);
        this->TEMP_KEY = parent->keys[node_with_key_index - 1];
        this->refresh(B_factor,root,parent);

        //std::cout << "Живо1!  " << std::endl;

        if (parent_status == PARENT_HAS_MORE_KEYS) {
            parent->keys[node_with_key_index - 1] = -1;
            parent->remove_free_place(B_factor);
        }

        //std::cout << "Живо2!  " << std::endl;

        std::cout << left_brother << std::endl;

        this->TEMP_KEY = left_brother->keys[0];
        //std::cout << "чек1!  " << std::endl;
        this->TEMP_POINTER = left_brother->pointers[0];
        //std::cout << "чек 2!  " << std::endl;
        this->refresh(B_factor,root,parent);
        //std::cout << "чек 3!  " << std::endl;
        this->TEMP_POINTER = left_brother->pointers[1];
        //std::cout << "чек 4 3!  " << std::endl;
        this->refresh(B_factor,root,parent);

        //std::cout << "Живо 3!  " << std::endl;


        parent->pointers[node_with_key_index - 1] = nullptr;
        parent->remove_free_pointer(B_factor);

        //в конце
        key = parent->keys[0];

        if (parent_status == PARENT_HAS_ONE_KEY){
            parent->delete_key(parent->keys[node_with_key_index],B_factor,root, parent->find_this_parent(B_factor,root,root),parent,USED);
        }

        else if (parent_status == PARENT_ROOT_HAS_ONE){
            std::cout << "ИЗМЕНЯЕМ КОРЕНЬ!  " << std::endl;
            std::cout << "КОрень до изменений ! " << root << std::endl;
            std::cout << "Меняем на ! " << parent->pointers[0] << std::endl;
            change_root(parent->pointers[0], root, B_factor);
            //root = parent->pointers[0];
            std::cout << "КОрень после изменений " << parent->pointers[0] << std::endl;


        }

        return;


    }






    if (parent->pointers[node_with_key_index + 1] != nullptr) { //обратимся к правому брату
        std::cout << "Работаем с правым братом!  " << std::endl;
        Node* right_brother = parent->pointers[node_with_key_index + 1];

        this->del_key_only_this(key,B_factor,node_with_key);
        this->TEMP_KEY = parent->keys[node_with_key_index];
        this->refresh(B_factor,root,parent);

        if (parent_status == PARENT_HAS_MORE_KEYS) {
            parent->keys[node_with_key_index] = -1;
            parent->remove_free_place(B_factor);
        }


        this->TEMP_KEY = right_brother->keys[0];
        this->TEMP_POINTER = right_brother->pointers[0];
        this->refresh(B_factor,root,parent);
        this->TEMP_POINTER = right_brother->pointers[1];
        this->refresh(B_factor,root,parent);

        parent->pointers[node_with_key_index + 1] = nullptr;
        parent->remove_free_pointer(B_factor);

        //в конце
        key = parent->keys[0];

        if (parent_status == PARENT_HAS_ONE_KEY){
            parent->delete_key(parent->keys[node_with_key_index],B_factor,root, parent->find_this_parent(B_factor,root,root),parent,USED);
        }

        else if (parent_status == PARENT_ROOT_HAS_ONE){
            //root = parent->pointers[0];
            change_root(parent->pointers[0], root, B_factor);
        }


        return;

    }
}











void BTree::delete_key(int key){
    std::cout << "Функция: Удаление ключа (для дерева)!++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++=" << std::endl;
    Node* node_with_key = root->search(key, 0, B_factor, root, root, nullptr);
    if (node_with_key == nullptr){
        std::cout << "НЕТ ТАКОГО КЛЮЧАААААААААА!" << std::endl;
        return;
    }
    std::cout << "УЗЕЛ с ключом!!!"<< std::endl;
    //node_with_key->print_only_this(B_factor,root, nullptr);
    /*root было*/node_with_key->delete_key(key, B_factor, root, node_with_key->find_this_parent(B_factor,root,root), node_with_key, NOT_USED);
}

void BTree::Node::delete_key(int key, int B_factor, Node * root, Node * parent, Node * node_with_key, int is_used){
    std::cout << "Функция: Удаление ключа для node_with_key! ==========================================================================================" << std::endl;
    std::cout << "ДЕРЕВО ПЕРЕД УДАЛЕНИЕМ КЛЮЧА"<< std::endl;
    root->print(B_factor, nullptr, nullptr);
    std::cout << "ЭТОТ УЗЕЛ в котором мы " << this << "  Удаляем ключ  "<< key << std::endl;

    int success = 0;  // 1 означает что успешно
    std::cout << "Удаление ключа"<< std::endl;
    //найдем адрес узла с ключем, проверим есть ли такой ключ
    if (node_with_key == nullptr){
        std::cout << "НЕТ ТАКОГО КЛЮЧАААААААААА!" << std::endl;
        return;
    }
    //работа в листьях
    if (node_with_key->pointers[0] == nullptr) { // если нет детей
        std::cout << "Мы в листьях!" << std::endl;

        if (node_with_key->count_keys(B_factor) > 1) { //если больше 2 ключей и нет детей
            node_with_key->del_key_only_this(key, B_factor, node_with_key);
            return;
        }

        else if (node_with_key->count_keys(B_factor) == 1){ //остался один ключ, спросим у братьев соседей
            std::cout << "Спросим ключ у брата!" << std::endl;
            success = success + ask_brother_key(key,B_factor,node_with_key,parent,root);
            if (/*is_used == NOT_USED*/1){ //если это первый заход, то надо удалить ключ. удаляем ключ в любом случае
                //node_with_key->del_key_only_this(key,B_factor,node_with_key);
            }
        }

        if ((success) == 0 /*&& (parent->count_keys(B_factor) > 1)*/){
            std::cout << "Будем объединять братьев без детей!" << std::endl;
            //объеденимся с братом, даже если у родителя всего один ключ


            if (parent->count_keys(B_factor) > 1) {
                node_with_key->merge_nodes_brothers(key, B_factor, node_with_key, parent, root, PARENT_HAS_MORE_KEYS); // У нас тут КЛЮЧ УДАЛИЛСЯ У РОДИТЕЛЯ
                std::cout << "Контроль!" << std::endl;

                DEBUG_TREE
                std::cout << "Контроль КЛЮЧ!" << key << std::endl;
                //parent->delete_key(key, B_factor, root, parent->find_this_parent(B_factor, root, root), parent, USED);
            } else if (parent == root) {
                node_with_key->merge_nodes_brothers(key, B_factor, node_with_key, parent, root, PARENT_ROOT_HAS_ONE);


            }else if (parent->count_keys(B_factor) == 1) { //у родителей СЕЙЧАС КОНЧАТСЯ КЛЮЧИ
                node_with_key->merge_nodes_brothers(key, B_factor, node_with_key, parent, root, PARENT_HAS_ONE_KEY);

            }



            /*

            if(parent->count_keys(B_factor) == 1){
                //надо добыть родителю один ключ
                std::cout << "АААААААААА!" << std::endl;
                //merge_parents
                //найдем ключ у братьев родителя
                parent->take_key_brother_with_pointers(key,B_factor,node_with_key,parent->find_this_parent(B_factor,root,root),root);

                //если не получится, то тогда сливаем родиетелй, но мы воруем ключ сверху, надо чтобы сверху было больше 1
                //merge_nodes_brothers_with_pointers(key,B_factor,node_with_key,parent,root);
            }

             */


            //объединение узла


        }




    } else {
        std::cout << "Мы в ветке!" << std::endl;

        int key_index = -1;
        for(int i = 0; i < B_factor - 1; i++){
            if(node_with_key->keys[i] == key){
                key_index = i;
            }
        }



        if (is_used == NOT_USED) { //идем вниз воровать ключи
            std::cout << "Идем вниз брать лишний ключи!" << std::endl;
            //идем в вниз до узлов без детей и если возможно берем крайние ключи



            del_key_only_this(key,B_factor,node_with_key); //удалим ключ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

            success = node_with_key->lift_up_left(key,B_factor,root,parent,node_with_key, key_index);
            std::cout << "Резльтат взятия левого!" << success << std::endl;
            if (success == 0){
                std::cout << "идем брать правый!" << std::endl;
                success = node_with_key->lift_up_right(key,B_factor,root,parent,node_with_key, key_index);
            }
            if (success == 1){
                return;
            }
            std::cout << "Результат взятие правого!"<< success << std::endl;
            //если success  будет равен 0, то нужно что-то другое делать

            //node_with_key->lift_up(key,B_factor,root,parent,node_with_key);

        }
        if ((is_used == NOT_USED) && (success == 0)) { //если не удалось забрать ключи, забираем силой
            //украсть ключ снизу
            std::cout << "Будем просто отбирать ключи силой!"<< success << std::endl;


            node_with_key->print_only_this(B_factor,root,parent);

            node_with_key->steal_down_key(key,B_factor,node_with_key,parent,root,key_index);
            return;


            //после того как забрали силой нужно ДЕЛЕГИРОВАТЬ ОТСУТСТВИЕ КЛЮЧА В САМЫЙ НИЗ
        }
        if (1){ //будем брать ключ у братьев с детьми (если у них есть больше 1)
            success = success + node_with_key->ask_brother_key_with_pointers(key,B_factor,node_with_key,parent,root);
            std::cout << "Попытка взять у братьев ключей РЕЗУЛЬТАТ  " << success << std::endl;
            if (success == 1) {
                return;
            }

        }




        //ВСЕ ЧТО НИЖЕ ЧЕРНОВИК

        if (parent->count_keys(B_factor) > 1) {

            node_with_key->merge_nodes_brothers_with_pointers(key,B_factor,node_with_key,parent,root,PARENT_HAS_MORE_KEYS);
            //node_with_key->merge_nodes_brothers(key, B_factor, node_with_key, parent, root, PARENT_HAS_MORE_KEYS); // У нас тут КЛЮЧ УДАЛИЛСЯ У РОДИТЕЛЯ
            std::cout << "Контроль!" << std::endl;

            DEBUG_TREE
            std::cout << "Контроль КЛЮЧ!" << key << std::endl;
            //parent->delete_key(key, B_factor, root, parent->find_this_parent(B_factor, root, root), parent, USED);
        } else if (parent == root) {
            node_with_key->merge_nodes_brothers_with_pointers(key,B_factor,node_with_key,parent,root,PARENT_ROOT_HAS_ONE);
            //node_with_key->merge_nodes_brothers(key, B_factor, node_with_key, parent, root, PARENT_ROOT_HAS_ONE);


        }else if (parent->count_keys(B_factor) == 1) { //у родителей СЕЙЧАС КОНЧАТСЯ КЛЮЧИ
            node_with_key->merge_nodes_brothers_with_pointers(key,B_factor,node_with_key,parent,root,PARENT_HAS_ONE_KEY);
            //node_with_key->merge_nodes_brothers(key, B_factor, node_with_key, parent, root, PARENT_HAS_ONE_KEY);

        }





        if (1){ //скреститься с братом

            //ВАРИАНТЫ
            //сверху больше 1
            //сверху 1
            //сверху 1 и это корень

        }













            // если не удалось найти ключ снизу
            //пытаемся слить детей данного узла (но для этого должно быть больше 1)

         if (1/*?????*/){ //если не смогли, то берем один ключ и ссылку у брата (взять ключ с сосед ветки)


        }else if (1) { //если не смогли, то сливаемся с веткой братом (это надо рекурсивно)


        }





    }
    //std::cout << node_with_key->count_keys(B_factor) << std::endl;
    //std::cout << node_with_key->count_pointers(B_factor) << std::endl;


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

