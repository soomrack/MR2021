
// Алгоритм Джарвиса

#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

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

double dist (const point &a, const point &b) {
    return sqrt( 0.0 + (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int numb;
std::vector<point> mas;
std::vector<int> convex_hull;
double P;

int input() {
    std::cin>>numb;
    if (numb > 0) {
        mas.resize(numb);
    }
    for (int i=0;i<numb;i++) {
        scanf("%d %d", &mas[i].x, &mas[i].y);
    }
    return numb;
}
double OrientTriangl2(const point &p1,const point &p2, const point &p3) {
    return p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y);
}

bool isInside(const point &p1, const point &p, const point &p2) {
    return ( p1.x <= p.x && p.x <= p2.x &&
             p1.y <= p.y && p.y <= p2.y);
}
void ConvexHullJarvis(const std::vector<point> &mas, std::vector<int> &convex_hull, int count) {
    // находим самую левую из самых нижних
    if (count < 1) {
        return;
    }
    int base = 0;
    for (int i=1;i<count;i++) {
        if (mas[i].y < mas[base].y)
            base = i;
        else
        if (mas[i].y == mas[base].y &&
            mas[i].x < mas[base].x)
            base = i;
    }
    // эта точка точно входит в выпуклую оболочку
    convex_hull.push_back(base);

    int first = base;
    int cur = base;
    do {
        int next = (cur + 1) % count;
        for (int i=0;i<count;i++) {
            double sign = OrientTriangl2(mas[cur], mas[next], mas[i]);
            // точка mas[i] находится левее прямой ( mas[cur], mas[next] )
            if (sign < 0) // обход выпуклой оболочки против часовой стрелки
                next = i;
                // точка лежит на прямой, образованной точками  mas[cur], mas[next]
            else if (sign == 0) {
                // точка mas[i] находится дальше, чем mas[next] от точки mas[cur]
                if (isInside(mas[cur],mas[next],mas[i]))
                    next = i;
            }
        }
        cur = next;
        convex_hull.push_back(next);
    }
    while (cur != first);
}
void solve() {
    ConvexHullJarvis(mas,convex_hull, numb);
    if (numb < 1) {
        return;
    }
    for (size_t i=0;i<convex_hull.size()-1;i++) {
        P += dist(mas[convex_hull[i]],mas[convex_hull[i+1]]);
    }
}

void output() {
    printf("%0.1f",P);
}

int main() {

    input();
    solve();
    output();

    return 0;
}
