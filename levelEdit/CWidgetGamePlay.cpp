//----------------------------------------------------------------------------
#include <common.h>
#include "CWidgetGamePlay.h"
//----------------------------------------------------------------------------
CWidgetGamePlay::CWidgetGamePlay(QWidget *parent) : QWidget(parent) {
    x = y = 0;

    backImage = QImage(":/levelEdit/images/fond.png");
}
//----------------------------------------------------------------------------
void CWidgetGamePlay::setXY(int x, int y) {
    this->x = x;
    this->y = y;

    repaint();
}
//----------------------------------------------------------------------------
void CWidgetGamePlay::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QRect select(x * GAME_TILE_WIDTH, y * GAME_TILE_HEIGHT, GAME_TILE_WIDTH, GAME_TILE_HEIGHT);
    QPen pen(Qt::blue);
    pen.setStyle(Qt::DotLine);
    pen.setWidth(2);

    drawBackground(&painter);

    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen);
    painter.drawRect(select);
}
//----------------------------------------------------------------------------
void CWidgetGamePlay::drawBackground(QPainter *painter) {
    int x, y;

    for(y=0;y<size().height();y+=backImage.height()) {
        for(x=0;x<size().width();x+=backImage.width()) {
            painter->drawImage(QPoint(x, y), backImage);
        }
    }
}
//----------------------------------------------------------------------------
void CWidgetGamePlay::on_pbAdd_clicked(void) {

}
//----------------------------------------------------------------------------
