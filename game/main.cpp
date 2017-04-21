//----------------------------------------------------------------------------
#include <QApplication>
#include <CTiles.h>
#include <QImage>
#include <QtDebug>
#include <common.h>
#include "CGame.h"
//----------------------------------------------------------------------------
int main(int, char **) {
    QImage tilesImage = QImage(":/game/images/tileset.png");
    CTiles *tiles = new CTiles((tilesImage.size().width() - 2 * OFFSET_X) / REAL_TILE_WIDTH + 1, (tilesImage.size().height() - 2 * OFFSET_Y) / REAL_TILE_HEIGHT + 1);
    CLevel *level;

    tiles->load(":/game/datas/tiles.til");

    CGame *w = new CGame(tiles, &tilesImage);

    level = new CLevel();
    level->load(":/game/levels/level1.lvl");

    w->setLevel(level);

    w->loop();

    qDebug() << 1;
    delete w;
    qDebug() << 2;
    delete level;
    qDebug() << 3;
    delete tiles;
    qDebug() << 4;

    return 0;
}
//----------------------------------------------------------------------------
