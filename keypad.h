#ifndef KEYPAD_H
#define KEYPAD_H

#include <QWidget>
#include <QLineEdit>

namespace Ui {
class keypad;
}

class keypad : public QWidget
{
    Q_OBJECT

public:
    explicit keypad(QWidget *parent = nullptr);
    ~keypad();
//    QLineEdit* display2;
//    double input;
    QString digit;
    bool back = false;

signals:
    //void entersignal(double input);
    void textsignal(const QString& digit);
    void backsignal();
    void entersignal();

private slots:
    void entertext();
    void enterback();
    void enterenter();


public slots:
 //   void click();


private:
    Ui::keypad *ui;

};

#endif // KEYPAD_H
