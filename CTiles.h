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
    void computeGroups(void);
private:
    class CItem {
    public:
        CTile *tile;
        int animatedPosition;
        int animatedCount;
        bool bistableFirst;
    };

    typedef CItem * PCItem;

    int tileCount;
    QString filename;
    PCItem *tiles;
    QHash<QString, QList<CItem *> > animatedGroups;
    QHash<QString, QPair<CTile *, CTile *> > bistableGroups;
};
//----------------------------------------------------------------------------
#endif //__CTILES_H__
//----------------------------------------------------------------------------
