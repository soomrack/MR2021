#include "library.h"

//создание пустой структуры данных из N изолированных множеств
UF::UF(int N) {
    cnt = N;
    id = new int[N];
    size = new int[N];
    for (int i = 0; i < N; i++) {
        id[i] = i;
        size[i] = 1;
    }
}

//копирования
UF::UF(const UF &otherUF) {
    cnt = otherUF.cnt;
    id = new int[cnt];
    size = new int[cnt];
    for (int i = 0; i < cnt; i++) {
        id[i] = otherUF.id[i];
        size[i] = otherUF.size[i];
    }
}

//перемещения
UF:: UF( UF&& otherUF) {
    cnt = otherUF.cnt;
    id = new int[cnt];
    size = new int[cnt];
    for (int i = 0; i < cnt; i++) {
        id[i] = otherUF.id[i];
        size[i] = otherUF.size[i];
    }
    otherUF.~UF();
}

//удаление
UF::~UF() {
    delete[] id;
    delete[] size;
}

// Возвращение корня объекта р
int UF::find(int p) {
    int root = p;
    while (root != id[root])
        root = id[root];
    // "path compression"
    //делаем так, чтобы каждый элемент напрямую присоединялся к корню
    while (p != root) {
        int next = id[p];
        id[p] = root;
        p = next;
    }
    return root;
}

// Объединение множеств
void UF::merge(int x, int y) {
    //находим корни множеств
    int i = find(x);
    int j = find(y);

    //если х и у и так в одном множестве ничего не надо делать
    if (i == j) return;

    // присоединяем меньшее множество к большему
    //для корня меньшего, корнем становится корень большего
    if (size[i] < size[j]) {
        id[i] = j;
        size[j] += size[i];
    } else {
        id[j] = i;
        size[i] += size[j];
    }
    cnt--;
}

// Проверка находятся ли объекты х и у в одном множестве
bool UF::connected(int x, int y) {
    return find(x) == find(y);
}

// Возвращение количества множеств
int UF::count() {
    return cnt;
}