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
    void setXY(int x, int y);
private:
    QImage *image;
    int x, y;
protected:
    virtual void paintEvent(QPaintEvent *event);
};
//----------------------------------------------------------------------------
#endif //__CWIDGETTILE_H__
//----------------------------------------------------------------------------
