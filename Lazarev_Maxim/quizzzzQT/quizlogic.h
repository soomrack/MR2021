#ifndef QUIZLOGIC_H
#define QUIZLOGIC_H
#include "mainwindow.h"
#include <QDebug>



class Question {
private:

public:
    Question(MainWindow &w,const QString file_name);
};

class LongQuestion:public Question{
public:
    LongQuestion(MainWindow &w,const QString file_name);

};

class ShortQuestion:public Question{
public:
    ShortQuestion(MainWindow &w,const QString file_name);
};

class User {
public:
    static void increaseExp(){
        exp++;
    }

    static void setExp(qint32 value){
        exp = value;
    }

    static qint32 getExp(){
        return exp;
    }
private:
    static inline qint32 exp;
};



#endif // QUIZLOGIC_H
