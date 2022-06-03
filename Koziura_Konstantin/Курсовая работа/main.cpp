#include <iostream>
#include <vector>
#include <chrono>
#include <random>

class Point {
    friend class Plane;
    friend bool operator != (const Point &a, const Point &b) {
        return !(a.x == b.x && a.y == b.y);
    }
private:
    double x;
    double y;
public:
    ~Point() {;}
    Point() {
        x = 0;
        y = 0;
    }
    Point(double X, double Y) {
        x = X;
        y = Y;
    }
};

class Plane {
private:
    std::vector<Point> mas;
    std::vector<int> convex_hull;
    int numb;

    double OrientTriangle2(int p1,int p2, int p3);
    bool isInside(int p1,int p2, int p3);

public:

    Plane(){
        numb = 0;
    }

    Plane(int numb) {
        this->numb = numb;
        if (numb > 0) {
            mas.resize(numb);
        }
    }

    ~Plane() {
        mas.clear();
        convex_hull.clear();
    }
    void input();
    void ConvexHullJarvis();

};

double Plane::OrientTriangle2(int p1,int p2, int p3) {
    return mas[p1].x * (mas[p2].y - mas[p3].y) + mas[p2].x * (mas[p3].y - mas[p1].y) + mas[p3].x * (mas[p1].y - mas[p2].y);
}

bool Plane::isInside(int p1,int p2, int p3) {
    return ( mas[p1].x <= mas[p2].x && mas[p2].x <= mas[p3].x &&
             mas[p1].y <= mas[p2].y && mas[p2].y <= mas[p3].y);
}

void Plane::input() {
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.5,0.1);
    //std::uniform_real_distribution<double> distribution(0,1);

    for (int i=0;i<numb;i++) {
        mas[i].x = distribution(generator);
        mas[i].y = distribution(generator);
    }
}
void Plane::ConvexHullJarvis() {
    auto start_time = std::chrono::steady_clock::now();
    // находим самую левую из самых нижних
    if (numb < 1) {
        return;
    }
    int base = 0;
    for (int i=1;i<numb;i++) {
        if ((mas[i].y < mas[base].y) || (mas[i].y == mas[base].y && mas[i].x < mas[base].x)) {
            base = i;
        }
    }
    // эта точка точно входит в выпуклую оболочку
    convex_hull.push_back(base);

    int first = base;
    int cur = base;
    do {
        int next = (cur + 1) % numb;
        for (int i=0;i<numb;i++) {
            double sign = OrientTriangle2(cur, next, i);
            // точка mas[i] находится левее прямой ( mas[cur], mas[next] )
            if (sign < 0) // обход выпуклой оболочки против часовой стрелки
                next = i;
                // точка лежит на прямой, образованной точками  mas[cur], mas[next]
            else if (sign == 0) {
                // точка mas[i] находится дальше, чем mas[next] от точки mas[cur]
                if (isInside(cur,next,i))
                    next = i;
            }
        }
        cur = next;
        convex_hull.push_back(next);
    }
    while (cur != first);
    auto end_time = std::chrono::steady_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
    std::cout << elapsed_ns.count() << "\n";
}

int main() {

    Plane pl(250000);
    for (int i = 0; i < 10; ++i) {
        pl.input();
        pl.ConvexHullJarvis();
    }


    return 0;
}
