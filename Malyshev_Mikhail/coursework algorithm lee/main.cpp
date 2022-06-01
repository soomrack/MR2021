#include <iostream>
#include <ctime>
#include "lee.h"

using namespace std;

int H = 100;
int W = 100;

int main() {

    srand(time(NULL));

    Grid Pole(H, W);
    Pole.Random();
    Pole.lee(0, 0, H - 1, W - 1);

    //cout << clock();
    return 0;
}
