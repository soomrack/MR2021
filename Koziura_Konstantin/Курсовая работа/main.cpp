#include <iostream>
#include <vector>
#include <chrono>
#include <random>

struct point {
    double x,y;
    point() {
        x = 0;
        y = 0;
    }
    point(double X, double Y) {
        x = X;
        y = Y;
    }
};

bool operator != (const point &a, const point &b) {
    return !(a.x == b.x && a.y == b.y);
}

int numb;
std::vector<point> mas;
std::vector<int> convex_hull;

std::default_random_engine generator;
std::normal_distribution<double> distribution(0.5,0.1);
//std::uniform_real_distribution<double> distribution(0,1);


void input(int count) {
    numb = count;
    if (numb > 0) {
        mas.resize(numb);
    }
    for (int i=0;i<numb;i++) {
        mas[i].x = distribution(generator);
        mas[i].y = distribution(generator);
    }
}
double OrientTriangle2(const point &p1,const point &p2, const point &p3) {
    return p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y);
}

bool isInside(const point &p1, const point &p, const point &p2) {
    return ( p1.x <= p.x && p.x <= p2.x &&
             p1.y <= p.y && p.y <= p2.y);
}
void ConvexHullJarvis(const std::vector<point> &mass, std::vector<int> &convex_hul, int count) {
    auto start_time = std::chrono::steady_clock::now();
    // находим самую левую из самых нижних
    if (count < 1) {
        return;
    }
    int base = 0;
    for (int i=1;i<count;i++) {
        if ((mass[i].y < mass[base].y) || (mass[i].y == mass[base].y && mass[i].x < mass[base].x)) {
            base = i;
        }
    }
    // эта точка точно входит в выпуклую оболочку
    convex_hul.push_back(base);

    int first = base;
    int cur = base;
    do {
        int next = (cur + 1) % count;
        for (int i=0;i<count;i++) {
            double sign = OrientTriangle2(mass[cur], mass[next], mass[i]);
            // точка mas[i] находится левее прямой ( mas[cur], mas[next] )
            if (sign < 0) // обход выпуклой оболочки против часовой стрелки
                next = i;
                // точка лежит на прямой, образованной точками  mas[cur], mas[next]
            else if (sign == 0) {
                // точка mas[i] находится дальше, чем mas[next] от точки mas[cur]
                if (isInside(mass[cur],mass[next],mass[i]))
                    next = i;
            }
        }
        cur = next;
        convex_hul.push_back(next);
    }
    while (cur != first);
    auto end_time = std::chrono::steady_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
    std::cout << elapsed_ns.count() << "\n";
}

int main() {

    for (int k = 0; k < 10; ++k) {
        input(50000);
        ConvexHullJarvis(mas,convex_hull, numb);
    }

    return 0;
}
