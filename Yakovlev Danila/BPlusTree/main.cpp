#include "libraryseul.h"
#include <windows.h>
#include <chrono>

#define hundred  100
#define thousand 1000
#define million  1000000
#define billion  1000000000

int main() {
    SetConsoleOutputCP(CP_UTF8);
    BPTree B(5);
    int i = 0;
    while (i < 1000){
       B.add(i);
       i++;
    }
    B.print();
    B.del(4);
    B.print();
//    auto begin = std::chrono::steady_clock::now();
//    B.search(0);
//    auto end = std::chrono::steady_clock::now();
//    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
//    std::cout << "The time: " << elapsed_ms.count() << " ns\n";

    //cout << B.search(0)<< endl;

    return 0;
}
