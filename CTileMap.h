//----------------------------------------------------------------------------
#ifndef __CTILEMAP_H__
#define __CTILEMAP_H__
//----------------------------------------------------------------------------
#include <QDataStream>
#include <QList>
#include <QSize>
#include <QPoint>
#include <CTileGame.h>
//----------------------------------------------------------------------------
class CTileMap : public QObject {
    Q_OBJECT
public:
    CTileMap(void);
    ~CTileMap(void);
    void add(int x, int y, int tileIndex);
    void remove(int x, int y);
    int getTileCount(void);
    int * getTileIndex(int x, int y);
    CTileGame getTile(int x, int y);
    void setTile(const CTileGame& tile, int x, int y);
    QSize getSize(void);
    void clear(void);
    void setOrigin(const QPoint& p);
    QPoint getOrigin(void);
    void insertRow(int y);
    void insertColumn(int x);
private:
    int xMax, yMax;
    QList<CTileGame> map;
    QPoint origin;

    void addToMap(int nb);
    void reorderMap(int newXMax);
    friend QDataStream& operator<<(QDataStream& out, const CTileMap& tileMap);
    friend QDataStream& operator>>(QDataStream& in, CTileMap& tileMap);
signals:
    void mapResize(const QSize& size);
};
//----------------------------------------------------------------------------
#endif //__CTILEMAP_H__
//----------------------------------------------------------------------------
