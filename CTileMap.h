//----------------------------------------------------------------------------
#ifndef __CTILEMAP_H__
#define __CTILEMAP_H__
//----------------------------------------------------------------------------
#include <QDataStream>
#include <QList>
#include <QSize>
//----------------------------------------------------------------------------
class CTileMap : public QObject {
    Q_OBJECT
public:
    CTileMap(void);
    ~CTileMap(void);
    void add(int x, int y, int tileIndex);
    void remove(int x, int y);
    int getTileCount(void);
    int * getTile(int x, int y);
    QSize getSize(void);
private:
    int xMax, yMax;
    QList<int *> map;

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
