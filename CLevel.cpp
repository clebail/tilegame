//----------------------------------------------------------------------------
#include "CLevel.h"
//----------------------------------------------------------------------------
CLevel::CLevel() {
}
//----------------------------------------------------------------------------
CTileMap * CLevel::getFront(void) {
    return &front;
}
//----------------------------------------------------------------------------
CTileMap * CLevel::getBack(void) {
    return &back;
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
QDataStream& operator<<(QDataStream& out, const CLevel& level) {
	int i;

    out << level.playerStartPos;
    out << level.monsterStartPoss.size();
    for(i=0;i<level.monsterStartPoss.size();i++) {
    	out << level.monsterStartPoss.at(i);
   	}
    out << level.front;
    out << level.back;

    return out;
}
//-----------------------------------------------------------------------------------------------
QDataStream& operator>>(QDataStream& in, CLevel& level) {
	int nbMonster, i;

    in >> level.playerStartPos;
    in >> nbMonster;
    for(i=0;i<nbMonster;i++) {
    	QPoint mp;
    
    	in >> mp;
    	level.monsterStartPoss.append(mp);
    }
    in >> level.front;
    in >> level.back;

    return in;
}
//-----------------------------------------------------------------------------------------------
