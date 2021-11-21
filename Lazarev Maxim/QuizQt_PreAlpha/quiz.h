#ifndef QUIZ_H
#define QUIZ_H
#include <QApplication>

class User{
public:
    void set_point(qint32 value);
    qint32 get_point();
private:
    qint32 point;

};

class question {

};

class long_question: public question{

};

class short_question: public question{

};
#endif // QUIZ_H
