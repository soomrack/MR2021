#include <algorithm>        //Swap
#include "GL/freeglut.h"    //Graphic
#include <iostream>         //IO
#include <stdio.h>          //IO
#include <time.h>           //Rand seed, time
#include <unistd.h>         //POSIX API (Sleep)
#include <thread>           //Multithreading

//WIP
//#include "GL/gl.h"
//#include "GL/glut.h"
//#include "GL/glext.h"
//#include <stdlib.h>

int length = 10;
int delay = 10000;
int *arr;
int swapCounter = 0;
int sortIndex = 0;
char sortName[5][15] = {"QuickSort", "Bubble Sort", "BogoSort", "Insertion Sort", "Heap Sort"};
int typeSort = 0;
int startTime;
int endTime;
int sortTime = 0;


int main(int argc, char *argv[]);

void counterMessage(std::string message);

//--------------------Array--------------------
void fillArray();

void randomizeArray(int *arr, int length);

void swap(int index1, int index2);

void arrayColor(int i, float l);
//^^^^^^^^^^^^^^^^^^^^Array^^^^^^^^^^^^^^^^^^^^

int setUp(int argc, char **argv);

void render();

void displayText(float x, float y, float red, float green, float blue, char *string);

void polygon(float leftX, float rightX, float bottomY, float topY);

void keyboardEvent(unsigned char key, int x, int y);

//--------------------QuickSort--------------------
void visualizeQuickSort(int *a, int length);

void quickSort(int *a, int low, int high);

int partition(int *a, int low, int high);
//^^^^^^^^^^^^^^^^^^^^QuickSort^^^^^^^^^^^^^^^^^^^^

//--------------------Bubble Sort--------------------
void visualizeBubbleSort(int *a, int length);
//^^^^^^^^^^^^^^^^^^^^Bubble Sort^^^^^^^^^^^^^^^^^^^^

//--------------------BogoSort--------------------
void visualizeBogoSort(int *a, int length);

void shuffle(int *a, int length);

bool isSorted(int *a, int length);
//^^^^^^^^^^^^^^^^^^^^BogoSort^^^^^^^^^^^^^^^^^^^^

//--------------------Insertion Sort--------------------
void visualizeInsertionSort(int *a, int length);
//^^^^^^^^^^^^^^^^^^^^Insertion Sort^^^^^^^^^^^^^^^^^^^^

//--------------------Heap Sort--------------------
void visualizeHeapSort(int *a, int length);

void heapify(int *a, int length, int i);
//^^^^^^^^^^^^^^^^^^^^Heap Sort^^^^^^^^^^^^^^^^^^^^

void isItRunning();

void (*sort)(int *, int);


int main(int argc, char *argv[]) {
    srand(time(NULL));

    fillArray();
    sort = visualizeQuickSort;

    setUp(argc, argv);

    //printf("1"); //DEBUG
    free(arr);
    //printf("2"); //DEBUG
}


void counterMessage(std::string message) {
    std::cout << "\nSwap count in " << message << ": " << swapCounter << std::endl;
    swapCounter = 0;
}

void isItRunning() {
    MSG msg;
    if (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }
}


//--------------------Array--------------------
void fillArray() {
    free(arr);
    arr = (int *) malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i)
        arr[i] = i;
}

void randomizeArray(int *arr, int length) {
    for (int i = length - 1; i > 0; --i) {
        std::swap(arr[i], arr[rand() % (i + 1)]);
    }
}

void swap(int index1, int index2) {
    std::swap(arr[index1], arr[index2]);
    render();
    swapCounter++;
    usleep(delay);
}

void arrayColor(int i, float l) {
    if (arr[i] < (l / 6)) glColor3f(1, 6 * arr[i] / l, 0);
    else if (arr[i] < (l / 3)) glColor3f(1 - ((arr[i] - (l / 6)) * (6 / l)), 1, 0);
    else if (arr[i] < (l / 2)) glColor3f(0, 1, (arr[i] - (l / 3)) * (6 / l));
    else if (arr[i] < (2 * l / 3)) glColor3f(0, 1 - ((arr[i] - (l / 2)) * (6 / l)), 1);
    else if (arr[i] < (5 * l / 6)) glColor3f((arr[i] - (2 * l / 3)) * (6 / l), 0, 1);
    else glColor3f(1, 0, 1 - ((arr[i] - (5 * l / 6)) * (6 / l)));
}
//^^^^^^^^^^^^^^^^^^^^Array^^^^^^^^^^^^^^^^^^^^


