#include <iostream>
#include <ctime>
#include <chrono>
#define MAXSIZE 1000

using namespace std;

void Merge(int* A, int firstElement, int lastElement) {                                  //функция, сливающая массивы
    static int middleElement, start, final;
    static int mas[MAXSIZE];
    middleElement = (firstElement + lastElement) / 2;                                     //вычисление среднего элемента
    start = firstElement;                                                                 //начало левой части
    final = middleElement + 1;                                                            //начало правой части
    for (int i = firstElement; i <= lastElement; i++) {                                   //выполнять от начала до конца
        if ((start <= middleElement) && ((final > lastElement) || (A[start] < A[final]))) {
            mas[i] = A[start];
            start++;
        } else {
            mas[i] = A[final];
            final++;
        }
    }
    for (int i = firstElement; i <= lastElement; i++){
        A[i] = mas[i];                                                                   //возвращение результата в список
    }
};
void MergeSort(int massiv[], int firstElement, int lastElement) {                        //рекурсивная процедура сортировки
    if (firstElement < lastElement) {
        MergeSort(massiv, firstElement, (firstElement + lastElement) / 2);     //сортировка левой части
        MergeSort(massiv, (firstElement + lastElement) / 2 + 1, lastElement);  //сортировка правой части
        Merge(massiv, firstElement, lastElement);                                        //слияние двух частей
    }
};
class Timer {
public:
    Timer() {
        start = std::chrono::high_resolution_clock::now();
    }
    ~Timer() {
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration < double > duration = end - start;
        std::cout << "DURATION " << duration.count() << " s\n\n";
    }
private:
    std::chrono::time_point < std::chrono::high_resolution_clock > start, end;
};
int main() {
    srand(time(NULL));
    int arraSize;
    cout << "Array size > ";
    cin >> arraSize;
    //int testArray[6] = {1,4,5,2,7,8};
    int* sortableArray = new int[arraSize];
    for (int i = 0; i < arraSize; i++) {
        sortableArray[i] = (rand() % 100);
    }
    Timer t;
    //MergeSort(testArray, 0, 6); // тестирование сортировки
    MergeSort(sortableArray, 0, arraSize-1); //вызов сортирующей процедуры
    cout << "sorted array: "; //вывод упорядоченного массива
    for (int i = 1; i <= arraSize; i++) {
        cout << sortableArray[i] << " ";
    }
    return 0;
}