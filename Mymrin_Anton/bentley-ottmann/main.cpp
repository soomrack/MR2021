#include <iostream>
#include <cmath>
#include <algorithm>
#include <random>
#include <ctime>
#include <map>
#include "bentley_ottmann.h"

using namespace std;

double eps=0.000000001; //eps=10^-9

Point::Point(double x, double y) {
    this->x=x;
    this->y=y;
}

Point::Point() {
    x=0;
    y=0;
}

Segment::Segment(Point first, Point last) : first(first),last(last) {
    if (this->first.x < this->last.x) {
        this->first=first;
        this->last=last;
    } else {
        this->first=last;
        this->last=first;
    }
    this->cur_x=cur_x;
}

Segment::Segment() {
    first={0,0};
    last={0,0};
    cur_x=0;
}

Segment & Segment::operator=(const Segment &s) {
    if (&s== this){
        return *this;
    }
    first.x=s.first.x;
    first.y=s.first.y;
    last.x=s.last.x;
    last.y=s.last.y;
    return *this;
}

//положение вектора ab относительно ac (по часовой(если >0) или против часовой стрелки(если <0))
double Event::direction(Point a, Point b, Point c) {
    return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
}

bool operator<(const Segment &s1,const Segment &s2) {

    double dir012=Event::direction(s1.first,s1.last,s2.first);
    double dir302=Event::direction(s2.last,s1.first,s2.first);
    double dir013=Event::direction(s1.first,s1.last,s2.last);
    if(Event::intersect(s1,s2)) {
        double ints_x=Event::intersection_point(s1,s2).x;
        double curx=max(s1.cur_x,s2.cur_x);
        if (curx<(ints_x-eps)) //если х выметающей меньше x точки пересечения
            return ((dir012>0)&&(dir302>0)&&(dir013)>0) or ((dir012>0)&&(dir302<0)&&(dir013)>0) or ((dir012>0)&&(dir302<0)&&(dir013)<0) or ((dir012<0)&&(dir302<0)&&(dir013)>0);
        else
            return !(((dir012>0)&&(dir302>0)&&(dir013)>0) or ((dir012>0)&&(dir302<0)&&(dir013)>0) or ((dir012>0)&&(dir302<0)&&(dir013)<0) or ((dir012<0)&&(dir302<0)&&(dir013)>0));
    }
    return ((dir012>0)&&(dir302>0)&&(dir013)>0) or ((dir012>0)&&(dir302<0)&&(dir013)>0) or ((dir012>0)&&(dir302<0)&&(dir013)<0) or ((dir012<0)&&(dir302<0)&&(dir013)>0);
}

bool operator==(const Segment &s1, const Segment &s2) {
    return (fabs(s1.first.x-s2.first.x)<eps)&&(fabs(s1.first.y==s2.first.y)<eps)&&(fabs(s1.last.x==s2.last.x)<eps)&&(fabs(s1.last.y==s2.last.y)<eps);
}

default_random_engine generator;
uniform_real_distribution<double> distribution(0.1,90);
double get_random() {
    return distribution(generator);
}

bool Event::on_segment(Point a, Point b, Point c) { //определяет, лежит ли точка c на отрезке ab
    if (fabs(direction(a,b,c))<eps and ((c.x>(a.x+eps))&&(c.x<(b.x-eps)) or (c.x>(b.x+eps))&&(c.x<(a.x-eps)))and ((c.y>(a.y+eps))&&(c.y<(b.y-eps)) or (c.y>(b.y+eps))&&(c.y<(a.y-eps))))
        return true;
    return false;
}

bool Event::intersect(Segment a, Segment b) { //определяет, есть ли пересечение
    double dir1= direction(b.first,b.last,a.first);
    double dir2= direction(b.first,b.last,a.last);
    double dir3= direction(a.first,a.last,b.first);
    double dir4= direction(a.first,a.last,b.last);
    if (((dir1>0)&&(dir2<0)or(dir1<0)&&(dir2>0))and((dir3>0)&&(dir4<0)or(dir3<0)&&(dir4>0)))
        return true;
    if (on_segment(b.first,b.last,a.first))
        return true;
    if (on_segment(b.first,b.last,a.last))
        return true;
    if (on_segment(a.first,a.last,b.first))
        return true;
    if (on_segment(a.first,a.last,b.last))
        return true;
    return false;
}

