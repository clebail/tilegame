//----------------------------------------------------------------------------
#include "CLevel.h"
//----------------------------------------------------------------------------
CLevel::CLevel(void) {
    addLayer();
}
//----------------------------------------------------------------------------
CLevel::~CLevel(void) {
    clear();
}
//----------------------------------------------------------------------------
CTileMap * CLevel::getFront(void) {
    return layers.at(0);
}
//----------------------------------------------------------------------------
CTileMap * CLevel::getBack(void) {
    return layers.at(1);
}
//----------------------------------------------------------------------------
void CLevel::setPlayerStartPos(int x, int y) {
    playerStartPos = QPoint(x, y);
}
//----------------------------------------------------------------------------
QPoint CLevel::getPlayerStartPos(void) {
    return playerStartPos;
}
//----------------------------------------------------------------------------
void CLevel::toggleMonsterStartPoss(int x, int y) {
    int i;

    i=0;
    while(i<monsterStartPoss.size()) {
        QPoint p = monsterStartPoss.at(i);

        if(x == p.x() && y == p.y()) {
            monsterStartPoss.removeAt(i);
            return;
        }

        i++;
    }

    monsterStartPoss.append(QPoint(x, y));
}
//----------------------------------------------------------------------------
QList<QPoint> CLevel::getMonsterStartPoss(void) {
    return monsterStartPoss;
}
//----------------------------------------------------------------------------
void CLevel::clear(void) {
    playerStartPos = QPoint();
    monsterStartPoss = QList<QPoint>();

    while(layers.size()) {
        delete layers.takeAt(0);
    }
}
//----------------------------------------------------------------------------
void CLevel::addLayer(void) {
     CTileMap *tm = new CTileMap();

     layers.append(tm);
}
//----------------------------------------------------------------------------
void CLevel::create(void) {
    clear();
    addLayer();
}
//----------------------------------------------------------------------------
int CLevel::getNbLayer(void) {
    return layers.size();
}
//----------------------------------------------------------------------------
CTileMap * CLevel::getLayer(int index) {
    if(index >=0 && index < layers.size()) {
        return layers.at(index);
    }

    return 0;
}
//----------------------------------------------------------------------------
bool CLevel::deleteLayer(int index) {
    if(index >=0 && index < layers.size()) {
        layers.removeAt(index);

        if(index == 0) {
            playerStartPos = QPoint();
            monsterStartPoss.clear();
        }

        return true;
    }

    return false;
}
//----------------------------------------------------------------------------
void CLevel::layerUp(int index) {
    layers.swap(index, index - 1);
}
//----------------------------------------------------------------------------
void CLevel::layerDown(int index) {
    layers.swap(index, index + 1);
}
//----------------------------------------------------------------------------
QDataStream& operator<<(QDataStream& out, const CLevel& level) {
	int i;

    out << level.playerStartPos;
    out << level.monsterStartPoss.size();
    for(i=0;i<level.monsterStartPoss.size();i++) {
    	out << level.monsterStartPoss.at(i);
   	}
    out << level.layers.size();
    for(i=0;i<level.layers.size();i++) {
        CTileMap *tm = level.layers.at(i);
        out << *tm;
    }

    return out;
}
//-----------------------------------------------------------------------------------------------
QDataStream& operator>>(QDataStream& in, CLevel& level) {
    int nbMonster, nbLayer, i;

    in >> level.playerStartPos;
    in >> nbMonster;
    for(i=0;i<nbMonster;i++) {
    	QPoint mp;
    
    	in >> mp;
    	level.monsterStartPoss.append(mp);
    }
    in >> nbLayer;
    for(i=0;i<nbLayer;i++) {
        CTileMap *tm = new CTileMap();

        in >> *tm;
        level.layers.append(tm);
    }

    return in;
}
//-----------------------------------------------------------------------------------------------
