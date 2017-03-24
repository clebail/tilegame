//----------------------------------------------------------------------------
#ifndef __CWIDGETPREVIEW_H__
#define __CWIDGETPREVIEW_H__
//----------------------------------------------------------------------------
#include <QWidget>
#include "CTileMap.h"
//----------------------------------------------------------------------------
class CWidgetPreview : public QWidget {
    Q_OBJECT
public:
    explicit CWidgetPreview(QWidget *parent = 0);
    void setTilesImage(QImage *tilesImage);
    void setTileMap(CTileMap *tileMap);
    void setViewPort(int x, int y);
    void setOrigin(const QPoint& p);
    void setPlayerStartPos(int x, int y);
    void setPlayerStartPos(const QPoint& p );
protected:
    virtual void paintEvent(QPaintEvent *event);
private:
    QImage backImage;
    QImage *tilesImage;
    int xTileMax;
    CTileMap *tileMap;
    int viewPortX, viewPortY;
    QPoint origin;
    QPoint playerStartPos;
    QImage gentil, mechant;

    void drawBackground(QPainter *painter);
    void drawMap(QPainter *painter);
};
//----------------------------------------------------------------------------
#endif // __CWIDGETPREVIEW_H__
//----------------------------------------------------------------------------
