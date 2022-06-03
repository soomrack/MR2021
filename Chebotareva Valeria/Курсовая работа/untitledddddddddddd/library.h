#ifndef UNTITLEDDDDDDDDDDDD_LIBRARY_H
#define UNTITLEDDDDDDDDDDDD_LIBRARY_H
using namespace std;

class UF {
private:
    int *id;
    int cnt = 0;
    int *size;
public:
    //создание
    UF(int N);
//копирования
    UF(const UF &otherUF);
    //переноса
    UF( UF&& otherUF);
//удаление
    ~UF();

    int find(int p);

    void merge(int x, int y);

    bool connected(int x, int y);

    int count();
};

#endif //UNTITLEDDDDDDDDDDDD_LIBRARY_H
