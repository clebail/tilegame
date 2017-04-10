//----------------------------------------------------------------------------
#include <QPainter>
#include <QtDebug>
#include "CSpriteFrameWidget.h"
//----------------------------------------------------------------------------
CSpriteFrameWidget::CSpriteFrameWidget(QWidget *parent) : QWidget(parent) {
     backImage = QImage(":/spriteEdit/images/fond.png");
}
//----------------------------------------------------------------------------
void CSpriteFrameWidget::setImage(const QImage& image) {
    this->image = image;

    repaint();
}
//----------------------------------------------------------------------------
void CSpriteFrameWidget::paintEvent(QPaintEvent *) {
    int x, y;
    QPainter painter(this);

    for(y=0;y<size().height();y+=backImage.height()) {
        for(x=0;x<size().width();x+=backImage.width()) {
            painter.drawImage(QPoint(x, y), backImage);
        }
    }

    if(!image.isNull()) {
        double w, h, mX, mY;

        w = ((double)this->size().width()) / ((double)image.width());
        h = ((double)this->size().height()) / ((double)image.height());

        if(w <= h) {
            h = w;
        }else {
            w = h;
        }

        w *= image.width();
        h *= image.height();

        mX = (((double)this->size().width()) - w) / 2.0;
        mY = (((double)this->size().height()) - h) / 2.0;

        QRect dst(mX, mY, w, h);

        painter.drawImage(dst, image);
    }
}
//----------------------------------------------------------------------------
