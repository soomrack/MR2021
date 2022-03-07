#include "quizlogic.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
          stack = new QStackedWidget;
          stack->setCurrentIndex(point);
          MainWindow::setCentralWidget(stack);

          User::setExp(0);

          text_file_vector.reserve(AMOUNT_OF_PAGES);
          page_vector.reserve(AMOUNT_OF_PAGES);
          layout_vector.reserve(AMOUNT_OF_PAGES);
          text_vector.reserve(AMOUNT_OF_PAGES);
          yesButton_vector.reserve(AMOUNT_OF_PAGES);
          noButton_vector.reserve(AMOUNT_OF_PAGES);
          lineEdit_vector.reserve(AMOUNT_OF_PAGES);

          text_file_vector.push_back(new MyQFile("C:\\MyFiles\\cpp_proj\\quizzzz\\Texts\\text0.txt"));
          page_vector.push_back(new QWidget());
          layout_vector.push_back(new QVBoxLayout());
          text_vector.push_back(new QTextBrowser());
          text_vector.last()->setText(text_file_vector.last()->readFile());
          ok_button = new QPushButton("Ok");
          stack->addWidget(page_vector.last());
          page_vector.last()->setLayout(layout_vector.last());
          layout_vector.last()->addWidget(text_vector.last());
          layout_vector.last()->addWidget(ok_button);


          LongQuestion quest1(*this, "C:\\MyFiles\\cpp_proj\\quizzzz\\Texts\\text1.txt");
          ShortQuestion quest2(*this,"C:\\MyFiles\\cpp_proj\\quizzzz\\Texts\\text2.txt");


          connect(ok_button,SIGNAL (clicked()),this, SLOT(ok_button_clicked()));
          connect(lineEdit_vector[0], SIGNAL(returnPressed()),this,SLOT(lineEdit1_sent()));
          connect(yesButton_vector[0],SIGNAL(clicked()),this, SLOT(quest2_sent()));
          connect(noButton_vector[0],SIGNAL(clicked()),this, SLOT(quest2_sent()));

}


MainWindow::~MainWindow()
{
    delete ok_button;

}

QString MainWindow::MyQFile::readFile(){
    QString str="";
    this->open(QIODevice::ReadOnly);
    if (this->exists())
    {
        while(!this->atEnd())
        {
            str=str+this->readLine();
        }
        this->close();
    }
    return str;
}

void MainWindow::ok_button_clicked(){
    point++;
    stack->setCurrentIndex(point);
}

void MainWindow::lineEdit1_sent(){
    point++;
    stack->setCurrentIndex(point);
    if (lineEdit_vector[0]->text()=="Петр Первый") {
        User::increaseExp();
    }
    qDebug()<<User::getExp();
};

void MainWindow::quest2_sent(){
    point++;
    stack->setCurrentIndex(point);
    QObject* button = QObject::sender();
    if (button == yesButton_vector[0]) {
        User::increaseExp();
    }
     qDebug()<<User::getExp();
}
