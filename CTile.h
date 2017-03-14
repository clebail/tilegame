//----------------------------------------------------------------------------
#ifndef __CTILE_H__
#define __CTILE_H__
//----------------------------------------------------------------------------
#include <QDataStream>
#include <QList>
//----------------------------------------------------------------------------
class CTile {
private:
    friend QDataStream& operator<<(QDataStream& out, const CTile& tile);
    friend QDataStream& operator>>(QDataStream& in, CTile& tile);
public:
    explicit CTile(int x, int y);
    bool solidUp, solidRight, solidDown, solidLeft;
    struct {
        bool active;
        QString groupName;
        int animactedCount;
        QList<int> positions;
    } animated;
    bool bistable;
    bool breakable;
    bool touchBonus, hitBonus;
    bool dangerous;
    QString bistableGroupName;

    int getX(void);
    int getY(void);
    void parseAnimated(QString str);
    QString serializeAnimated(void);

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
