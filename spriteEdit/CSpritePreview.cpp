//----------------------------------------------------------------------------
#include <QPainter>
#include <QtDebug>
#include "CSpritePreview.h"
//----------------------------------------------------------------------------
#define MARGIN                      5
//----------------------------------------------------------------------------
CSpritePreview::CSpritePreview(QWidget *parent) : QWidget(parent) {
    sprite = 0;
    currentMotion = CSprite::emNothing;
    currentFrameIndex = 0;

    backImage = QImage(":/spriteEdit/images/fond.png");
}
//----------------------------------------------------------------------------
void CSpritePreview::setSprite(CSprite *sprite) {
    this->sprite = sprite;

    repaint();
}
//----------------------------------------------------------------------------
void CSpritePreview::setCurrentMotion(CSprite::EMotion currentMotion) {
    this->currentMotion = currentMotion;

    repaint();
}
//----------------------------------------------------------------------------
void CSpritePreview::setCurrentFrameIndex(int currentFrameIndex) {
    this->currentFrameIndex = currentFrameIndex;

    repaint();
}
//----------------------------------------------------------------------------
void CSpritePreview::paintEvent(QPaintEvent *) {
    int x, y;
    QPainter painter(this);

    for(y=0;y<size().height();y+=backImage.height()) {
        for(x=0;x<size().width();x+=backImage.width()) {
            painter.drawImage(QPoint(x, y), backImage);
        }
    }

    if(sprite != 0 && !sprite->getSpriteSheet().isNull()) {
        QImage spriteSheet = sprite->getSpriteSheet();
        int i;

        double w = MARGIN, h = 0;

        for(i=0;i<sprite->getFrameCount(currentMotion);i++) {
            CSpriteFrame spriteFrame = sprite->getFrame(currentMotion, i);

            w += spriteFrame.getRect().width() + MARGIN;
            h = qMax(h, (double)spriteFrame.getRect().height());
        }

        double coefX, coefY, coef, mX, mY;

        coefX = ((double)this->size().width()) / w;
        coefY = ((double)this->size().height()) / h;

        coef = coefX;
        if(coefX > coefY) {
            coef = coefY;
        }

        mX = (((double)this->size().width()) - w * coef) / 2.0 + MARGIN * coef;
        mY = (((double)this->size().height()) - h * coef) / 2.0;

        int x = mX;

        for(i=0;i<sprite->getFrameCount(currentMotion);i++) {
            CSpriteFrame spriteFrame = sprite->getFrame(currentMotion, i);
            QRect dst(x, mY + (h - spriteFrame.getRect().height()) * coef, spriteFrame.getRect().width() * coef, spriteFrame.getRect().height() * coef);

            painter.drawImage(dst, spriteSheet, spriteFrame.getRect());

            if(i == currentFrameIndex) {
                QPen pen(Qt::DotLine);
                pen.setColor(QColor(0, 0, 255));

                painter.setPen(pen);
                painter.drawRect(dst);
            }

            x += (spriteFrame.getRect().width() + MARGIN) * coef;
        }
    }
}
//----------------------------------------------------------------------------