int setUp(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Sort");

    glutDisplayFunc(render);
    glutKeyboardFunc(keyboardEvent);

    //printf("4"); //DEBUG
    //usleep(1000000);
    //printf("5"); //DEBUG

    glutMainLoop();
}


void render() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    float l = (float) length;
    float arrayWidth = 2 / l;
    switch (typeSort % 2) {
        case 0:
            for (int i = 0; i < length; ++i) {
                glBegin(GL_POLYGON);

                float arrayHeight = 2 * (arr[i] + 1) / l;
                float arrayWidthSum = 2 * i / l;

                float leftX = -1 + arrayWidthSum;
                float rightX = leftX + arrayWidth;
                float bottomY = -1;
                float topY = bottomY + arrayHeight;

                arrayColor(i, l);

                polygon(leftX, rightX, bottomY, topY);
                glEnd();
            }
            break;
        case 1:
            for (int i = 0; i < length; ++i) {

                float arrayHeight = 2 * (arr[i] + 1) / l;
                float arrayWidthSum = 2 * i / l;
                float midX = -1 + arrayWidthSum + arrayWidth;
                float midY = -1 + arrayHeight;

                arrayColor(i, l);

                char letter = arr[i] + 'a';

                glRasterPos2f(midX, midY);
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
            }
            break;
    }
    displayText(-0.98, 0.95, 1, 1, 1, sortName[sortIndex]);

    char charSwapCounter[10] = "";
    std::sprintf(charSwapCounter, "%d", swapCounter);
    displayText(-0.98, 0.88, 1, 1, 1, "Swap counter:");
    displayText(-0.69, 0.88, 1, 1, 1, charSwapCounter);

    char charArraySize[10] = "";
    std::sprintf(charArraySize, "%d", length);
    displayText(-0.98, 0.81, 1, 1, 1, "Array size:");
    displayText(-0.75, 0.81, 1, 1, 1, charArraySize);

    char charDelay[10] = "";
    std::sprintf(charDelay, "%d", delay);
    displayText(-0.98, 0.74, 1, 1, 1, "Delay (us):");
    displayText(-0.72, 0.74, 1, 1, 1, charDelay);
    glFlush();

    char charTime[10] = "";
    std::sprintf(charDelay, "%d", sortTime);
    displayText(-0.98, 0.67, 1, 1, 1, "Time (us):");
    displayText(-0.72, 0.67, 1, 1, 1, charDelay);
    glFlush();
}


void polygon(float leftX, float rightX, float bottomY, float topY) {
    glVertex2f(leftX, bottomY);
    glVertex2f(rightX, bottomY);
    glVertex2f(rightX, topY);
    glVertex2f(leftX, topY);
}

