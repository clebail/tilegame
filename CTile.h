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
    explicit CTile(int x, int y);
    bool solidUp, solidRight, solidDown, solidLeft;
    bool animated;
    bool bistable;
    bool breakable;
    bool touchBonus, hitBonus;
    bool dangerous;
    QString animatedGroupName;
    QString bistableGroupName;

    int getX(void);
    int getY(void);

    static QString getGroup(QString str);
    static QString getElement(QString str, int n);
private:
    int x, y;
};
//-----------------------------------------------------------------------------------------------
QDataStream& operator<<(QDataStream& out, const CTile& tile);
QDataStream& operator>>(QDataStream& in, CTile& tile);
//----------------------------------------------------------------------------
#endif //__CTILE_H__
//----------------------------------------------------------------------------
