//----------------------------------------------------------------------------
#include <QPainter>
#include "CWidgetSimulate.h"
//----------------------------------------------------------------------------
CWidgetSimulate::CWidgetSimulate(QWidget *parent) : QWidget(parent) {
    front = back = 0;
}
//----------------------------------------------------------------------------
void CWidgetSimulate::setTileMaps(CTileMap *front, CTileMap *back) {
    this->front = front;
    this->back = back;

    repaint();
}
//----------------------------------------------------------------------------
void CWidgetSimulate::setTiles(CTiles *tiles) {
    this->tiles = tiles;

    groups = tiles->getGroups();

    repaint();
}
//----------------------------------------------------------------------------
void CWidgetSimulate::setTilesImage(QImage *tilesImage) {
    this->tilesImage = tilesImage;

    repaint();
}
//----------------------------------------------------------------------------
void CWidgetSimulate::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QBrush brush(QColor(74, 115, 207));
    QPen pen(QColor(74, 115, 207));

    painter.setBrush(brush);
    painter.setPen(pen);
    painter.drawRect(rect());

    drawBack(&painter);
    drawFront(&painter);
}
//----------------------------------------------------------------------------
void CWidgetSimulate::drawBack(QPainter *painter) {
}
//----------------------------------------------------------------------------
void CWidgetSimulate::drawFront(QPainter *painter) {

}
//----------------------------------------------------------------------------
