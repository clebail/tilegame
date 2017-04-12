//----------------------------------------------------------------------------
#include "CDialogAnimate.h"
//----------------------------------------------------------------------------
CDialogAnimate::CDialogAnimate(QWidget *parent) : QDialog(parent) {
    setupUi(this);

    timer = new QTimer(this);
    timer->setInterval(1000 - slTime->value());
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));

    sprite = 0;
    motionIndex = -1;
    currentFrame = 0;
}
//----------------------------------------------------------------------------
CDialogAnimate::~CDialogAnimate(void) {
    delete timer;
}
//----------------------------------------------------------------------------
void CDialogAnimate::setSprite(CSprite *sprite) {
    this->sprite = sprite;
    motionIndex = -1;
    currentFrame = 0;
}
//----------------------------------------------------------------------------
void CDialogAnimate::setMotionIndex(int index) {
    motionIndex = index;
    if(sprite != 0) {
        int i, wMax, hMax;
        double coefX, coefY;


        for(i=wMax=hMax=0;i<sprite->getFrameCount(motionIndex);i++) {
            CSpriteFrame *spriteFrame = sprite->getFrame(motionIndex, i);

            if(wMax < spriteFrame->getRect().width()) {
                wMax = spriteFrame->getRect().width();
            }

            if(hMax < spriteFrame->getRect().height()) {
                hMax = spriteFrame->getRect().height();
            }
        }

        coefX = ((double)wAnimate->width()) / ((double)wMax);
        coefY = ((double)wAnimate->height()) / ((double)hMax);

        coef = coefX;
        if(coefX > coefY) {
            coef = coefY;
        }

        x = (wAnimate->width() - wMax * coef) / 2;
        y = (wAnimate->height() + hMax * coef) / 2;
    }
}
//----------------------------------------------------------------------------
void CDialogAnimate::on_pbPlay_clicked(void) {
    timer->start();
    currentFrame = 0;
}
//----------------------------------------------------------------------------
void CDialogAnimate::on_pbStop_clicked(void) {
    timer->stop();
    currentFrame = 0;
}
//----------------------------------------------------------------------------
void CDialogAnimate::on_slTime_valueChanged(int value) {
    timer->setInterval(1000 - value);
}
//----------------------------------------------------------------------------
void CDialogAnimate::timeout(void) {
    if(sprite != 0 && motionIndex != -1) {
        if(currentFrame >= sprite->getFrameCount(motionIndex)) {
            currentFrame = 0;
        }



        currentFrame++;
    }
}
//----------------------------------------------------------------------------