Point Event::intersection_point(Segment a, Segment b){ // Точка пересечения из уравнения прямой по двум ее точкам
    double x1=a.first.x;
    double x2=a.last.x;
    double x3=b.first.x;
    double x4=b.last.x;

    double y1=a.first.y;
    double y2=a.last.y;
    double y3=b.first.y;
    double y4=b.last.y;

    double ax=(y2-y1)/(x2-x1);
    double bx=(y4-y3)/(x4-x3);
    double ay=(x2-x1)/(y2-y1);
    double by=(x4-x3)/(y4-y3);

    double intersec_x=(x1*ax-x3*bx+y3-y1)/(ax-bx);
    double intersec_y=(y1*ay-y3*by+x3-x1)/(ay-by);
    return {intersec_x,intersec_y};

}

multimap <double,Segment> make_schedule(Segment data[],multimap <double,Segment> schedule, int size) {
    for (int i=0;i<size;i++) {
        schedule.insert(make_pair(data[i].first.x,data[i]));
        schedule.insert(make_pair(data[i].last.x,data[i]));
    }
    return schedule;
}
//существует ли в структуре отрезок выше
bool below_q( multimap <Segment, Segment> :: iterator it, multimap <Segment,Segment> &queue) {
    return it!=queue.begin();
}
//существует ли в структуре отрезок ниже
bool above_q(multimap <Segment, Segment> :: iterator it, multimap <Segment,Segment> &queue) {
    it++;
    return it!=queue.end();
}
//определяет, есть ли такая же точка пересечения в контейнере
bool equal_intpoint(multimap <double,pair<Segment,Segment>> intersections,double value) {
    multimap <double,pair<Segment,Segment>> :: iterator it;
    it=intersections.find(value);
    if (it!=intersections.begin()) {
        it--;
        if(fabs(value-it->first)<eps)
            return true;
        it++;
    }
    if ((it++)!=intersections.end()) {
        if (fabs(value-it->first)<eps)
            return true;
    }
    return false;
}

int intp_cnt=0; //счетчик точек пересечения

