//----------------------------------------------------------------------------
#include <QtDebug>
#include <QPainter>
#include <QMouseEvent>
#include <common.h>
#include "CTileSetWidget.h"

//----------------------------------------------------------------------------
CTileSetWidget::CTileSetWidget(QImage *image, QWidget *parent) : QWidget(parent) {
    setupUi(this);

    resize(image->size());
    this->image = image;
    x = y = 0;
}
//----------------------------------------------------------------------------
CTileSetWidget::~CTileSetWidget() {
}
//----------------------------------------------------------------------------
void CTileSetWidget::setXY(int x, int y) {
    this->x = x;
    this->y = y;

    repaint();
}
//----------------------------------------------------------------------------
void CTileSetWidget::paintEvent(QPaintEvent *) {
    if(image) {
        QPainter painter(this);
        QRect select(x * REAL_TILE_WIDTH + OFFSET_X, y * REAL_TILE_HEIGHT + OFFSET_Y, TILE_WIDTH, TILE_HEIGHT);
        QPen pen(Qt::blue);
        pen.setStyle(Qt::DotLine);
        pen.setWidth(2);

        painter.drawImage(QPoint(0, 0), *image);

        painter.setBrush(Qt::NoBrush);
        painter.setPen(pen);
        painter.drawRect(select);
    }
}
//----------------------------------------------------------------------------
void CTileSetWidget::mousePressEvent(QMouseEvent *event) {
    int x, y;

    x = (event->x() - OFFSET_X) / REAL_TILE_WIDTH;
    y = (event->y() - OFFSET_X) / REAL_TILE_HEIGHT;

    emit(mousePress(x, y));
}
//----------------------------------------------------------------------------

