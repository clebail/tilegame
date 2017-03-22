//----------------------------------------------------------------------------
#ifndef __CWIDGETSIMULATE_H__
#define __CWIDGETSIMULATE_H__
//----------------------------------------------------------------------------
#include <QWidget>
#include <CTileMap.h>
#include <CTiles.h>
//----------------------------------------------------------------------------
class CWidgetSimulate : public QWidget {
    Q_OBJECT
public:
    explicit CWidgetSimulate(QWidget *parent = 0);
    void setTileMaps(CTileMap *front, CTileMap *back);
    void setTiles(CTiles *tiles);
    void setTilesImage(QImage *tilesImage);
private:
    CTileMap *front;
    CTileMap *back;
    CTiles *tiles;
    QImage *tilesImage;
};
//----------------------------------------------------------------------------
#endif // __CWIDGETSIMULATE_H__
//----------------------------------------------------------------------------
