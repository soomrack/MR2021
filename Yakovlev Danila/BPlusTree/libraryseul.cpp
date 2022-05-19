
// Created by Мотылек on 13.05.2022.
//
/*нумерация в узле
 * ключи
 * 0(MIN) 1 2 3 4 .... n
 * ссылки
 * 0 1 2 3 4 ... n
*/

#include "libraryseul.h"

Node::Node(int data_leaf_or_bfactor,bool leaf_or_node) {
    if (leaf_or_node) {
        key_data = data_leaf_or_bfactor;
        neighbour = nullptr;
    }
    else {
        size_array = data_leaf_or_bfactor+1;
        max_ref_child_id = -1;
        key_copy = new int[size_array];
        child_array.resize(size_array, nullptr);
        key_copy[0] = MIN;
        for (int i = 1; i < size_array; i++) {
            key_copy[i] = MAX;
        }
    }
    leaf = leaf_or_node;
}
Node::Node(const Node &node){
    this-> size_array = node.size_array;
    if (leaf) {
        this-> key_data = node.key_data;
        this-> neighbour = node.neighbour;
    }
    else {
        this-> max_ref_child_id = node.max_ref_child_id;
        key_copy = new int[size_array];
        child_array.reserve(node.child_array.size());
        memcpy(key_copy, node.key_copy,sizeof(int)*(size_array));
        memcpy(&child_array.at(0), &node.child_array.at(0), node.child_array.size());
    }
    this-> leaf = node.leaf;
}
Node::Node(Node &&node) noexcept {
    size_array = node.size_array;
    leaf = node.leaf;
    node.size_array = false;
    node.leaf = false;
    if (leaf) {
        key_data = node.key_data;
        neighbour = node.neighbour;
        node.key_data = 0;
        node.neighbour = nullptr;
    }
    else {
        key_copy = node.key_copy;
        child_array = node.child_array;
        max_ref_child_id = node.max_ref_child_id;
        node.key_copy = nullptr;
        node.child_array.clear();
        node.max_ref_child_id = 0;
    }
}
Node::~Node() {
    ///____когда то все в этом деструкторе было закоменнченым и все работало. будет ли работать иначе____///
    if (leaf) {
        key_data = 0;
        neighbour = nullptr;
    }
    else {
        delete key_copy ;
        child_array.clear();
        max_ref_child_id = 0;
    }
}

BPTree::BPTree(int b_factor) {
    H = 0;
    Hplus = false;
    this -> b_factor = b_factor-1;
    root = new Node(b_factor,false);
}
BPTree::~BPTree() {
    int ooo = 0;
    //удаление всех листьев и узлов рекурсией
}

//готово
bool BPTree::search(int leaf){
    if (H==0) if (root->child_array[0] == nullptr) return false;//единственный случай пустоты - ни один лист не создан
    return search(leaf, root, 0);
}
bool BPTree::search(int leaf,Node* ref_node, int floor) {
    if (floor < H){//до предлистового узла поднимаемся
        int i = 1; //проход по текущему узлу сравнивая ключи
        while ((i <= ref_node->max_ref_child_id) and (leaf > ref_node->key_copy[i])) i++;
        if(leaf == ref_node->key_copy[i]) return true;
        return search(leaf, ref_node->child_array[i-1], floor+1);//переход к следующему узлу рекурсией
    }
    else {//мы в листе
        if(leaf == ref_node->key_data) return true;
    }
    return false;
};

