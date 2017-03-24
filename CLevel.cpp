//----------------------------------------------------------------------------
#include "CLevel.h"
//----------------------------------------------------------------------------
CLevel::CLevel() {
}
//----------------------------------------------------------------------------
QDataStream& operator<<(QDataStream& out, const CLevel& level) {
    out << level.playerStartPos;
    out << level.monsterStartPoss;
    out << level.front;
    out << level.back;

    return out;
}
//-----------------------------------------------------------------------------------------------
QDataStream& operator>>(QDataStream& in, CLevel& level) {
    in >> level.playerStartPos;
    in >> level.monsterStartPoss;
    in >> level.front;
    in >> level.back;

    return in;
}
//-----------------------------------------------------------------------------------------------
