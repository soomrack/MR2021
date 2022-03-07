#include "quizlogic.h"

Question::Question(MainWindow &w, const QString file_name){
    w.text_file_vector.push_back(new MainWindow::MyQFile(file_name));
    w.page_vector.push_back(new QWidget());
    w.layout_vector.push_back(new QVBoxLayout());
    w.text_vector.push_back(new QTextBrowser());

    w.stack->addWidget(w.page_vector.last());
    w.page_vector.last()->setLayout(w.layout_vector.last());
    w.text_vector.last()->setText(w.text_file_vector.last()->readFile());
    w.layout_vector.last()->addWidget(w.text_vector.last());
}

LongQuestion::LongQuestion(MainWindow &w,const QString file_name):Question(w,file_name){
    w.lineEdit_vector.push_back(new QLineEdit());
    w.layout_vector.last()->addWidget(w.lineEdit_vector.last());
}

ShortQuestion::ShortQuestion(MainWindow &w,const QString file_name):Question(w,file_name){
    w.yesButton_vector.push_back(new QPushButton("0.39"));
    w.noButton_vector.push_back(new QPushButton("0.66"));
    w.layout_vector.last()->addWidget(w.yesButton_vector.last());
    w.layout_vector.last()->addWidget(w.noButton_vector.last());
}
