//----------------------------------------------------------------------------
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

    repaint();
}
//----------------------------------------------------------------------------
void CWidgetSimulate::setTilesImage(QImage *tilesImage) {
    this->tilesImage = tilesImage;

    repaint();
}
//----------------------------------------------------------------------------
