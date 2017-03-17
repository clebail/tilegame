//----------------------------------------------------------------------------
#ifndef __CTILEMAP_H__
#define __CTILEMAP_H__
//----------------------------------------------------------------------------
#include <QList>
//----------------------------------------------------------------------------
class CTileMap {
public:
    CTileMap(void);
    ~CTileMap(void);
    void add(int x, int y, int tileIndex);
    void remove(int x, int y);
    int getTileCount(void);
    int * getTile(int x, int y);
private:
    int xMax, yMax;
    QList<int *> map;

    void addToMap(int nb);
    void reorderMap(int newXMax);
};
//----------------------------------------------------------------------------
#endif //__CTILEMAP_H__
//----------------------------------------------------------------------------
