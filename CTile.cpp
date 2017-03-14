//----------------------------------------------------------------------------
#include <QStringList>
#include "CTile.h"
//----------------------------------------------------------------------------
QDataStream& operator<<(QDataStream& out, const CTile& tile) {
    out << tile.solidUp;
    out << tile.solidRight;
    out << tile.solidDown;
    out << tile.solidLeft;
    out << tile.animated;
    out << tile.bistable;
    out << tile.breakable;
    out << tile.touchBonus;
    out << tile.hitBonus;
    out << tile.dangerous;
    out << tile.animatedGroupName;
    out << tile.bistableGroupName;

    return out;
}
//-----------------------------------------------------------------------------------------------
QDataStream& operator>>(QDataStream& in, CTile& tile) {
   in >> tile.solidUp;
    in >> tile.solidRight;
    in >> tile.solidDown;
    in >> tile.solidLeft;
    in >> tile.animated;
    in >> tile.bistable;
    in >> tile.breakable;
    in >> tile.touchBonus;
    in >> tile.hitBonus;
    in >> tile.dangerous;
    in >> tile.animatedGroupName;
    in >> tile.bistableGroupName;

    return in;
}
//-----------------------------------------------------------------------------------------------
QString CTile::getGroup(QString str) {
    return CTile::getElement(str, 0);
}
//-----------------------------------------------------------------------------------------------
QString CTile::getElement(QString str, int n) {
    QStringList items = str.split(";");

    return items[n];
}
//-----------------------------------------------------------------------------------------------
