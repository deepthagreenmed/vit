#include "mainwindow.h"
#include "plotupdater.h"
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
#include <QwtScaleWidget>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_scale_draw.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>

#if defined MAKE_VIT_LIB
    #define TEST_VIT_EXPORT Q_DECL_EXPORT
#else
    #define TEST_VIT_EXPORT Q_DECL_IMPORT
#endif


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

    // Create a QwtPlot widget
    QwtPlot *plot = new QwtPlot(centralWidget);

    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    canvas->setPalette(Qt::white);
    plot->setCanvas(canvas);

    layout->addWidget(plot);
    layout->addWidget(key);

    // Create a curve to be plotted
    QwtPlotCurve *curve = new QwtPlotCurve("Vit Graph");

    QColor color(Qt::green);
    curve->setStyle(QwtPlotCurve::Lines);
    curve->setPen(QPen(color, 2));

    // Attach the curve to the plot
    curve->attach(plot);

    QwtPlot::Axis axis = QwtPlot::xBottom;
    QwtScaleWidget *sw = plot->axisWidget(axis);
    sw->setPalette(Qt::green);

    QwtPlot::Axis axis2 = QwtPlot::yLeft;
    QwtScaleWidget *sw2 = plot->axisWidget(axis2);
    sw2->setPalette(Qt::green);

    // Create an object to handle dynamic updates of the plot
    PlotUpdater plotUpdater(curve, plot);

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


    // Set the range and scale of the x-axis
    plot->setAxisScale(QwtPlot::xBottom, 0, 10000, 50);

    // Set the range and scale of the y-axis
    plot->setAxisScale(QwtPlot::yLeft, 0, 20, 1);

    // Redraw the plot with the updated axis limits
    plot->replot();


    // Set up the main window
    mainWindow.setCentralWidget(centralWidget);
    mainWindow.setGeometry(100, 100, 800, 600);
    mainWindow.show();

    // Enter the application main loop
    return app.exec();
}




