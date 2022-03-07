#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QFile>
#include <vector>


class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    const qint16 AMOUNT_OF_PAGES = 5;
    qint16 point = 0;

    class MyQFile:public QFile{
    public:
        MyQFile():QFile(){};
        MyQFile(const QString name):MyQFile(){
            this->setFileName(name);
        }
        MyQFile(const MyQFile& file):MyQFile(){
            this->setFileName(file.fileName());
        }
        MyQFile& operator=(const MyQFile& file){
            if(this==&file){
                return *this;
            }
            this->setFileName(file.fileName());
            return *this;
        }
         QString readFile();
    };
public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


     QStackedWidget *stack;
     QPushButton *ok_button=nullptr;
     QVector<QWidget*> page_vector;
     QVector<QVBoxLayout*> layout_vector;
     QVector<MyQFile*> text_file_vector;
     QVector<QTextBrowser*> text_vector;
     QVector<QPushButton*> yesButton_vector;
     QVector<QPushButton*> noButton_vector;
     QVector<QLineEdit*> lineEdit_vector;

    friend class Question;

private slots:
    void ok_button_clicked();
    void lineEdit1_sent();
    void quest2_sent();

};


#endif // MAINWINDOW_H
