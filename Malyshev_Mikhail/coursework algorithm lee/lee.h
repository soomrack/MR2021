#ifndef LEE_LEE_H
#define LEE_LEE_H

class Grid
{
private:
    int W;       // ширина рабочего поля
    int H;       // высота рабочего поля
    int **grid;

private:
    void memory_alloc();
    void free_memory();

public:
    Grid();
    Grid(int W, int H);
    void Random (); // случайная генерация поля
    bool lee(int ax, int ay, int bx, int by);     // поиск пути из клетки (ax, ay) в клетку (bx, by)
};

#endif