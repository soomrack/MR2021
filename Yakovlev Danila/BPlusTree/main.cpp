#include "libraryseul.h"
#include <windows.h>
#include <chrono>


int main() {
    SetConsoleOutputCP(CP_UTF8);
    BPTree B(10);
    int i = 0;
    while (i < 100){
       B.add(i);
       i++;
    }
    B.print();
    cout << "End" << endl;

    B.del(5);
    B.print();

//    auto begin = std::chrono::steady_clock::now();
//    auto end = std::chrono::steady_clock::now();
//    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
//    std::cout << "The time: " << elapsed_ms.count() << " ns\n";
    return 0;
}
