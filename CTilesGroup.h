//----------------------------------------------------------------------------
#ifndef __CTILESGROUP_H__
#define __CTILESGROUP_H__
//----------------------------------------------------------------------------
#include <QString>
#include <QList>
#include <CTile.h>
//----------------------------------------------------------------------------
class CTilesGroup {
public:
    explicit CTilesGroup(QString name);
    QString getName(void);
    void addTile(CTile *tile);
    void next(void);
    void reset(void);
    CTile * getCurrentTile(void);
private:
    QString name;
    QList<CTile *> tiles;
    int currentTileIndex;
    int currentTime;
};
//----------------------------------------------------------------------------
#endif // __CTILESGROUP_H__
//----------------------------------------------------------------------------
