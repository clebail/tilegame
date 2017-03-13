//----------------------------------------------------------------------------
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
    out << tile.bonus;
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
    in >> tile.bonus;
    in >> tile.dangerous;
    in >> tile.animatedGroupName;
    in >> tile.bistableGroupName;

    return in;
}
//-----------------------------------------------------------------------------------------------
