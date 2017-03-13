//----------------------------------------------------------------------------
#ifndef __CTILE_H__
#define __CTILE_H__
//----------------------------------------------------------------------------
#include <QDataStream>
//----------------------------------------------------------------------------
class CTile {
private:
    friend QDataStream& operator<<(QDataStream& out, const CTile& tile);
    friend QDataStream& operator>>(QDataStream& in, CTile& tile);
public:
    bool solidUp, solidRight, solidDown, solidLeft;
    bool animated;
    bool bistable;
    bool breakable;
    bool touchBonus, hitBonus;
    bool dangerous;
    QString animatedGroupName;
    QString bistableGroupName;
};
//-----------------------------------------------------------------------------------------------
QDataStream& operator<<(QDataStream& out, const CTile& tile);
QDataStream& operator>>(QDataStream& in, CTile& tile);
//----------------------------------------------------------------------------
#endif //__CTILE_H__
//----------------------------------------------------------------------------
