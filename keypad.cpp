#include "keypad.h"
#include "ui_keypad.h"

#include <QLineEdit>
#include <QDebug>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>

keypad::keypad(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::keypad)
{
    ui->setupUi(this);


    connect(ui->pushButton, &QPushButton::clicked, this, &keypad::entertext);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &keypad::entertext);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &keypad::entertext);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &keypad::entertext);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &keypad::entertext);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &keypad::entertext);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &keypad::entertext);
    connect(ui->pushButton_8, &QPushButton::clicked, this, &keypad::entertext);
    connect(ui->pushButton_9, &QPushButton::clicked, this, &keypad::entertext);
    connect(ui->pushButton_10, &QPushButton::clicked, this, &keypad::entertext);
    connect(ui->pushButton_11, &QPushButton::clicked, this, &keypad::enterback);
    connect(ui->pushButton_12, &QPushButton::clicked, this, &keypad::enterenter);
}


keypad::~keypad()
{
    delete ui;
}

void keypad::entertext()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
     if (button)
     {
         digit = button->text();
         emit textsignal(digit);
     }
}

void keypad::enterback()
{
    back = true;
    emit backsignal();
}

void keypad::enterenter()
{
    emit entersignal();
}



