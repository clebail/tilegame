//----------------------------------------------------------------------------
#ifndef __CWIDGETGAMEPLAY_H__
#define __CWIDGETGAMEPLAY_H__
//----------------------------------------------------------------------------
#include <QWidget>
#include <QPainter>
#include <CTileMap.h>
//----------------------------------------------------------------------------
class CWidgetGamePlay : public QWidget {
    Q_OBJECT
public:
    explicit CWidgetGamePlay(QWidget *parent = 0);
    void setXY(int x, int y);
    void setTilesImage(QImage *tilesImage);
    void setTileMap(CTileMap *tileMap);
    QPoint getViewPortCoords(void);
protected:
    virtual void paintEvent(QPaintEvent *event);
private:
    int x, y;
    int viewPortX, viewPortY;
    int xTileMax;
    QImage backImage;
    QImage *tilesImage;
    CTileMap *tileMap;

    void drawBackground(QPainter *painter);
    void drawMap(QPainter *painter);
signals:
    void viewPortChange(const QPoint& point);
};
//----------------------------------------------------------------------------
#endif //__CWIDGETGAMEPLAY_H__
//----------------------------------------------------------------------------
