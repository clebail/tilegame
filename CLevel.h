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
    explicit CLevel(void);
    ~CLevel(void);
    void setPlayerStartPos(int x, int y);
    QPoint getPlayerStartPos(void);
    void toggleMonsterStartPoss(int x, int y);
    QList<QPoint> getMonsterStartPoss(void);
    void clear(void);
    void addLayer(void);
    void create(void);
    int getNbLayer(void);
    CTileMap * getLayer(int index);
    bool deleteLayer(int index);
    void layerUp(int index);
    void layerDown(int index);
    QString getMusicName(void);
    void setMusicName(QString musicName);
    QByteArray getMusic(void);
    void setMusic(const QByteArray& music);
    void load(QString fileName);
    void save(QString fileName);
private:
    QList<CTileMap *> layers;
    QPoint playerStartPos;
    QList<QPoint> monsterStartPoss;
    QString musicName;
    QByteArray music;


    friend QDataStream& operator<<(QDataStream& out, const CLevel& level);
    friend QDataStream& operator>>(QDataStream& in, CLevel& level);
};
//----------------------------------------------------------------------------
#endif //__CLEVEL_H__
//----------------------------------------------------------------------------
