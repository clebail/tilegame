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
    CTileMap * getFront(void);
    CTileMap * getBack(void);
    void setPlayerStartPos(int x, int y);
    QPoint getPlayerStartPos(void);
    void toggleMonsterStartPoss(int x, int y);
    QList<QPoint> getMonsterStartPoss(void);
    void clear(void);
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
