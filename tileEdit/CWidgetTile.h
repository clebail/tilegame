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
