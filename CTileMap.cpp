//----------------------------------------------------------------------------
#include <QtDebug>
#include "CTileMap.h"
//----------------------------------------------------------------------------
CTileMap::CTileMap() {
    xMax = yMax= 0;
}
//----------------------------------------------------------------------------
CTileMap::~CTileMap(void) {
    int i;

    for(i=0;i<getTileCount();i++) {
        delete map[i];
    }
}
//----------------------------------------------------------------------------
void CTileMap::add(int x, int y, int tileIndex) {
    int mapIndex;
    int *mapValue;

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
    if(map[mapIndex] == 0) {
        map[mapIndex] = new int;
    }

    mapValue = map[mapIndex];
    *mapValue = tileIndex;
}
//----------------------------------------------------------------------------
void CTileMap::remove(int x, int y) {

}
//----------------------------------------------------------------------------
int CTileMap::getTileCount(void) {
    return xMax * yMax;
}
//----------------------------------------------------------------------------
int * CTileMap::getTile(int x, int y) {
    if(x >= xMax || y >= yMax) {
        return 0;
    }

    return map.at(y * xMax + x);
}
//----------------------------------------------------------------------------
void CTileMap::addToMap(int nb) {
    int i;

    for(i=0;i<nb;i++) {
        map.append(0);
    }
}
//----------------------------------------------------------------------------
void CTileMap::reorderMap(int newXMax) {
    int i;

    for(i=getTileCount()-1;i>=0;i--) {
        int x = i % xMax;
        int y = i / xMax;

        if(y > 0 && map[i] != 0) {
            int newI = y * newXMax + x;

            map[newI] = map[i];
            map[i] = 0;

            qDebug() << "Décale";
            qDebug() << map;

        }
    }
}
//----------------------------------------------------------------------------