void displayText(float x, float y, float red, float green, float blue, char *string) {
    glColor3f(red, green, blue);
    glRasterPos2f(x, y);
    char *c;
    for (c = string; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
}

void keyboardEvent(unsigned char key, int x, int y) {
    //printf("Key:%d\n", key); //DEBUG

    //ESC - Exit
    //s - Sort
    //r - Randomize
    //Num 8 - Add delay (x10)
    //Num 2 - Reduce delay (/10)
    //Num 4 - Reduce size (/10)
    //Num 6 - Increase size (x10)

    switch (key) {
        //General purpose
        case 27:
            free(arr);
            exit(0);
        case 's':
            //std::thread sortThread(sort, arr, length);
            //sortThread.join();
            startTime = clock();
            sort(arr, length);
            endTime = clock();
            sortTime = endTime - startTime;
            break;
        case 'r':
            randomizeArray(arr, length);
            break;

            //NUMPAD
        case 56: //UP - NumPad 8
            if (delay < 40000)
                delay *= 2;
            //printf("1"); //DEBUG
            break;
        case 50: //DOWN - NumPad 2
            if (delay > 1)
                delay /= 2;
            break;
        case 52: //LEFT - NumPad 4
            if (length == 10)
                length = 5;
            else if (length > 10 && length != 26)
                length /= 10;
            fillArray();
            break;
        case 54: //RIGHT - NumPad 6
            if (length == 5)
                length = 10;
            else if (length < 1000 && length != 26)
                length *= 10;
            fillArray();
            break;
        case ']':
            typeSort++;
            if (typeSort % 2 == 0) length = 10;
            if (typeSort % 2 == 1) length = 26;
            fillArray();
            break;
        case '[':
            typeSort--;
            if (typeSort % 2 == 0) length = 10;
            if (typeSort % 2 == 1) length = 26;
            fillArray();
            break;

            //Sort
        case 'q':
            sort = visualizeQuickSort;
            sortIndex = 0;
            break;
        case 'b':
            sort = visualizeBubbleSort;
            sortIndex = 1;
            break;
        case 'u':
            sort = visualizeBogoSort;
            sortIndex = 2;
            break;
        case 'i':
            sort = visualizeInsertionSort;
            sortIndex = 3;
            break;
        case 'h':
            sort = visualizeHeapSort;
            sortIndex = 4;
            break;
    }
}


//--------------------QuickSort--------------------
void visualizeQuickSort(int *a, int length) {
    quickSort(a, 0, length - 1);
    counterMessage("QuickSort");
}

void quickSort(int *a, int low, int high) {
    isItRunning();
    if (low < high) {
        int pi = partition(a, low, high);

        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}

int partition(int *a, int low, int high) {
    int lowIndex = low - 1;
    int pivot = a[high];

    for (int i = low; i < high; ++i) {
        if (a[i] <= pivot) {
            ++lowIndex;
            swap(lowIndex, i);
        }
    }

    ++lowIndex;
    swap(lowIndex, high);

    return lowIndex;
}
//^^^^^^^^^^^^^^^^^^^^QuickSort^^^^^^^^^^^^^^^^^^^^


//--------------------Bubble Sort--------------------
void visualizeBubbleSort(int *a, int length) {
    for (int i = 0; i < length; i++) {
        isItRunning();
        for (int j = i + 1; j < length; j++)
            if (a[j] < a[i])
                swap(i, j);
    }
    counterMessage("Bubble Sort");
}
//^^^^^^^^^^^^^^^^^^^^Bubble Sort^^^^^^^^^^^^^^^^^^^^


//--------------------BogoSort--------------------
void visualizeBogoSort(int *a, int length) {
    while (!isSorted(a, length))
        shuffle(a, length);
    counterMessage("BogoSort");
}

void shuffle(int *a, int length) {
    for (int i = 0; i < length; i++)
        swap(a[i], a[rand() % length]);
}

bool isSorted(int *a, int length) {
    isItRunning();
    for (int i = 0; i < length; i++)
        if (a[i] > a[i + 1])
            return false;
    return true;
}
//^^^^^^^^^^^^^^^^^^^^BogoSort^^^^^^^^^^^^^^^^^^^^


//--------------------Insertion Sort--------------------
void visualizeInsertionSort(int *a, int length) {
    int key, j;
    for (int i = 1; i < length; i++) {
        isItRunning();
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            swap(j + 1, j);
            j = j - 1;
        }
        arr[j + 1] = key;
    }
    counterMessage("Insertion Sort");
}
//^^^^^^^^^^^^^^^^^^^^Insertion Sort^^^^^^^^^^^^^^^^^^^^


//--------------------Heap Sort--------------------
void visualizeHeapSort(int *a, int length) {
    for (int i = length / 2 - 1; i >= 0; i--)
        heapify(a, length, i);

    for (int i = length - 1; i > 0; i--) {
        swap(0, i);

        heapify(a, i, 0);
    }
    counterMessage("Heap Sort");
}

void heapify(int *a, int length, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;


    if (left < length && a[left] > a[largest])
        largest = left;

    if (right < length && a[right] > a[largest])
        largest = right;

    if (largest != i) {
        swap(i, largest);
        heapify(a, length, largest);
    }
}
//^^^^^^^^^^^^^^^^^^^^Heap Sort^^^^^^^^^^^^^^^^^^^^




//TEXT. Doesn't work. WIP
/*
void renderBitmapString(
        float x,
        float y,
        void *font,
        char *string) {

    char *c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
} */



