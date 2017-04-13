//----------------------------------------------------------------------------
#include <QtDebug>
#include "CDialogAnimate.h"
//----------------------------------------------------------------------------
CDialogAnimate::CDialogAnimate(QWidget *parent) : QDialog(parent) {
    setupUi(this);

    timer = new QTimer(this);
    timer->setInterval(1000 - slTime->value());
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
}
//----------------------------------------------------------------------------
CDialogAnimate::~CDialogAnimate(void) {
    delete timer;
}
//----------------------------------------------------------------------------
void CDialogAnimate::setData(CSprite *sprite, int motionIndex) {
    wAnimate->setData(sprite, motionIndex);
}
//----------------------------------------------------------------------------
void CDialogAnimate::on_pbPlay_clicked(void) {
    timer->start();
}
//----------------------------------------------------------------------------
void CDialogAnimate::on_pbStop_clicked(void) {
    timer->stop();
}
//----------------------------------------------------------------------------
void CDialogAnimate::on_slTime_valueChanged(int value) {
    int v = 1000 - value;

    timer->setInterval(v);
    slTime->setToolTip(QString::number(v));
}
//----------------------------------------------------------------------------
void CDialogAnimate::timeout(void) {
    wAnimate->updateFrame();
}
//----------------------------------------------------------------------------
