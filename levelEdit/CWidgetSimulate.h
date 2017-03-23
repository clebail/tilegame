//----------------------------------------------------------------------------
#ifndef __CWIDGETSIMULATE_H__
#define __CWIDGETSIMULATE_H__
//----------------------------------------------------------------------------
#include <QWidget>
#include <QPainter>
#include <CTileMap.h>
#include <CTiles.h>
//----------------------------------------------------------------------------
class CWidgetSimulate : public QWidget {
    Q_OBJECT
public:
    explicit CWidgetSimulate(QWidget *parent = 0);
    ~CWidgetSimulate(void);
    void setTileMaps(CTileMap *front, CTileMap *back);
    void setTiles(CTiles *tiles);
    void setTilesImage(QImage *tilesImage);
    void incX(void);
    void incY(void);
    void decX(void);
    void decY(void);
    void updateAnimate(void);
protected:
    virtual void paintEvent(QPaintEvent *event);
private:
    CTileMap *front;
    CTileMap *back;
    CTiles *tiles;
    QImage *tilesImage;
    QHash<QString, CTilesGroup *> groups;
    int xFront, yFront, xBack, yBack;

    void drawTiles(QPainter *painter, CTileMap *tileMap, int curX, int curY);
};
//----------------------------------------------------------------------------
#endif // __CWIDGETSIMULATE_H__
//----------------------------------------------------------------------------
