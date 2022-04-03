#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define n 5

void qsortRecursive(int *mas, int size) {
    //Указатели в начало и в конец массива
    int i = 0;
    int j = size - 1;

    //Центральный элемент массива
    int mid = mas[size / 2];

    //Делим массив
    do {
        //Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
        //В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
        while(mas[i] < mid) {
            i++;
        }
        //В правой части пропускаем элементы, которые больше центрального
        while(mas[j] > mid) {
            j--;
        }

        //Меняем элементы местами
        if (i <= j) {
            int tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;

            i++;
            j--;
        }
    } while (i <= j);


    //Рекурсивные вызовы, если осталось, что сортировать
    if(j > 0) {
        //"Левый кусок"
        qsortRecursive(mas, j + 1);
    }
    if (i < size) {
        //"Првый кусок"
        qsortRecursive(&mas[i], size - i);
    }
}

void sort(int32_t* buf, uint32_t size){
    // if array's length is 0 then do nothing
    if (size == 0)
        return;

    // indexes of left and right edge of the array
    int64_t left = 0;
    int64_t right = size - 1;

    // central element
    int32_t mid = buf[size / 2];

    // replace elements which is less than "mid" to the left side
    // replace elements which is greater than "mid" to the right side
    do {
        while(buf[left] < mid) {
            left++;
        }
        while(buf[right] > mid) {
            right--;
        }

        if (left <= right) {
            int tmp = buf[left];
            buf[left] = buf[right];
            buf[right] = tmp;

            left++;
            right--;
            for (int i = 0; i < size; i++){
                printf("%d ", buf[i]);
            }
            printf("\n");
        }

    } while (left <= right);

    //sort left and right side recursively, if they have anything to sort
    if(right > 0) {
        sort(buf, right + 1);
    }
    if (left < size) {
        sort(&buf[left], size - left);
    }
}

int32_t getOrderStatistic(int32_t * buf, uint32_t size,  uint32_t j){
    if (size == 0)
        return 0;
    if (size == 1)
        return buf[0];
    int64_t left = 0;
    int64_t right = size - 1;

    int64_t mid = size / 2;

    do {
        while(buf[left] < buf[mid]) {
            left++;
        }
        while(buf[right] > buf[mid]) {
            right--;
        }

        if (left <= right) {
            int tmp = buf[left];
            buf[left] = buf[right];
            buf[right] = tmp;

            if (mid == right){
                mid = left;
            }
            else if (mid == right){
                mid = right;
            }

            left++;
            right--;
            for (int i = 0; i < size; i++){
                printf("%d ", buf[i]);
            }
            printf("\n");
        }

    } while (left <= right);

    if (right >= j){
        if(right > 0)
            return getOrderStatistic(buf, right + 1, j);
        return buf[0];
    }
    else{
        if (right < size - 1)
            return getOrderStatistic(&buf[right + 1], size - right - 1, j - right - 1);
        return buf[size - 1];
    }
}

int main() {
//    int a[] = { 427, 777, 517, 220, 597, 261, 566, 986, 450, 524, 819, 700, 49, 499, 56, 79, 447, 917, 749, };
//    sort(a, 19);
//    for (int i = 0; i < 19; i++){
//        printf("%d ", a[i]);
//    }

    int32_t buf[] = { 917, 430, 67, 250, 213, 226, 710, 811, 463, 428, 40, 254, 621, 901, 802, 906, 262, };
    printf("\n%d",getOrderStatistic( buf,17, 10));
    return 0;
}
