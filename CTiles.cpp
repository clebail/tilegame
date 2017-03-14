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

            computeGroups();
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

    if(animatedGroups.contains(groupName)) {
       ret = animatedGroups.value(groupName);
    }

    return ret;
}
//----------------------------------------------------------------------------
QPair<CTile *, CTile *> CTiles::getBistableGroup(QString groupName) {
    QString bistableGroup = CTile::getGroup(groupName);
    QPair<CTile *, CTile *> ret;

    if(bistableGroups.contains(bistableGroup)) {
        ret = bistableGroups.value(bistableGroup);
    }

    return ret;
}
//----------------------------------------------------------------------------
CTile * CTiles::getTile(int idx) {
    return tiles[idx];
}
//----------------------------------------------------------------------------
void CTiles::computeGroups(void) {
    for(int i=0;i<tileCount;i++) {
    }
}
//----------------------------------------------------------------------------
