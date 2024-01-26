#include "mainwindow.h"
//#include "plotupdater.h"
#include "keypad.h"

#include <QApplication>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QtWidgets>
#include <QGridLayout>
#include <QLabel>
#include <QTimer>
#include <QObject>
#include <QtWidgets>


int main(int argc, char **argv) {
    QApplication app(argc, argv);

    // Create a main window
    QMainWindow mainWindow;
    MainWindow window;

    // Create a central widget for the main window
    QWidget *centralWidget = new QWidget(&mainWindow);
    keypad *key = new keypad(&mainWindow);

    // Create a layout for the central widget
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    layout->addWidget(key);

    QHBoxLayout *layout2 = new QHBoxLayout;

    // Add buttons
    layout2->addWidget(window.on_btn);
    layout2->addWidget(window.off_btn);
    layout2->addWidget(window.inc_ontime_btn);
    layout2->addWidget(window.dec_ontime_btn);
    layout2->addWidget(window.inc_period_btn);
    layout2->addWidget(window.dec_period_btn);

    layout2->addWidget(window.lineEdit);

    layout2->addWidget(window.lineEdit_2);

    layout2->addWidget(window.label);

    QWidget *subWidget = new QWidget;
    subWidget->setLayout(layout2);
    layout->addWidget(subWidget);


    // Set up the main window
    mainWindow.setCentralWidget(centralWidget);
    mainWindow.setGeometry(100, 100, 800, 600);
    mainWindow.show();

    // Enter the application main loop
    return app.exec();
}




