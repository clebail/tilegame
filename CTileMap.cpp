//----------------------------------------------------------------------------
#include <QtDebug>
#include "CTileMap.h"
//----------------------------------------------------------------------------
QDataStream& operator<<(QDataStream& out, const CTileMap& tileMap) {
    int i;

    out << tileMap.xMax;
    out << tileMap.yMax;
    out << tileMap.origin;

    for(i=0;i<tileMap.map.size();i++) {
        out << tileMap.map.at(i);
    }

    return out;
}
//-----------------------------------------------------------------------------------------------
QDataStream& operator>>(QDataStream& in, CTileMap& tileMap) {
    int x, y;

    in >> tileMap.xMax;
    in >> tileMap.yMax;
    in >> tileMap.origin;

    for(y=0;y<tileMap.yMax;y++) {
        for(x=0;x<tileMap.xMax;x++) {
            CTileGame tileGame;

            in >> tileGame;
            tileMap.map.append(tileGame);
        }
    }

    return in;
}
//-----------------------------------------------------------------------------------------------
CTileMap::CTileMap() {
    xMax = yMax= 0;
    origin = QPoint(0, 0);
}
//----------------------------------------------------------------------------
CTileMap::~CTileMap(void) {
    clear();
}
//----------------------------------------------------------------------------
void CTileMap::add(int x, int y, int tileIndex) {
    int mapIndex;
    CTileGame tileGame;

    if(x > xMax - 1 || y > yMax -1) {
        int newXMax = qMax(x + 1, xMax);
        int newYMax = qMax(y + 1, yMax);

        addToMap((newXMax * newYMax) - getTileCount());

        if(x > xMax - 1) {
            reorderMap(x + 1);
        }

        xMax = newXMax;
        yMax = newYMax;
    }

    mapIndex = y * xMax + x;
    tileGame = map[mapIndex];
    if(tileGame.tileIndex == 0) {
        tileGame.tileIndex = new int;
        map[mapIndex] = tileGame;
    }

    *tileGame.tileIndex = tileIndex;
}
//----------------------------------------------------------------------------
void CTileMap::remove(int x, int y) {
    int idx = y * xMax + x;
    CTileGame tileGame = map[idx];

    if(tileGame.tileIndex != 0) {
        delete tileGame.tileIndex;

        tileGame.tileIndex = 0;
        tileGame.score = 0;
        tileGame.bonusType = CTileGame::ebtNone;
    }

    map[idx] = tileGame;
    compress();
}
//----------------------------------------------------------------------------
int CTileMap::getTileCount(void) {
    return xMax * yMax;
}
//----------------------------------------------------------------------------
int * CTileMap::getTileIndex(int x, int y) {
    if(x >= xMax || y >= yMax) {
        return 0;
    }

    return map.at(y * xMax + x).tileIndex;
}
//----------------------------------------------------------------------------
CTileGame CTileMap::getTile(int x, int y) {
    if(x >= xMax || y >= yMax) {
        return CTileGame();
    }

    return map.at(y * xMax + x);
}
//----------------------------------------------------------------------------
void CTileMap::setTile(const CTileGame& tile, int x, int y) {
    if(x < xMax && y < yMax) {
        return map.replace(y * xMax + x, tile);
    }
}
//----------------------------------------------------------------------------
QSize CTileMap::getSize(void) {
    return QSize(xMax, yMax);
}
//----------------------------------------------------------------------------
void CTileMap::clear(void) {
    int i;

    for(i=0;i<getTileCount();i++) {
        if(map[i].tileIndex != 0) {
            delete map[i].tileIndex;
        }
    }

    map.clear();

    xMax = yMax= 0;
    origin = QPoint(0, 0);
}
//----------------------------------------------------------------------------
void CTileMap::setOrigin(const QPoint& p) {
    origin.setX(p.x());
    origin.setY(p.y());
}
//----------------------------------------------------------------------------
QPoint CTileMap::getOrigin(void) {
    return origin;
}
//----------------------------------------------------------------------------
void CTileMap::insertRow(int y) {
    int idx = y * xMax;
    int i;

    for(i=0;i<xMax;i++) {
        map.insert(idx, CTileGame());
    }
    yMax++;
}
//----------------------------------------------------------------------------
void CTileMap::insertColumn(int x) {
    int xM, y;

    reorderMap(xMax+1);
    xMax++;

    for(y=0;y<yMax;y++) {
        for(xM=xMax-1;xM>=x;xM--) {
            int idx = y * xMax + xM;

            if(xM > x) {
                map[idx] = map[idx-1];
            }else {
                map[idx] = CTileGame();
            }
        }
    }
}
//----------------------------------------------------------------------------
void CTileMap::compress(void) {
    int newXMax = 0;
    int newYMax = 0;
    int i;

    for(i=0;i<getTileCount();i++) {
        int x = i % xMax;
        int y = i / xMax;

        if(map[i].tileIndex != 0) {
            newXMax = qMax(x + 1, newXMax);
            newYMax = qMax(y + 1, newYMax);
        }
    }

    reorderMap(newXMax);

    xMax = newXMax;
    yMax = newYMax;
}
//----------------------------------------------------------------------------
void CTileMap::addToMap(int nb) {
    int i;

    for(i=0;i<nb;i++) {
        map.append(CTileGame());
    }
}
//----------------------------------------------------------------------------
void CTileMap::reorderMap(int newXMax) {
    int i;

    if(newXMax > xMax) {
        for(i=getTileCount()-1;i>=0;i--) {
            int x = i % xMax;
            int y = i / xMax;

            if(y > 0 && map[i].tileIndex != 0) {
                int newI = y * newXMax + x;

                map[newI] = map[i];
                map[i].tileIndex = 0;
            }
        }
    } else if(newXMax < xMax) {

    }
}
//----------------------------------------------------------------------------
