//----------------------------------------------------------------------------
#include <QPainter>
#include <QResizeEvent>
#include <QtDebug>
#include "CWidgetAnimate.h"
//----------------------------------------------------------------------------
CWidgetAnimate::CWidgetAnimate(QWidget *parent) : QWidget(parent) {
    backImage = QImage(":/spriteEdit/images/fond.png");
}
//----------------------------------------------------------------------------
void CWidgetAnimate::setData(CSprite *sprite, int motionIndex) {
    this->sprite = sprite;
    this->motionIndex = motionIndex;

    currentFrame = 0;

    updateMetrics();

    repaint();
}
//----------------------------------------------------------------------------
void CWidgetAnimate::updateFrame(void) {
    if(sprite != 0) {
        if(currentFrame >= sprite->getFrameCount(motionIndex)) {
            currentFrame = 0;
        }

        updateFrameMetrics();

        currentFrame++;

        repaint();
    }
}
//----------------------------------------------------------------------------
void CWidgetAnimate::paintEvent(QPaintEvent *) {
    int x, y;
    QPainter painter(this);

    for(y=0;y<size().height();y+=backImage.height()) {
        for(x=0;x<size().width();x+=backImage.width()) {
            painter.drawImage(QPoint(x, y), backImage);
        }
    }

    if(sprite != 0 && !image.isNull() && !rect.isNull()) {
        painter.drawImage(rect, image);
    }
}
//----------------------------------------------------------------------------
void CWidgetAnimate::resizeEvent(QResizeEvent * event) {
    QWidget::resizeEvent(event);

    updateMetrics();
}
//----------------------------------------------------------------------------
void CWidgetAnimate::updateMetrics(void) {
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

        coefX = ((double)width()) / ((double)wMax);
        coefY = ((double)height()) / ((double)hMax);

        coef = coefX;
        if(coefX > coefY) {
            coef = coefY;
        }

        x = (width() - wMax * coef) / 2;
        y = (height() + hMax * coef) / 2;

        updateFrameMetrics();
    }
}
//----------------------------------------------------------------------------
void CWidgetAnimate::updateFrameMetrics(void) {
    if(sprite != 0) {
        CSpriteFrame *spriteFrame;
        int h;

        spriteFrame = sprite->getFrame(motionIndex, currentFrame);
        image = sprite->getSpriteSheet().copy(spriteFrame->getRect());

        h = spriteFrame->getRect().height() * coef;
        rect = QRect(x, y - h, spriteFrame->getRect().width() * coef, h);
    }
}
//----------------------------------------------------------------------------
