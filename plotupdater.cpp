#include "plotupdater.h"

#include <QDebug>
#include <QTimer>
#include <QFile>
#include <QProcess>

#include <stdint.h>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <vector>
#include <iostream>

#define OUTPUT_MIN 0
#define OUTPUT_MAX 16383
#define PRESSURE_MIN -1       // min is 0 for sensors that give absolute values
//#define PRESSURE_MAX 206842.7   // 30psi (and we want results in pascals)
#define PRESSURE_MAX 15 // in psi

PlotUpdater::PlotUpdater(QwtPlotCurve *curve, QwtPlot *plot) : curve(curve), plot(plot) {

    spi_fd = open("/dev/spidev2.0", O_RDWR);

    int mode;
    int bits = 8;
    int speed = 1000000;
    ioctl(spi_fd, SPI_IOC_WR_MODE, &mode);
    ioctl(spi_fd, SPI_IOC_RD_MODE, &mode);
    ioctl(spi_fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    ioctl(spi_fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
    ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    ioctl(spi_fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);

    // Create a timer to update the plot every 1000 milliseconds
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePlot()));
    timer->start(1000); // milliseconds
}

PlotUpdater::~PlotUpdater()
{
    close(spi_fd);
}

void PlotUpdater::updatePlot() {
    // Update curve data
    const int numPoints = 10000;
    QVector<double> xData(numPoints);
    QVector<double> yData(numPoints);
    QVector<double> x(numPoints/25);
    QVector<double> y(numPoints/25);

    for (int i = 0; i < numPoints; ++i) {
        xData[i] = i;
        yData[i] = convert();
        //qDebug() << xData[i] << " " << yData[i];
    }

    for(int j=0; j<numPoints; j+=25)
    {
        int xsum=0;
        int ysum=0;
        for(int i=j; i<(j+25); i++)
        {
            xsum += xData[i];
            ysum += yData[i];
        }
        x[j/25] = xsum/25;
        y[j/25] = ysum/25;
        //qDebug() << x[j/25] << " " << y[j/25];

    }

    // Set new data for the curve
    curve->setSamples(x, y);

    // Replot the plot
    plot->replot();
}

double PlotUpdater::convert()
{
    uint8_t tx[2] = {0xD7, 0x00};
    uint8_t rx[2] = {0x00, 0x00};
    int sample = 0;
    uint16_t delay = 0;
    uint8_t bits = 8;
    uint32_t speed = 1000000;

    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)tx,
        .rx_buf = (unsigned long)rx,
        .len = 2,
        .speed_hz = speed,
        .delay_usecs = delay,
        .bits_per_word = bits,
    };

    /* send the cmd to start the conversion and read the result */
    ioctl(spi_fd, SPI_IOC_MESSAGE(1), &tr);
    //qDebug()<<rx[0]<<rx[1];

    sample = (uint16_t)(((rx[0] & 0x3F) << 8) + rx[1]);
    float pressure = 1.0 * ((sample - OUTPUT_MIN) * (PRESSURE_MAX - PRESSURE_MIN) / (OUTPUT_MAX - OUTPUT_MIN) + PRESSURE_MIN);
    //qDebug()<< "sample: " << sample << "pressure: " << pressure;
    //qDebug()<<sample;
    //qDebug()<<pressure;
    return pressure;
}
