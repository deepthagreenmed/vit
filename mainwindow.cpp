#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "keypad.h"


#include <QTimer>
#include <QDialog>
#include <QFormLayout>
#include <QDoubleSpinBox>
#include <QDialogButtonBox>
#include <QObject>
#include <QLabel>
#include <QFormLayout>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QObject>
#include <QLineEdit>

#include <stdint.h>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <vector>
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


     key = new keypad;
//    key->show();


    on_btn = new QPushButton("ON", this);
    on_btn->setStyleSheet("QPushButton {background-color: red; color: white; }");
    connect(on_btn, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);

    off_btn = new QPushButton("OFF", this);
    off_btn->setStyleSheet("QPushButton {background-color: red; color: white; }");
    connect(off_btn, &QPushButton::clicked, this, &MainWindow::on_pushButton_2_clicked);

    inc_ontime_btn = new QPushButton("increase on time", this);
    inc_ontime_btn->setStyleSheet("QPushButton {background-color: red; color: white; }");
    connect(inc_ontime_btn, &QPushButton::clicked, this, &MainWindow::on_pushButton_3_clicked);

    dec_ontime_btn = new QPushButton("decrease on time", this);
    connect(dec_ontime_btn, &QPushButton::clicked, this, &MainWindow::on_pushButton_4_clicked);
    dec_ontime_btn->setStyleSheet("QPushButton {background-color: red; color: white; }");

    inc_period_btn = new QPushButton("increase period", this);
    connect(inc_period_btn, &QPushButton::clicked, this, &MainWindow::on_pushButton_5_clicked);
    inc_period_btn->setStyleSheet("QPushButton {background-color: red; color: white; }");

    dec_period_btn = new QPushButton("decrease period", this);
    connect(dec_period_btn, &QPushButton::clicked, this, &MainWindow::on_pushButton_6_clicked);
    dec_period_btn->setStyleSheet("QPushButton {background-color: red; color: white; }");



    lineEdit = new QLineEdit(QString::number(timeon));
    QPalette palette = lineEdit->palette();
    palette.setColor(QPalette::WindowText, Qt::blue);
    lineEdit->setPalette(palette);

    lineEdit_2 = new QLineEdit(QString::number(period));
    QPalette palette2 = lineEdit_2->palette();
    palette2.setColor(QPalette::WindowText, Qt::blue);
    lineEdit_2->setPalette(palette2);

    label = new QLabel(QString::number(periodms));
    QPalette palette3 = label->palette();
    palette3.setColor(QPalette::WindowText, Qt::blue);
    label->setPalette(palette3);

    lineEdit_2->installEventFilter(this);
    lineEdit->installEventFilter(this);

    connect(key, &keypad::textsignal, this, &MainWindow::on_clicked);
    connect(key, &keypad::backsignal, this, &MainWindow::on_clickedbackspace);
    connect(key, &keypad::entersignal, this, &MainWindow::on_clickedenter);

    lineEdit->clearFocus();
    lineEdit_2->clearFocus();

}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{

    if (obj == lineEdit_2 && event->type() == QEvent::MouseButtonPress)
    {
        lineEdit_2->setFocus();
        key->move(800,10);
        key->show();

    }

    if (obj == lineEdit && event->type() == QEvent::MouseButtonPress)
    {
        lineEdit->setFocus();
        key->move(800,10);
        key->show();

    }


    return false;

}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    h.vit_ontime(timeon);
    h.vit_on(periodms);
//    qDebug()<<timeon<<periodms;
}

void MainWindow::on_pushButton_2_clicked()
{
    h.vit_off();
}

void MainWindow::on_pushButton_5_clicked()
{
        period = period + 60;
        periodms = 1000 / (period / 60);
        //timeon = periodms/2;
        h.vit_ontime(timeon);
        h.vit_on(periodms);

        lineEdit->setText(QString::number(timeon));
        lineEdit_2->setText(QString::number(period));
        label->setText(QString::number(periodms));
}

void MainWindow::on_pushButton_6_clicked()
{
        period = period - 60;
        periodms = 1000 / (period / 60);
        //timeon = periodms/2;
        h.vit_ontime(timeon);
        h.vit_on(periodms);

        lineEdit->setText(QString::number(timeon));
        lineEdit_2->setText(QString::number(period));
        label->setText(QString::number(periodms));
}

void MainWindow::on_clicked(const QString& digit)
{
    bool ok;
    bool ok2;
    if(lineEdit->focusWidget()) {
        lineEdit_2->clearFocus();
        if(!flag)
        {
        lineEdit->setFocus();
        lineEdit->insert(digit);

     }
    }

      if(lineEdit_2->focusWidget())
      {
         lineEdit->clearFocus();
          flag=false;
          if(!flag)
          {
            lineEdit_2->setFocus();
            lineEdit_2->insert(digit);

          }
      }

    timeon = lineEdit->text().toDouble(&ok);
    period = lineEdit_2->text().toDouble(&ok2);

    lineEdit->setText(QString::number(timeon));
    lineEdit_2->setText(QString::number(period));
    label->setText(QString::number(periodms));
}

void MainWindow::on_clickedbackspace()
{
    bool ok;
    bool ok2;
    if (lineEdit->focusWidget())
    {

        QString data = lineEdit->text();
        data.chop(1);
        lineEdit->setText(data);



    }
    if(lineEdit_2->focusWidget())
    {

        QString data = lineEdit_2->text();
        data.chop(1);
        lineEdit_2->setText(data);

    }

    timeon = lineEdit->text().toDouble(&ok);
    period = lineEdit_2->text().toDouble(&ok2);

    lineEdit->setText(QString::number(timeon));
    lineEdit_2->setText(QString::number(period));
    label->setText(QString::number(periodms));

}

void MainWindow::on_clickedenter()
{
    key->hide();

    lineEdit->clearFocus();
    lineEdit_2->clearFocus();


    periodms = static_cast<double>(1000 / (period / 60));
   // timeon = periodms/2;

    h.vit_ontime(timeon);
    h.vit_on(periodms);

    lineEdit->setText(QString::number(timeon));
    lineEdit_2->setText(QString::number(period));
    label->setText(QString::number(periodms));

}

void MainWindow::on_pushButton_3_clicked()
{
    timeon = timeon+1;
    h.vit_ontime(timeon);

    lineEdit->setText(QString::number(timeon));
    lineEdit_2->setText(QString::number(period));
    label->setText(QString::number(periodms));
}

void MainWindow::on_pushButton_4_clicked()
{
    timeon = timeon-1;
    h.vit_ontime(timeon);

    lineEdit->setText(QString::number(timeon));
    lineEdit_2->setText(QString::number(period));
    label->setText(QString::number(periodms));
}
