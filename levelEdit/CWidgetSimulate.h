//----------------------------------------------------------------------------
#ifndef __CWIDGETSIMULATE_H__
#define __CWIDGETSIMULATE_H__
//----------------------------------------------------------------------------
#include <QWidget>
#include <QPainter>
#include <CLevel.h>
#include <CTiles.h>
//----------------------------------------------------------------------------
class CWidgetSimulate : public QWidget {
    Q_OBJECT
public:
    explicit CWidgetSimulate(QWidget *parent = 0);
    virtual ~CWidgetSimulate(void);
    void setLevel(CLevel *level);
    void setTiles(CTiles *tiles);
    virtual void setTilesImage(QImage *tilesImage);
    void incX(void);
    void incY(void);
    void decX(void);
    void decY(void);
    void updateAnimate(void);
protected:
    CLevel *level;
    CTileMap *front, *back;
    CTiles *tiles;
    QImage *tilesImage;
    QHash<QString, CTilesGroup *> groups;
    int xFront, yFront, xBack, yBack;
    QImage gentil, mechant;

    virtual void paintEvent(QPaintEvent *event);
private:
    void drawTiles(QPainter *painter, CTileMap *tileMap, int curX, int curY);
};
//----------------------------------------------------------------------------
#endif // __CWIDGETSIMULATE_H__
//----------------------------------------------------------------------------
