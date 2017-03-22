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
CTilesGroup * CTiles::getAnimatedGroup(QString groupName) {
    QHash<QString, CTilesGroup *> groups = getGroups();

    return groups.value(groupName);
}
//----------------------------------------------------------------------------
CTile * CTiles::getTile(int idx) {
    return tiles[idx];
}
//----------------------------------------------------------------------------
QHash<QString, CTilesGroup *> CTiles::getGroups(void) {
    QHash<QString, CTilesGroup *> groups;
    int i;

    for(i=0;i<tileCount;i++) {
        CTile *tile = tiles[i];

        if(tile->animated.active) {
            QString key = tile->animated.groupName;
            CTilesGroup *group;

            if(groups.contains(key)) {
                group = groups.value(key);
            }else {
                group = new CTilesGroup(key);
            }

            group->addTile(tile);

            groups.insert(key, group);
        }
    }

    return groups;
}
//----------------------------------------------------------------------------