void event_handler(multimap <double,Segment> schedule,multimap <Segment,Segment> queue) {
    multimap <double,pair<Segment,Segment>> intersections;
    auto qit=queue.begin(); //итератор для очереди

    for(auto &it : schedule) {
        Event event{};
        Point intpoint{};
        if(intersections.find(it.first)!=intersections.end()) { //если х найдено в контейнере точек пересечения

            Segment above=intersections.find(it.first)->second.first;
            Segment below=intersections.find(it.first)->second.second;
            qit=queue.find(above);//итератор на верхний отрезок
            queue.erase(qit);
            above.cur_x=it.first;
            queue.insert(make_pair(above,above)); //замена верхнего и нижнего отрезка на новые с новым значением cur_x

            qit=queue.find(below);
            queue.erase(qit);
            below.cur_x=it.first;
            queue.insert(make_pair(below,below)); //новые отрезки будут иметь уже другой порядок относительно друг друга

            qit=queue.find(below);

            //далее проверим, есть ли точки пересечения с соседями у этих отрезков
            //т.е. верхнего отрезка с соседом сверху и нижнего с соседом снизу

            if (above_q(qit,queue)) { //если итератор - не начало контейнера - есть что-то выше
                qit++;
                Segment above_plus = qit->second; //если есть отрезок выше, инициализируем его
                qit--;
                if(event.intersect(qit->second,above_plus)) { //если отрезки пересекаются
                    intpoint=event.intersection_point(qit->second,above_plus);//ищем точку пересечения
                    intersections.insert(make_pair(intpoint.x, make_pair(above_plus,qit->second)));
                    if (equal_intpoint(intersections,intpoint.x)) {
                        intersections.erase(intersections.find(intpoint.x));
                    } else {
                        intp_cnt++;
                        schedule.insert(make_pair(intpoint.x,above_plus));// внесем в расписание отрезок
                    }
                }
            }
            qit=queue.find(above);
            if(below_q(qit,queue)) { //существует ли отрезок ниже
                qit--;
                Segment below_plus=qit->second;
                below.cur_x=it.first;
                qit++;
                if(event.intersect(qit->second,below_plus)) { //если отрезки пересекаются
                    intpoint=event.intersection_point(qit->second,below_plus);//ищем точку пересечения
                    intersections.insert(make_pair(intpoint.x, make_pair(qit->second,below_plus)));
                    if (equal_intpoint(intersections,intpoint.x)) {
                        intersections.erase(intersections.find(intpoint.x));
                    } else {
                        intp_cnt++;
                        schedule.insert(make_pair(intpoint.x,below_plus));// внесем в расписание отрезок
                    }
                    qit--;
                }
            }
        } else
        if (it.first==it.second.first.x) { // если точка НАЧАЛЬНАЯ, вносим в очередь
            it.second.cur_x=it.first; //x выметающей прямой запишем в cur_x отрезка
            queue.insert(pair<Segment,Segment>(it.second,it.second)); //вносим в очередь
            qit=queue.find(it.second); //итератор на отрезок, которому принадлежит точка
            if(above_q(qit,queue)){ //если итератор - не начало контейнера - есть что-то выше
                qit++; //итератор на отрезок выше
                Segment above = qit->second; //если есть отрезок выше, инициализируем его
                qit--;
                if(event.intersect(qit->second,above)) { //если отрезки пересекаются
                    intpoint=event.intersection_point(qit->second,above);//ищем точку пересечения
                    intersections.insert(make_pair(intpoint.x, make_pair(above,qit->second)));
                    if (equal_intpoint(intersections,intpoint.x)) { //если такая тока пересечения уже есть
                        intersections.erase(intersections.find(intpoint.x)); //удаляем из контейнера точек пересечения
                    } else {
                        intp_cnt++;
                        schedule.insert(make_pair(intpoint.x,above));// внесем в расписание отрезок
                    }
                }
            }
            if(below_q(qit,queue)) { //существует ли отрезок ниже
                qit--;
                Segment below=qit->second;
                below.cur_x=it.first;
                qit++;
                if(event.intersect(qit->second,below)) { //если отрезки пересекаются
                    intpoint=event.intersection_point(qit->second,below);//ищем точку пересечения
                    intersections.insert(make_pair(intpoint.x, make_pair(qit->second,below)));
                    if (equal_intpoint(intersections,intpoint.x)) {
                        intersections.erase(intersections.find(intpoint.x));
                    } else {
                        intp_cnt++;
                        schedule.insert(make_pair(intpoint.x,below));// внесем в расписание отрезок
                    }
                    qit--;
                }
            }
        } else
        if (it.first==it.second.last.x) {//если точка - КОНЕЦ
            it.second.cur_x=it.first; //записываем в отрезок х выметающей прямой
            qit=queue.find(it.second); //итератор на данный отрезок в очереди

            //если есть отрезки выше и ниже, проверяем их на пересечение

            if(above_q(qit,queue) && below_q(qit,queue)) {
                qit++;
                Segment above =qit->second; //определим верхний отрезок
                above.cur_x=it.first;
                advance(qit,-2);
                Segment below=qit->second; //определим нижний отрезок
                below.cur_x=it.first;
                qit++;
                if(event.intersect(above,below)) {
                    intpoint=event.intersection_point(above,below);//ищем точку пересечения
                    intersections.insert(make_pair(intpoint.x, make_pair(above,below)));
                    if (equal_intpoint(intersections,intpoint.x)) {
                        intersections.erase(intersections.find(intpoint.x));
                    } else {
                        intp_cnt++;
                        schedule.insert(make_pair(intpoint.x,above));// внесем в расписание отрезок
                    }
                }
            }
            queue.erase(qit); //обработав конец, отрезок можно удалить из очереди
        }
    }
}

void seg_inp(Segment s[],int numb) { //вводим рандомные отрезки
    for (int i=0;i<numb;i++) {
        Point p;
        Point q;
        p=Point{get_random(),get_random()};
        q=Point{get_random(),get_random()};
        s[i]=Segment{p,q};
    }
}

int main() {

    static Segment s[30];

    multimap <double,Segment> schedule;
    multimap <Segment,Segment> queue;

    seg_inp(s,30);
    schedule=make_schedule(s,schedule,30);
    event_handler(schedule,queue);
    cout << "count: "<<intp_cnt<<endl;
    cout << "runtime = " << clock() <<"ms"<< endl;
    return 0;
}



