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
        int *tileIndex = tileMap.map[i];

        if(tileIndex != 0) {
            out << QString::number(*tileIndex);
        }else {
            out << QString("N");
        }
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
            QString s;

            in >> s;

            if(s != "N") {
                int *tileIndex = new int;

                *tileIndex = s.toInt();
                tileMap.map.append(tileIndex);
            }else {
                tileMap.map.append(0);
            }
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
    int *mapValue;
    bool resize = false;

    if(x > xMax - 1 || y > yMax -1) {
        int newXMax = qMax(x + 1, xMax);
        int newYMax = qMax(y + 1, yMax);

        addToMap((newXMax * newYMax) - getTileCount());
        resize = true;

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

    if(resize) {
        emit(mapResize(QSize(xMax, yMax)));
    }
}
//----------------------------------------------------------------------------
void CTileMap::remove(int x, int y) {
    int idx = y * xMax + x;
    if(map[idx] != 0) {
        delete map[idx];
        map[idx] = 0;
    }
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
QSize CTileMap::getSize(void) {
    return QSize(xMax, yMax);
}
//----------------------------------------------------------------------------
void CTileMap::clear(void) {
    int i;

    for(i=0;i<getTileCount();i++) {
        delete map[i];
    }

    map.clear();
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
        }
    }
}
//----------------------------------------------------------------------------
