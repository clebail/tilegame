//----------------------------------------------------------------------------
#include <QDataStream>
#include <QFile>
#include <QtDebug>
#include "CTiles.h"
//----------------------------------------------------------------------------
CTiles::CTiles(int maxX, int maxY) {
    int i;

    tileCount = maxX * maxY;
    tiles = new PCItem[tileCount];
    for(i=0;i<tileCount;i++) {
        int x, y;

        y = i / maxX;
        x = i % maxX;

        tiles[i] = new CItem();
        tiles[i]->tile = new CTile(x, y);
    }
}
//----------------------------------------------------------------------------
CTiles::~CTiles(void) {
    int i;

    for(i=0;i<tileCount;i++) {
        delete tiles[i]->tile;
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
                QString animatedGroupName, bistableGroupName;

                stream >> *(tiles[i]->tile);

                animatedGroupName = tiles[i]->tile->animatedGroupName;
                bistableGroupName = tiles[i]->tile->bistableGroupName;

                if(!animatedGroupName.isEmpty()) {
                    int animatedPosition = CTile::getElement(animatedGroupName, 1).toInt();
                    int animatedCount = CTile::getElement(animatedGroupName, 2).toInt();

                    tiles[i]->animatedPosition = animatedPosition;
                    tiles[i]->tile->animatedCount = animatedCount;
                }

                if(!bistableGroupName.isEmpty()) {
                    bool bistableFirst = CTile::getElement(bistableGroupName, 1).toInt() != 0;

                    tiles[i]->bistableFirst = bistableFirst;
                }
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
                stream << *(tiles[i]->tile);
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
    QString animatedGroup = CTile::getGroup(groupName);
    QList<CTile *> ret;

    if(animatedGroups.contains(animatedGroup)) {
        QList<CItem *> items = animatedGroups.value(animatedGroup);
        for(int i=0;i<items.size();i++) {
            ret.append(items.at(i)->tile);
        }
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
    return tiles[idx]->tile;
}
//----------------------------------------------------------------------------
void CTiles::computeGroups(void) {
    for(int i=0;i<tileCount;i++) {
        CTile *tile = tiles[i]->tile;

        if(!tile->animatedGroupName.isEmpty()) {
            QString animatedGroup = CTile::getGroup(tile->animatedGroupName);
            QList<CItem *> items;
            int j;
            bool isInsert = false;

            if(animatedGroups.contains(animatedGroup)) {
                items = animatedGroups.value(animatedGroup);
            }

            for(j=0;j<items.size();j++) {
                if(items.at(j)->animatedPosition > tiles[i]->animatedPosition) {
                    items.insert(j, tiles[i]);
                    isInsert = true;
                    break;
                }
            }

            if(!isInsert) {
               items.append(tiles[i]);
            }

            animatedGroups.insert(animatedGroup, items);
        }

        if(!tile->bistableGroupName.isEmpty()) {
            QString bistableGroup = CTile::getGroup(tile->bistableGroupName);
            QPair<CTile *, CTile *> items;

            if(bistableGroups.contains(bistableGroup)) {
                items = bistableGroups.value(bistableGroup);
            }

            if(tiles[i]->bistableFirst) {
                items.first = tile;
            }else {
                items.second = tile;
            }

            bistableGroups.insert(bistableGroup, items);
        }
    }
}
//----------------------------------------------------------------------------
