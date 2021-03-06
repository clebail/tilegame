//----------------------------------------------------------------------------
#include <QStringList>
#include <QCryptographicHash>
#include <common.h>
#include <CTile.h>
//----------------------------------------------------------------------------
QDataStream& operator<<(QDataStream& out, const CTile& tile) {
    out << tile.solidUp;
    out << tile.solidRight;
    out << tile.solidDown;
    out << tile.solidLeft;
    out << tile.animated.active;
    out << tile.animated.groupName;
    out << tile.animated.count;
    out << tile.animated.positions;
    out << tile.climbing;
    out << tile.breakable;
    out << tile.touchBonus;
    out << tile.hitBonus;
    out << tile.dangerous;

    return out;
}
//-----------------------------------------------------------------------------------------------
QDataStream& operator>>(QDataStream& in, CTile& tile) {
    in >> tile.solidUp;
    in >> tile.solidRight;
    in >> tile.solidDown;
    in >> tile.solidLeft;
    in >> tile.animated.active;
    in >> tile.animated.groupName;
    in >> tile.animated.count;
    in >> tile.animated.positions;
    in >> tile.climbing;
    in >> tile.breakable;
    in >> tile.touchBonus;
    in >> tile.hitBonus;
    in >> tile.dangerous;

    return in;
}
//-----------------------------------------------------------------------------------------------
CTile::CTile(int x, int y) {
    this->x = x;
    this->y = y;

    realX = x * REAL_TILE_WIDTH + OFFSET_X;
    realY = y * REAL_TILE_HEIGHT + OFFSET_Y;

    this->hash = QCryptographicHash::hash((QString::number(x)+"_"+QString::number(y)).toAscii(), QCryptographicHash::Md5);

    solidUp = false;
    solidRight = false;
    solidDown = false;
    solidLeft = false;
    animated.active = false;
    animated.groupName = "";
    animated.count = 0;
    animated.positions = QList<int>();
    climbing = false;
    breakable = false;
    touchBonus = false;
    hitBonus = false;
    dangerous = false;

}
//----------------------------------------------------------------------------
int CTile::getX(void) {
    return x;
}
//----------------------------------------------------------------------------
int CTile::getY(void) {
    return y;
}
//----------------------------------------------------------------------------
int CTile::getRealX(void) {
    return realX;
}
//----------------------------------------------------------------------------
int CTile::getRealY(void) {
    return realY;
}
//----------------------------------------------------------------------------
void CTile::parseAnimated(QString str) {
    QStringList items = str.split(";");

    animated.groupName = items[0];
    animated.count = 0;
    animated.positions.clear();

    if(items.size() > 1) {
        animated.count = items[1].toInt();
        if(items.size() == 3) {
            QStringList pos = items[2].split(",");

            for(int i=0;i<pos.size();i++) {
                animated.positions.append(pos[i].toInt());
            }
        }
    }
}
//----------------------------------------------------------------------------
QString CTile::serializeAnimated(void) {
    QString ret = animated.groupName+";"+QString::number(animated.count)+";";
    QString s = "";

    for(int i=0;i<animated.positions.size();i++) {
        ret += s + QString::number(animated.positions.at(i));
        s = ",";
    }

    return ret;
}
//----------------------------------------------------------------------------
QString CTile::getHash(void) {
    return hash;
}
//----------------------------------------------------------------------------
QString CTile::getGroup(QString str) {
    return CTile::getElement(str, 0);
}
//-----------------------------------------------------------------------------------------------
QString CTile::getElement(QString str, int n) {
    QStringList items = str.split(";");

    if(n >= 0 && n < items.size()) {
        return items[n];
    }

    return "";
}
//-----------------------------------------------------------------------------------------------
