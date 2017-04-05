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
    }

    repaint();
}
//----------------------------------------------------------------------------
void CWidgetSpriteSheet::paintEvent(QPaintEvent *) {
    if(!image.isNull()) {
        QPainter painter(this);

        painter.drawImage(QPoint(0, 0), image);
    }
}
//----------------------------------------------------------------------------
