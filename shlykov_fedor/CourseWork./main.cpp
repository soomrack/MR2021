#include <iostream>

#include <ctime>

#include <chrono>

using namespace std;
//функция, сливающая массивы
void Merge(int * A, int first, int last) {
    int middle, start, final, j;
    int * mas = new int[1000];
    middle = (first + last) / 2; //вычисление среднего элемента
    start = first; //начало левой части
    final = middle + 1; //начало правой части
    for (j = first; j <= last; j++) //выполнять от начала до конца
        if ((start <= middle) && ((final > last) || (A[start] < A[final]))) {
            mas[j] = A[start];
            start++;
        }
        else {
            mas[j] = A[final];
            final++;
        }
    //возвращение результата в список
    for (j = first; j <= last; j++) A[j] = mas[j];
    delete[] mas;
};
//рекурсивная процедура сортировки
void MergeSort(int * A, int first, int last) {
    {
        if (first < last) {
            MergeSort(A, first, (first + last) / 2); //сортировка левой части
            MergeSort(A, (first + last) / 2 + 1, last); //сортировка правой части
            Merge(A, first, last); //слияние двух частей
        }
    }
};
//главная функция
class Timer {
public:
    Timer() {
        start = std::chrono::high_resolution_clock::now();
    }~Timer() {
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration < double > duration = end - start;
        std::cout << "DURATION " << duration.count() << " s\n\n";
    }
private:
    std::chrono::time_point < std::chrono::high_resolution_clock > start, end;
};
int main() {
    srand(time(0));
    int i, n;
    int * A = new int[1000];
    cout << "Array size > ";
    cin >> n;
    for (i = 0; i < n; i++) {
        A[i] = (rand() % 1000);
    } {
        Timer t;
        MergeSort(A, 1, n); //вызов сортирующей процедуры
    }
    cout << "sorted array: "; //вывод упорядоченного массива
    for (i = 1; i <= n; i++) cout << A[i] << " ";
    delete[] A;
    return 0;
}