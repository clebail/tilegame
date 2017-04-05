//----------------------------------------------------------------------------
#include <QPainter>
#include <QtDebug>
#include "CWidgetSpriteSheet.h"
//----------------------------------------------------------------------------
CWidgetSpriteSheet::CWidgetSpriteSheet(QWidget *parent) : QWidget(parent) {
    setupUi(this);
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
void CWidgetSpriteSheet::paintEvent(QPaintEvent *) {
    if(!image.isNull()) {
        QPainter painter(this);

        painter.drawImage(QRect(0, 0, image.width() * zoomScale, image.height() * zoomScale), image);
    }
}
//----------------------------------------------------------------------------
