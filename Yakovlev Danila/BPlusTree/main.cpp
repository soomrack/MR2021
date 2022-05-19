#include "libraryseul.h"
#include <windows.h>

#define hundred  100
#define thousand 1000
#define million  1000000
#define billion  1000000000
#define trillion 1000000000000

int main() {
    SetConsoleOutputCP(CP_UTF8);

    BPTree B(10);

    for (int i=0;i<thousand;i++){
        B.add(i);//+rand()%1000
        //B.print();
    }
    cout<< "Все"<<endl;
    B.print();
//    B.add(5);
//    B.print();
//    B.add(10);
//    B.print();
//    B.add(20);
//    B.print();
//    B.add(25);
//    B.print();
//
//    B.add(-25);
//    B.print();
//    B.add(-20);
//    B.print();
//    B.add(-15);
//    B.print();
//    B.add(-10);
//    B.print();
    B.add(534);
//    B.print();

//    B.del(0);
//    B.del(8);
//    B.print();
//
//    B.add(0);
//    B.print();
//    B.add(6);
//    B.print();
//
//    cout << "Есть ли в дереве 2 ::: " << B.search(2) << endl;
    cout << "Есть ли в дереве -4 ::: " << B.search(-4) << endl;
    cout << "Есть ли в дереве 900 ::: " << B.search(900) << endl;
    cout << "Есть ли в дереве 534 ::: " << B.search(534) << endl;
    cout << "Есть ли в дереве 0 ::: " << B.search(0) << endl;
    cout << "Есть ли в дереве MAX ::: " << B.search(MAX) << endl;
    cout << "Есть ли в дереве MIN ::: " << B.search(MIN) << endl;
    return 0;
}
