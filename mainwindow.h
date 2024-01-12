#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QInputDialog>
#include <QMouseEvent>
#include <QLineEdit>

#include "hwhandler.h"
#include "keypad.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool eventFilter(QObject* object, QEvent* event);

    QPushButton *on_btn;
    QPushButton *off_btn;

    QPushButton *inc_period_btn;
    QPushButton *dec_period_btn;

    QPushButton *inc_ontime_btn;
    QPushButton *dec_ontime_btn;


    double period = 60;
    double periodms = 1000;
    double timeon = 500;

    QLineEdit *lineEdit, *lineEdit_2;
    QLabel *label;




public slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_clicked(const QString& digit);

     void on_clickedbackspace();

     void on_clickedenter();




private:
    Ui::MainWindow *ui;
    hwHandler h;
    keypad *key;
    bool flag = false;


};
#endif // MAINWINDOW_H
