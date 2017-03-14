//----------------------------------------------------------------------------
#include <QDataStream>
#include <QFile>
#include <QtDebug>
#include "CTiles.h"
//----------------------------------------------------------------------------
CTiles::CTiles(int maxX, int maxY) {
    int i;

    tileCount = maxX * maxY;
    tiles = new PCTile[tileCount];
    for(i=0;i<tileCount;i++) {
        int x, y;

        y = i / maxX;
        x = i % maxX;

        tiles[i] = new CTile(x, y);
    }
}
//----------------------------------------------------------------------------
CTiles::~CTiles(void) {
    int i;

    for(i=0;i<tileCount;i++) {
        delete tiles[i];
    }

    delete[] tiles;
}
//----------------------------------------------------------------------------
void CTiles::load(QString fileName) {
    if(!fileName.isEmpty()) {
        QFile file(fileName);
        if(file.open(QIODevice::ReadOnly)) {
            QDataStream stream(&file);

            for(int i=0;i<tileCount;i++) {
                stream >> *(tiles[i]);
            }

            file.close();

            this->filename = fileName;
        }
    }
}
//----------------------------------------------------------------------------
void CTiles::save(QString fileName) {
    if(!fileName.isEmpty()) {
        QFile file(fileName);
        if(file.open(QIODevice::WriteOnly)) {
            QDataStream stream(&file);

            for(int i=0;i<tileCount;i++) {
                stream << *(tiles[i]);
            }

            file.close();

            this->filename = fileName;
        }
    }
}
//----------------------------------------------------------------------------
QString CTiles::getFileName(void) {
    return filename;
}
//----------------------------------------------------------------------------
QList<CTile *> CTiles::getAnimatedGroup(QString groupName) {
    QList<CTile *> ret;
    QHash<int, CTile *> tmp;
    int i;

    for(i=0;i<tileCount;i++) {
        CTile *tile = tiles[i];

        if(tile->animated.active && tile->animated.groupName == groupName) {
            for(int j=0;j<tile->animated.positions.size();j++) {
                tmp.insert(tile->animated.positions.at(j), tile);
            }
        }
    }

    QHashIterator<int, CTile *> it(tmp);
    while (it.hasNext()) {
        it.next();
        ret.append(it.value());
    }

    return ret;
}
//----------------------------------------------------------------------------
QPair<CTile *, CTile *> CTiles::getBistableGroup(QString groupName) {
    QPair<CTile *, CTile *> ret;

    return ret;
}
//----------------------------------------------------------------------------
CTile * CTiles::getTile(int idx) {
    return tiles[idx];
}
//----------------------------------------------------------------------------
