//----------------------------------------------------------------------------
#include "CTileGame.h"
//----------------------------------------------------------------------------
QDataStream& operator<<(QDataStream& out, const CTileGame& tileGame) {
    if(tileGame.tileIndex != 0) {
        out << QString::number(*tileGame.tileIndex);
    }else {
        out << QString("N");
    }

    out << tileGame.score;
    out << (int)tileGame.bonusType;

    return out;
}
//-----------------------------------------------------------------------------------------------
QDataStream& operator>>(QDataStream& in, CTileGame& tileGame) {
    QString s;
    int bt;

    in >> s;

    if(s != "N") {
        tileGame.tileIndex = new int;
        *tileGame.tileIndex = s.toInt();
    }else {
        tileGame.tileIndex = 0;
    }

    in >> tileGame.score;
    in >> bt;

    tileGame.bonusType = (CTileGame::EBonusType)bt;

    return in;
}
//-----------------------------------------------------------------------------------------------
CTileGame::CTileGame(void) {
    tileIndex = 0;
    score = 0;
    bonusType = ebtNone;
}
//----------------------------------------------------------------------------
