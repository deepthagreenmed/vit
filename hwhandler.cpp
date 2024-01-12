#include "hwhandler.h"
#include <QDebug>

void *mapped_base, *mapped_dev_base;
off_t dev_base = XPAR_AXI_COMBINED_BASEADDR;



hwHandler::hwHandler(QObject *parent):
    QThread(parent)
{

    memfd = open("/dev/mem", O_RDWR | O_SYNC);
    if (memfd == -1) {
        //        printf("Can't open /dev/mem.\n");
        exit(0);
    }
    mapped_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, memfd, dev_base & ~MAP_MASK);
    if (mapped_base == (void *) -1) {
        //        printf("Can't map the memory to user space.\n");
        exit(0);
    }

        mapped_dev_base = mapped_base + (dev_base & MAP_MASK);
}


void hwHandler::vit_on(int periodCount)
{
    qDebug()<<periodCount;
    qDebug()<<"Vit ON";
   // if(periodCount<60||periodCount>1500)
       // return;
    *((uint16_t *) (mapped_dev_base  + VIT_COUNT_REG ))    = (uint16_t)(periodCount);
    *((uint8_t *) (mapped_dev_base  + VIT_ONOFF_REG ))   = VIT_ON_MASK;

}

void hwHandler::vit_off()
{
    *((uint8_t *) (mapped_dev_base  + VIT_ONOFF_REG ))   = VIT_OFF_MASK;
        qDebug()<<"Vit Off";
}

void hwHandler::vit_ontime(int ontime)
{
    *((uint8_t *) (mapped_dev_base  + VIT_ONTIME_REG ))   = ontime;
}

