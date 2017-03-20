//----------------------------------------------------------------------------
#include <QtDebug>
#include <common.h>
#include "CWidgetGamePlay.h"
//----------------------------------------------------------------------------
CWidgetGamePlay::CWidgetGamePlay(QWidget *parent) : QWidget(parent) {
    x = y = 0;
    viewPortX = viewPortY = 0;

    tilesImage = 0;
    tileMap = 0;

    backImage = QImage(":/levelEdit/images/fond.png");
}
//----------------------------------------------------------------------------
void CWidgetGamePlay::setXY(int x, int y) {
    if(x >= GAME_NB_X - 1) {
        viewPortX = x - GAME_NB_X + 1;
        this->x = GAME_NB_X - 1;
    }else {
        viewPortX = 0;
        this->x = x;
    }

    if(y >= GAME_NB_Y - 1) {
        viewPortY = y - GAME_NB_Y + 1;
        this->y = GAME_NB_Y - 1;
    }else {
        viewPortY = 0;
        this->y = y;
    }

    emit(viewPortChange(QPoint(viewPortX, viewPortY)));

    repaint();
}
//----------------------------------------------------------------------------
void CWidgetGamePlay::setTilesImage(QImage *tilesImage) {
    this->tilesImage = tilesImage;
    xTileMax = (tilesImage->size().width() - OFFSET_X) / REAL_TILE_WIDTH;

    repaint();
}
//----------------------------------------------------------------------------
void CWidgetGamePlay::setTileMap(CTileMap *tileMap) {
    this->tileMap = tileMap;

    repaint();
}
//----------------------------------------------------------------------------
QPoint CWidgetGamePlay::getViewPortCoords(void) {
    return QPoint(viewPortX, viewPortY);
}
//----------------------------------------------------------------------------
void CWidgetGamePlay::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QRect select(x * GAME_TILE_WIDTH, y * GAME_TILE_HEIGHT, GAME_TILE_WIDTH, GAME_TILE_HEIGHT);
    QPen pen(Qt::blue);
    pen.setStyle(Qt::DotLine);
    pen.setWidth(2);

    drawBackground(&painter);

    if(tilesImage != 0 && tileMap != 0) {
        drawMap(&painter);
    }

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
void CWidgetGamePlay::drawMap(QPainter *painter) {
    int x, y;

    for(y=0;y<GAME_NB_Y;y++) {
        for(x=0;x<GAME_NB_X;x++) {
            int *tileIndex = tileMap->getTile(x + viewPortX, y + viewPortY);

            if(tileIndex != 0) {
                int xTile = (*tileIndex) % xTileMax;
                int yTile = (*tileIndex) / xTileMax;

                QRect src(xTile * REAL_TILE_WIDTH + OFFSET_X, yTile * REAL_TILE_HEIGHT + OFFSET_Y, TILE_WIDTH, TILE_HEIGHT);
                QRect dst(x * GAME_TILE_WIDTH, y * GAME_TILE_HEIGHT, GAME_TILE_WIDTH, GAME_TILE_HEIGHT);

                painter->drawImage(dst, *tilesImage, src);
            }
        }
    }
}
//----------------------------------------------------------------------------
