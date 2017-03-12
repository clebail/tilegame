//----------------------------------------------------------------------------
#ifndef __CWIDGETTILE_H__
#define __CWIDGETTILE_H__
//----------------------------------------------------------------------------
#include <QWidget>
//----------------------------------------------------------------------------
class CWidgetTile : public QWidget {
public:
    explicit CWidgetTile(QWidget *parent = 0);
    void setImage(QImage *image);
    void incX(void);
    void decX(void);
    void incY(void);
    void decY(void);
    int getX(void) { return x; }
    int getY(void) { return y; }
    int getXMax(void) { return maxX; }
    int getYMax(void) { return maxY; }
private:
    QImage *image;
    int x, y;
    int maxX, maxY;
protected:
    virtual void paintEvent(QPaintEvent *event);
};
//----------------------------------------------------------------------------
#endif //__CWIDGETTILE_H__
//----------------------------------------------------------------------------
