//----------------------------------------------------------------------------
#include <QPainter>
#include <QtDebug>
#include <common.h>
#include "CWidgetSimulate.h"
//----------------------------------------------------------------------------
CWidgetSimulate::CWidgetSimulate(QWidget *parent) : QWidget(parent) {
    front = back = 0;
    tiles = 0;
    tilesImage = 0;
}
//----------------------------------------------------------------------------
CWidgetSimulate::~CWidgetSimulate(void) {
    QHashIterator<QString, CTilesGroup *> i(groups);
    while (i.hasNext()) {
        i.next();

        delete i.value();
    }
}
//----------------------------------------------------------------------------
void CWidgetSimulate::setTileMaps(CTileMap *front, CTileMap *back) {
    this->front = front;
    this->back = back;

    xFront = front->getOrigin().x() * GAME_TILE_WIDTH;
    yFront = front->getOrigin().y() * GAME_TILE_HEIGHT;

    xBack = back->getOrigin().x() * GAME_TILE_WIDTH;
    yBack = back->getOrigin().y() * GAME_TILE_HEIGHT;

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
void CWidgetSimulate::incX(void) {
    if(front != 0 && back != 0) {
        if(xFront + GAME_WIDTH < front->getSize().width() * GAME_TILE_WIDTH - 1) {
            xFront += 2;
        }

        if(xBack + GAME_WIDTH < back->getSize().width() * GAME_TILE_WIDTH) {
            xBack++;
        }
    }
}
//----------------------------------------------------------------------------
void CWidgetSimulate::incY(void) {
    if(front != 0 && back != 0) {
        if(yFront + GAME_HEIGHT < front->getSize().height() * GAME_TILE_HEIGHT - 1) {
            yFront += 2;
        }

        if(yBack + GAME_HEIGHT < back->getSize().height() * GAME_TILE_HEIGHT) {
            yBack++;
        }
    }
}
//----------------------------------------------------------------------------
void CWidgetSimulate::decX(void) {
    if(front != 0 && back != 0) {
        if(xFront >= 2) {
            xFront -= 2;
        }

        if(xBack) {
            xBack--;
        }
    }
}
//----------------------------------------------------------------------------
void CWidgetSimulate::decY(void) {
    if(front != 0 && back != 0) {
        if(yFront >= 2) {
            yFront -= 2;
        }

        if(yBack) {
            yBack--;
        }
    }
}
//----------------------------------------------------------------------------
void CWidgetSimulate::updateAnimate(void) {
    QHashIterator<QString, CTilesGroup *> i(groups);
    while (i.hasNext()) {
        i.next();

        i.value()->next();
    }
}
//----------------------------------------------------------------------------
void CWidgetSimulate::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QBrush brush(QColor(74, 115, 207));
    QPen pen(QColor(74, 115, 207));

    painter.setBrush(brush);
    painter.setPen(pen);
    painter.drawRect(rect());

    if(tilesImage != 0 && tiles != 0) {
        if(back != 0) {
            drawTiles(&painter, back, xBack, yBack);
        }
        if(front != 0) {
            drawTiles(&painter, front, xFront, yFront);
        }
    }
}
//----------------------------------------------------------------------------
void CWidgetSimulate::drawTiles(QPainter *painter, CTileMap *tileMap, int curX, int curY) {
    int x, y;

    for(y=0;y<GAME_HEIGHT;y++) {
        int screenY = y * GAME_TILE_HEIGHT;
        int realY = curY + screenY;
        int tileY = realY / GAME_TILE_HEIGHT;
        int h = GAME_TILE_HEIGHT - curY % GAME_TILE_HEIGHT;

        for(x=0;x<GAME_WIDTH;x++) {
            int screenX = x * GAME_TILE_WIDTH;
            int realX = curX + screenX;
            int tileX = realX / GAME_TILE_WIDTH;
            int *tileIdx = tileMap->getTile(tileX, tileY);

            if(tileIdx != 0) {
                CTile * tile = tiles->getTile(*tileIdx);
                int w = GAME_TILE_WIDTH - curX % GAME_TILE_WIDTH;

                QRect dst(screenX - GAME_TILE_WIDTH + w, screenY - GAME_TILE_HEIGHT + h, GAME_TILE_WIDTH, GAME_TILE_HEIGHT);

                if(tile->animated.active) {
                    tile = groups.value(tile->animated.groupName)->getCurrentTile();
                }

                painter->drawImage(dst, *tilesImage, QRect(tile->getRealX(), tile->getRealY(), TILE_WIDTH, TILE_HEIGHT));
            }
        }
    }
}
//----------------------------------------------------------------------------
