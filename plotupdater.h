#ifndef PLOTUPDATER_H
#define PLOTUPDATER_H

#include <QObject>
#include <QVector>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>

class PlotUpdater : public QObject
{
    Q_OBJECT
public:
    PlotUpdater(QwtPlotCurve *curve, QwtPlot *plot);
    ~PlotUpdater();
    double convert();

private slots:
    void updatePlot();

private:
    QwtPlotCurve *curve;
    QwtPlot *plot;
    QTimer *timer;
    int spi_fd;

};

#endif // PLOTUPDATER_H
