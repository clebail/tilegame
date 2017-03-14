//----------------------------------------------------------------------------
#include <QPainter>
#include <common.h>
#include "CWidgetTile.h"
//----------------------------------------------------------------------------
CWidgetTile::CWidgetTile(QWidget *parent) : QWidget(parent) {
    x = y = 0;
}
//----------------------------------------------------------------------------
void CWidgetTile::setImage(QImage *image) {
    this->image = image;

    repaint();
}
//----------------------------------------------------------------------------
QImage * CWidgetTile::getImage(void) {
    return this->image;
}
//----------------------------------------------------------------------------
void CWidgetTile::setXY(int x, int y) {
    this->x = x;
    this->y = y;

    repaint();
}
//----------------------------------------------------------------------------
void CWidgetTile::paintEvent(QPaintEvent *) {
    int xt, yt, wt, ht;
    QPainter painter(this);
    QRect src(x * (REAL_TILE_WIDTH) + OFFSET_X, y * (REAL_TILE_HEIGHT) + OFFSET_Y, TILE_WIDTH, TILE_HEIGHT);

    if(this->size().width() >= this->size().height()) {
        xt = (this->size().width() - this->size().height()) / 2;
        yt = 0;
        wt = ht = this->size().height();
    } else {
        xt = 0;
        yt = (this->size().height() - this->size().width()) / 2;
        wt = ht = this->size().width();
    }

    painter.drawImage(QRect(xt, yt, wt, ht), *image, src);
}
//----------------------------------------------------------------------------