//работает все до поры разделения. корень то конечно делится, а вот дальше...
void* BPTree::add(int leaf) {
    Hplus = false;
    //cout << endl<<"_____ Добавление " << leaf << endl;
///0. отработка исключения
    if (root->max_ref_child_id == -1){      // если нет ни одного еще листа
        root->child_array[0] = new Node(leaf,true);
        root->max_ref_child_id++;
        H++;
        cout <<"Добавили первый лист номиналом " << leaf <<  " успешно_____" << endl<< endl;//***********************************
        return nullptr;
    }
    //cout << "Поиск последнего узла в который добавим лист"<< endl;
/// 1. поиск последнего узла, в который добавим лист
    ptr_path_array = new Node*[H];
    ptr_path_array[0] = root;
    int floors_for_separation = search_place_for_add(leaf, root, 0, 0);//сколько ярусов нужно разделить пополам по пути добавления листа
    int i_new_leaf = 0;//место нового листа
    while ((i_new_leaf <= ptr_path_array[H-1]->max_ref_child_id)and(leaf > ptr_path_array[H-1]->child_array[i_new_leaf]->key_data)){
        i_new_leaf++;//двигаемся вправо пока не достигнем места куда вставим наш лист
    }
    if (i_new_leaf <= ptr_path_array[H-1]->max_ref_child_id){
        if(ptr_path_array[H-1]->child_array[i_new_leaf]->key_data == leaf){
            cout << "такой лист уже существует = " << leaf << endl;
            delete ptr_path_array;
            return nullptr;
        }
    }

    //cout << "Поиск закончен. Теперь подготовка дерева к добавлению"<< endl;
    /// 2. подготовить дерево к добавлению узла
    while(floors_for_separation > 0){                  //если предлистовой узел переполнен и далее в сторону корня
        //cout << "Этажей для разделения = " << floors_for_separation << endl;
        if (H == floors_for_separation){            //разделение корня, если надо
            //1. Создаем новый корень
            Hplus = true;
            newroot = new Node(b_factor, false);
            newroot->child_array[0] = root;
            newroot->max_ref_child_id++;
            //3. разделяем значения
            node_separation(root,newroot, 0, leaf);
            root = newroot;
            newroot = nullptr;
            floors_for_separation--;
        }
        else{
            node_separation(ptr_path_array[H-floors_for_separation], ptr_path_array[H-floors_for_separation-1], H-floors_for_separation, leaf);
            floors_for_separation--;
        }
    }
    //cout << "С подготовкой дерева закончили. Переходим к заполнению предлистового узла"<< endl;
///3. подготовка предлистового узла и добавление листа (можно завернуть в отдельную функцию)
    Node *here = ptr_path_array[H-1];
    int i = here->max_ref_child_id + 1;
    while (i > i_new_leaf) {// тут смещение ссылок и копий на 1 вправо до места добавления листа
        here->key_copy[i] = here->key_copy[i-1];
        here->child_array[i] = here->child_array[i-1];
        i--;
    }
    //cout << "Заполнение предлистового листа успешно. Наверное. Теперь добавление листа"<< endl;
    if (leaf < here->child_array[0]->key_data) {                      //если новый лист меньше нулевого
        here->key_copy[1] = here->child_array[0]->key_data;
        here->child_array[1] = here->child_array[0];
        here->child_array[0] = new Node(leaf, true);
    }
    else {
        here -> child_array[i] = new Node(leaf, true);
        here -> key_copy[i] = leaf;
    }
    here -> max_ref_child_id++;
    if (Hplus) {H++; Hplus = false;}//если в процессе был создан новый корень, то высота увеличилась
    //cout << "И наконец поправим соседей.\n рассмотрим соседа слева:"<< endl;
///4. Поправляем ссылки на соседеей
    Node* left_node = search_neighbour_left(leaf, root, 0);
    if (left_node-> key_data < leaf) {
        //cout << "Сосед слева "<< left_node->key_data << endl;
        left_node->neighbour = here->child_array[i];//добавка предыдущему листу ссылку на текущий
    }
    //cout << "рассмотрим соседа справа:"<< endl;
    Node* right_node = search_neighbour_right(leaf, root, 0);
    if (right_node-> key_data > leaf){
        //cout << "Сосед справа "<< right_node->key_data << endl;
        here->child_array[i] -> neighbour = right_node;//добавка текущему листу ссылку на следующий
    }
    //cout << "Соседей поправили"<< endl;
    //cout <<" Добавление " << leaf <<  " успешно_____" << endl<< endl;//***********************************
    delete ptr_path_array;
    return nullptr;
}
int BPTree::search_place_for_add(int leaf, Node* &ref_node, int floor, int floors_for_separation){
    if (floor < H-1){//до предлистового узла поднимаемся
        int i = 0;  //счет идет по ссылкам
        while ((i <= ref_node->max_ref_child_id) and (leaf > ref_node->key_copy[i])) i++;
        if(leaf == ref_node->key_copy[i]) return -1;//такой лист уже есть
        if (ref_node->max_ref_child_id >= b_factor) floors_for_separation++;//нужно ли разделять узел
        else floors_for_separation = 0;
        floor++;
        ptr_path_array[floor] = ref_node->child_array[i-1];
        return search_place_for_add(leaf, ptr_path_array[floor], floor, floors_for_separation);
    }
    if (ref_node->max_ref_child_id >= b_factor) floors_for_separation++;
    else floors_for_separation = 0;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    cout<<"Заполненность: "<< ref_node->max_ref_child_id+1 <<" uз "<< b_factor+1 <<" Тут узлы:"<<endl;
    int i = 0;
    while (i <= ref_node->max_ref_child_id){
        cout << ref_node->child_array[i]->key_data <<" ";
        i++;
    }
    cout<<endl<<"Высота дерева "<<H<<" Тут этажей для разделения: ";
    cout<<floors_for_separation<<endl;
     */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    return floors_for_separation;
}
void* BPTree::node_separation(Node* &ref_node,Node* &ref_parent_node, int floor, int leaf){//узел для разделения, родительский узел, этаж детей (на котором будем разедлять), лист
    //cout<<"То самое разделение узла. На этаже:  "<< floor<<endl;
        ///1. подвинуть у родителя узлы для добавления
    int i_place_node = ref_parent_node-> max_ref_child_id;
    while ((i_place_node > 0) and (ref_parent_node -> child_array[i_place_node] != ref_node)){
        ref_parent_node->key_copy[i_place_node+1] = ref_parent_node->key_copy[i_place_node] ;
        ref_parent_node->child_array[i_place_node+1] = ref_parent_node->child_array[i_place_node];
        i_place_node--;
    } i_place_node++;
        ///2. создаем новый узел. он будет справа от переполненного.
    ref_parent_node->child_array[i_place_node] = new Node(b_factor, false);
    ref_parent_node->max_ref_child_id++;
    //cout<<"Заполненность узла родителя после добавления ему нового узла: "<<ref_parent_node->max_ref_child_id<<endl;
       ///3. непосредственно разделяем узлы
    int half = 1+b_factor/2;
    //cout<<"blyt1. половина = "<< half<<endl;//*************************************************************************
        //аккуратный перенос 0-1 позиций. а дальше в цикле
    ref_parent_node->child_array[i_place_node]->child_array[0] = ref_node->child_array[half];
    ref_parent_node->child_array[i_place_node]->child_array[1] = ref_node->child_array[half+1];
    if(floor == (H-1)){     //если мы на предлистовом узле
        //cout<<"предлистовой узел"<<endl;
        ref_parent_node->child_array[i_place_node]->key_copy[1] = ref_node->child_array[half+1]->key_data;
    }
    else{   //иначе мы выше
        ref_parent_node->child_array[i_place_node]->key_copy[1] = ref_node->key_copy[half];
    }
    //cout<<"blyt2. на 1 позиции ключ разделитель равен = "<< ref_parent_node->child_array[i_place_node]->key_copy[1] <<endl;
    ref_node->child_array[half] = nullptr;
    ref_node->child_array[half+1] = nullptr;
    ref_node->key_copy[half] = MAX;
    ref_node->key_copy[half+1] = MAX;
    //cout<<"blyt3. первые 0 и 1 места заполнены"<<endl;
    int k = 2;
    while (k < half){
        ref_parent_node->child_array[i_place_node]->child_array[k] = ref_node->child_array[half+k];//скопировали
        ref_parent_node->child_array[i_place_node]->key_copy[k] = ref_node->key_copy[half+k];
        ref_node->child_array[half+k] = nullptr;
        ref_node->key_copy[half+k] = MAX;
        k++;
    }
    //cout<<"blyt4. все узлы разделены"<<endl;
    int new_key_copy_parent = search_for_the_first_leaf_of_this_branch(ref_parent_node->child_array[i_place_node]->child_array[0], floor+1);
    //cout<<"blyt5. ключ разделитель для родительского узла найден = " << new_key_copy_parent << endl;
    ref_parent_node->key_copy[i_place_node] = new_key_copy_parent;
    ref_node -> max_ref_child_id = b_factor/2;
    ref_parent_node->child_array[i_place_node] -> max_ref_child_id = ref_node -> max_ref_child_id;
    //cout<<"blyt6. максимумы обновлены. у старого узла = "<< ref_node -> max_ref_child_id <<" у нового узла = "<<ref_parent_node->child_array[i_place_node] -> max_ref_child_id<<endl;
    /*
    cout<<"blyt6. А сами узлы выглядят так:"<<endl;
    cout<<"В родительском узле копии:"<<endl;
    int i = 0;
    while (i <= ref_parent_node->max_ref_child_id){
        cout << ref_parent_node->key_copy[i] <<" ";
        i++;
    }
    cout<<endl<<"В старом узле :"<<endl;
    i = 0;
    while (i <= ref_node->max_ref_child_id){
        cout << ref_node->key_copy[i] <<" ";
        i++;
    }
    cout<<endl<<"В новом узле копии:"<<endl;
    i = 0;
    while (i <= ref_parent_node->child_array[i_place_node]->max_ref_child_id){
        cout << ref_parent_node->child_array[i_place_node]->child_array[i]->key_data <<" ";
        i++;
    }
    cout<<endl<<"В новом узле листья:"<<endl;
    i = 0;
    while (i <= ref_parent_node->child_array[i_place_node]->max_ref_child_id){
        cout << ref_parent_node->child_array[i_place_node]->child_array[i]->key_data <<" ";
        i++;
    }
    */
    if(leaf > new_key_copy_parent)ptr_path_array[floor] = ref_parent_node->child_array[i_place_node];
    //cout<<endl<<"blyt. END END END .blyt"<<endl;
    return nullptr;
}
int BPTree::search_for_the_first_leaf_of_this_branch(Node* ref_node, int floor){//дохожу до листа, беру значение для разделения
    if(floor<H){
        floor++;
        return search_for_the_first_leaf_of_this_branch(ref_node->child_array[0],floor);
    }
    return ref_node->key_data;
}
Node* BPTree::search_neighbour_left(int leaf, Node* &ref_node, int floor){
    //cout <<"В поисках соседа слева на этаже "<< floor <<"из "<< H <<endl;
    if (floor < H-1){//до листа
        int i = 0;
        while ((i <= ref_node->max_ref_child_id) and (leaf > ref_node->key_copy[i])) i++;
        //cout <<"Сосед слева в узле = "<<ref_node->key_copy[i-1] <<endl;
        return search_neighbour_left(leaf, ref_node->child_array[i-1], floor+1);
    }
    int i = 0;
    while ((i <= ref_node->max_ref_child_id) and (leaf > ref_node->key_copy[i])) i++;
    //cout <<"Местонахождение соседа слева найдено = "<< ref_node->key_copy[i-1] <<endl;
    //cout <<"Сосед слева найден = "<< ref_node->child_array[i-1]->key_data <<endl;
    return ref_node->child_array[i-1];
}
Node* BPTree::search_neighbour_right(int leaf, Node* &ref_node, int floor){//идти справа налево тут надо
    //cout <<"В поисках соседа справа"<<endl;
    if (floor < H){
        int i = 0;
        while ((i < ref_node->max_ref_child_id) and (leaf >= ref_node->key_copy[i])) i++;
        floor++;
        return search_neighbour_right(leaf, ref_node->child_array[i], floor);
    }
    //cout <<"Сосед справа найден = "<<ref_node->key_data <<endl;
    return ref_node;
}

