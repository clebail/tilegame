//----------------------------------------------------------------------------
#ifndef __CLEVEL_H__
#define __CLEVEL_H__
//----------------------------------------------------------------------------
#include <QPoint>
#include <QList>
#include <QDataStream>
#include <CTileMap.h>
//----------------------------------------------------------------------------
class CLevel {
public:
    explicit CLevel();
private:
    CTileMap front, back;
    QPoint playerStartPos;
    QList<QPoint> monsterStartPoss;

    friend QDataStream& operator<<(QDataStream& out, const CLevel& level);
    friend QDataStream& operator>>(QDataStream& in, CLevel& level);
};
//----------------------------------------------------------------------------
#endif //__CLEVEL_H__
//----------------------------------------------------------------------------
