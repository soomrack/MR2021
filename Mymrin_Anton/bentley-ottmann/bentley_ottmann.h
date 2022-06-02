//
// Created by кОмП on 15.04.2022.
//

#ifndef BENTLEY_OTTMANN_BENTLEY_OTTMANN_H
#define BENTLEY_OTTMANN_BENTLEY_OTTMANN_H
struct Point {
    double x;
    double y;
    Point(double x,double y);
    Point();
};

struct Segment {
    Point first;
    Point last;
    double cur_x;
    Segment(Point first, Point last);
    Segment();

    Segment& operator=(const Segment &s);
    friend bool operator< (const Segment& s1,const Segment& s2);
    friend bool operator== (const Segment& s1,const Segment& s2);
};

class Event {
public:
    static bool intersect(Segment a, Segment b);
    static Point intersection_point(Segment a, Segment b);
    static double direction(Point a, Point b, Point c);
private:
    static bool on_segment(Point a, Point b, Point c);
};

#endif //BENTLEY_OTTMANN_BENTLEY_OTTMANN_H


