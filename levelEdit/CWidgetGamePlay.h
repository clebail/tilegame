//----------------------------------------------------------------------------
#ifndef __CWIDGETGAMEPLAY_H__
#define __CWIDGETGAMEPLAY_H__
//----------------------------------------------------------------------------
#include <QWidget>
#include <QPainter>
//----------------------------------------------------------------------------
class CWidgetGamePlay : public QWidget {
    Q_OBJECT
public:
    explicit CWidgetGamePlay(QWidget *parent = 0);
    void setXY(int x, int y);
protected:
    virtual void paintEvent(QPaintEvent *event);
private:
    int x, y;
    QImage backImage;

    void drawBackground(QPainter *painter);
private slots:
    void on_pbAdd_clicked(void);
};
//----------------------------------------------------------------------------
#endif //__CWIDGETGAMEPLAY_H__
//----------------------------------------------------------------------------
