//----------------------------------------------------------------------------
#include <QPainter>
#include <QtDebug>
#include <QMouseEvent>
#include "CWidgetSpriteSheet.h"
//----------------------------------------------------------------------------
CWidgetSpriteSheet::CWidgetSpriteSheet(QWidget *parent) : QWidget(parent) {
    setupUi(this);

    mousePress = false;
    mouseOrigin = currentMousePos = QPoint();

    backImage = QImage(":/spriteEdit/images/fond.png");
}
//----------------------------------------------------------------------------
void CWidgetSpriteSheet::loadImage(QString fileName) {
    image = QImage(fileName);

    if(!image.isNull()) {
        resize(image.size());
        zoomScale = 1;
    }

    repaint();
}
//----------------------------------------------------------------------------
void CWidgetSpriteSheet::incZoomScale(void) {
    if(!image.isNull()) {
        zoomScale++;

        resize(image.width() * zoomScale, image.height() * zoomScale);

        repaint();
    }
}
//----------------------------------------------------------------------------
void CWidgetSpriteSheet::decZoomScale(void) {
    if(!image.isNull() && zoomScale > 1) {
        zoomScale--;

        resize(image.width() * zoomScale, image.height() * zoomScale);

        repaint();
    }
}
//----------------------------------------------------------------------------
int CWidgetSpriteSheet::getZoomScale(void) {
    return zoomScale;
}
//----------------------------------------------------------------------------
QImage CWidgetSpriteSheet::getImage(void) {
    return image;
}
//----------------------------------------------------------------------------
void CWidgetSpriteSheet::paintEvent(QPaintEvent *) {
    int x, y;
    QPainter painter(this);

    for(y=0;y<size().height();y+=backImage.height()) {
        for(x=0;x<size().width();x+=backImage.width()) {
            painter.drawImage(QPoint(x, y), backImage);
        }
    }

    if(!image.isNull()) {
        painter.drawImage(QRect(0, 0, image.width() * zoomScale, image.height() * zoomScale), image);

        if(mousePress) {
            QPen pen(Qt::DotLine);

            painter.setPen(pen);
            painter.drawRect(QRect(mouseOrigin, currentMousePos));
        }
    }
}
//----------------------------------------------------------------------------
void CWidgetSpriteSheet::mousePressEvent(QMouseEvent *event) {
    mousePress = true;
    mouseOrigin = currentMousePos = event->pos();
}
//----------------------------------------------------------------------------
void CWidgetSpriteSheet::mouseReleaseEvent(QMouseEvent *) {
    int x1, y1, x2, y2;
    mousePress = false;

    mouseOrigin /= zoomScale;
    currentMousePos /= zoomScale;

    x1 = getMinX(mouseOrigin, currentMousePos);
    y1 = getMinY(mouseOrigin, currentMousePos);
    x2 = getMaxX(mouseOrigin, currentMousePos);
    y2 = getMaxY(mouseOrigin, currentMousePos);

    emit(capture(QPoint(x1, y1), QPoint(x2, y2)));

    mouseOrigin = currentMousePos = QPoint();

    repaint();
}
//----------------------------------------------------------------------------
void CWidgetSpriteSheet::mouseMoveEvent(QMouseEvent *event) {
    currentMousePos = event->pos();

    repaint();
}
//----------------------------------------------------------------------------
int CWidgetSpriteSheet::getMinX(const QPoint &topLeft, const QPoint &bottomRight) {
    int i, j;

    if(!image.isNull()) {
        for(i=topLeft.x();i<bottomRight.x();i++) {
            for(j=topLeft.y();j<bottomRight.y();j++) {
                QRgb pixel = image.pixel(i, j);

                if(qAlpha(pixel) != 0) {
                    return i;
                }
            }
        }
    }

    return topLeft.x();
}
//----------------------------------------------------------------------------
int CWidgetSpriteSheet::getMaxX(const QPoint& topLeft, const QPoint& bottomRight) {
    int i, j;

    if(!image.isNull()) {
        for(i=bottomRight.x();i>=topLeft.x();i--) {
            for(j=topLeft.y();j<bottomRight.y();j++) {
                QRgb pixel = image.pixel(i, j);

                if(qAlpha(pixel) != 0) {
                    return i;
                }
            }
        }
    }

    return bottomRight.x();
}
//----------------------------------------------------------------------------
int CWidgetSpriteSheet::getMinY(const QPoint& topLeft, const QPoint& bottomRight) {
    int i, j;

    if(!image.isNull()) {
        for(i=topLeft.y();i<bottomRight.y();i++) {
            for(j=topLeft.x();j<bottomRight.x();j++) {
                QRgb pixel = image.pixel(j, i);

                if(qAlpha(pixel) != 0) {
                    return i;
                }
            }
        }
    }

    return topLeft.y();
}
//----------------------------------------------------------------------------
int CWidgetSpriteSheet::getMaxY(const QPoint& topLeft, const QPoint& bottomRight) {
    int i, j;

    if(!image.isNull()) {
        for(i=bottomRight.y();i>=topLeft.y();i--) {
            for(j=topLeft.x();j<bottomRight.x();j++) {
                QRgb pixel = image.pixel(j, i);

                if(qAlpha(pixel) != 0) {
                    return i;
                }
            }
        }
    }

    return bottomRight.y();
}
//----------------------------------------------------------------------------