//готово
void BPTree::print(){
    cout << "B+ - tree:"<< endl;
    Node* once_leaf = search_once_leaf(root, 0);
    print_leaf(once_leaf);
}
Node* BPTree::search_once_leaf(Node* ref_node, int floor){//поиск первого листа
    if (floor < H){
        floor++;
        return search_once_leaf(ref_node->child_array[0], floor);
    }
    return ref_node;
}
Node* BPTree::print_leaf(Node* ref_leaf){//печать всех листов
    cout << ref_leaf->key_data << "  ";
    if (ref_leaf->neighbour == nullptr){
        cout << "Конец" << endl;
        return nullptr;
    }
    return print_leaf(ref_leaf->neighbour);
}


///пока без поправки дерева после удаления
void* BPTree::del(int leaf) {
    //cout <<"DELETE "<< leaf << endl;
/// 1. поиск последнего узла, в котором удалим лист
    ptr_path_array = new Node*[H];
    ptr_path_array[0] = root;
    int floors_for_combining = search_place_for_del(leaf, root, 0, 0);//сколько ярусов нужно разделить пополам по пути добавления листа
    Node *here = ptr_path_array[H-1];
    int i = 0;
    while ((i < here->max_ref_child_id) and (leaf > here->child_array[i]->key_data)) i++;
    if (ptr_path_array[H-1]->child_array[i]->key_data != leaf){
        //cout << "Листа " << leaf << " и так нет." << endl;//******************************************************
        delete ptr_path_array;
        return nullptr;
    }
///2. поправка соседей
    Node* left_node = search_neighbour_left(leaf, root, 0);
    Node* right_node = search_neighbour_right(leaf, root, 0);
    if ((left_node != here->child_array[i])and(right_node != here->child_array[i])){//если они существуют оба
        left_node -> neighbour = right_node;
        //cout <<" Соседей поправил" << endl;// *********
    }
///3. удаление и наведение порядка в листьях
    while (i < here->max_ref_child_id + 1) {// тут смещение ссылок и копий на 1 влево с места удаления листа (и так как раз его и удалим случайно). поэтому соседи раньше
        here->key_copy[i] = here->key_copy[i+1];
        here->child_array[i] = here->child_array[i+1];
        i++;
    }
    here -> max_ref_child_id--;

//4. А теперь настройка дерева. Объединение узлов ........................отсутствует
    //cout <<"DELETE " << leaf <<  " COMPLETED" << endl;//***********************************
    return nullptr;
}
int BPTree::search_place_for_del(int leaf, Node* &ref_node, int floor, int floors_for_combining){
    if (floor < H-1){
        int i = 0;
        while ((i < ref_node->max_ref_child_id) and (leaf >= ref_node->key_copy[i])) i++;
        floor++;
        if (ref_node->max_ref_child_id <= b_factor/2) floors_for_combining++;//нужно ли разделять узел
        else floors_for_combining = 0;
        if(leaf == ref_node->key_copy[i]) return search(leaf, ref_node->child_array[i], floor);
        return search(leaf, ref_node->child_array[i-1], floor);
    }
    if (ref_node->max_ref_child_id <= b_factor/2) floors_for_combining++;//нужно ли разделять узел
    else floors_for_combining = 0;
    return floors_for_combining;
}

