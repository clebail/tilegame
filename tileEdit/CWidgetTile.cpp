//----------------------------------------------------------------------------
#include <QPainter>
#include "CWidgetTile.h"
//----------------------------------------------------------------------------
#define TILE_WIDTH                  16
#define TILE_HEIGHT                 16
#define SEP_WIDTH                   2
#define SEP_HEIGHT                  2
#define REAL_TILE_WIDTH             (TILE_WIDTH + SEP_WIDTH)
#define REAL_TILE_HEIGHT            (TILE_HEIGHT + SEP_HEIGHT)
#define OFFSET_X                    (2 * SEP_WIDTH)
#define OFFSET_Y                    (2 * SEP_HEIGHT)
//----------------------------------------------------------------------------
CWidgetTile::CWidgetTile(QWidget *parent) : QWidget(parent) {
    x = y = 0;
    maxX = maxY = 0;
}
//----------------------------------------------------------------------------
void CWidgetTile::setImage(QImage *image) {
    this->image = image;

    maxX = (image->size().width() - 2 * OFFSET_X) / REAL_TILE_WIDTH;
    maxY = (image->size().height() - 2 * OFFSET_Y) / REAL_TILE_HEIGHT;

    repaint();
}
//----------------------------------------------------------------------------
void CWidgetTile::incX(void) {
    if(x < maxX) {
        x++;
        repaint();
    }
}
//----------------------------------------------------------------------------
void CWidgetTile::decX(void){
    if(x > 0 ){
        x--;
        repaint();
    }
}
//----------------------------------------------------------------------------
void CWidgetTile::incY(void){
    if(y < maxY) {
        y++;
        repaint();
    }
}
//----------------------------------------------------------------------------
void CWidgetTile::decY(void) {
    if(y > 0) {
        y--;
        repaint();
    }
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
