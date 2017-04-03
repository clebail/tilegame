//----------------------------------------------------------------------------
#include <QPainter>
#include <QtDebug>
#include <common.h>
#include "CWidgetSimulate.h"
//----------------------------------------------------------------------------
#define INC_FRONT           10
#define INC_BACK            (INC_FRONT / 2)
//----------------------------------------------------------------------------
CWidgetSimulate::CWidgetSimulate(QWidget *parent) : QWidget(parent) {
    front = back = 0;
    tiles = 0;
    tilesImage = 0;

    gentil = QImage(":/levelEdit/images/gentil.png");
    mechant = QImage(":/levelEdit/images/mechant.png");
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
void CWidgetSimulate::setLevel(CLevel *level) {
    this->level = level;
    front = level->getFront();
    back = level->getBack();

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
        if(xFront + GAME_WIDTH < front->getSize().width() * GAME_TILE_WIDTH) {
            xFront += INC_FRONT;
        }

        if(xBack + GAME_WIDTH < back->getSize().width() * GAME_TILE_WIDTH) {
            xBack += INC_BACK;
        }
    }
}
//----------------------------------------------------------------------------
void CWidgetSimulate::incY(void) {
    if(front != 0 && back != 0) {
        if(yFront + GAME_HEIGHT < front->getSize().height() * GAME_TILE_HEIGHT) {
            yFront += INC_FRONT;
        }

        if(yBack + GAME_HEIGHT < back->getSize().height() * GAME_TILE_HEIGHT) {
            yBack += INC_BACK;
        }
    }
}
//----------------------------------------------------------------------------
void CWidgetSimulate::decX(void) {
    if(front != 0 && back != 0) {
        if(xFront >= INC_FRONT) {
            xFront -= INC_FRONT;
        }

        if(xBack >= INC_BACK) {
            xBack -= INC_BACK;
        }
    }
}
//----------------------------------------------------------------------------
void CWidgetSimulate::decY(void) {
    if(front != 0 && back != 0) {
        if(yFront >= INC_FRONT) {
            yFront -= INC_FRONT;
        }

        if(yBack >= INC_BACK) {
            yBack -= INC_BACK;
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
    int i;

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

        if(!level->getPlayerStartPos().isNull()) {
            int px = level->getPlayerStartPos().x() * GAME_TILE_WIDTH;
            int py = level->getPlayerStartPos().y() * GAME_TILE_HEIGHT;

            if(px - xFront + GAME_TILE_WIDTH >= 0 && py - yFront + GAME_TILE_HEIGHT >= 0) {
                QRect dst(px - xFront, py - yFront, GAME_TILE_WIDTH, GAME_TILE_HEIGHT);

                painter.drawImage(dst, gentil);
            }
        }

        for(i=0;i<level->getMonsterStartPoss().size();i++) {
            QPoint p = level->getMonsterStartPoss().at(i);
            int px = p.x() * GAME_TILE_WIDTH;
            int py = p.y() * GAME_TILE_HEIGHT;

            if(px - xFront + GAME_TILE_WIDTH >= 0 && py - yFront + GAME_TILE_HEIGHT >= 0) {
                QRect dst(px - xFront, py - yFront, GAME_TILE_WIDTH, GAME_TILE_HEIGHT);

                painter.drawImage(dst, mechant);
            }
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
            int *tileIdx = tileMap->getTileIndex(tileX, tileY);

            if(tileIdx != 0) {
                CTile * tile = tiles->getTile(*tileIdx);
                if(tile) {
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
}
//----------------------------------------------------------------------------
