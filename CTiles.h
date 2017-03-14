//----------------------------------------------------------------------------
#ifndef __CTILES_H__
#define __CTILES_H__
//----------------------------------------------------------------------------
#include <QPair>
#include <QHash>
#include <CTile.h>
//----------------------------------------------------------------------------
class CTiles {
public:
    explicit CTiles(int maxX, int maxY);
    ~CTiles(void);
    void load(QString fileName);
    void save(QString fileName);
    QString getFileName(void);
    QList<CTile *> getAnimatedGroup(QString groupName);
    QPair<CTile *, CTile *> getBistableGroup(QString groupName);
    CTile * getTile(int idx);
private:
    typedef CTile * PCTile;

    int tileCount;
    QString filename;
    PCTile *tiles;
};
//----------------------------------------------------------------------------
#endif //__CTILES_H__
//----------------------------------------------------------------------------
