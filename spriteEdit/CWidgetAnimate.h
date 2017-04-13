//----------------------------------------------------------------------------
#ifndef __CWIDGETANIMATE_H__
#define __CWIDGETANIMATE_H__
//----------------------------------------------------------------------------
#include <QWidget>
#include <CSprite.h>
//----------------------------------------------------------------------------
class CWidgetAnimate : public QWidget {
    Q_OBJECT
public:
    explicit CWidgetAnimate(QWidget *parent = 0);
    void setData(CSprite *sprite, int motionIndex);
    void updateFrame(void);
protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent * event);
private:
    QImage backImage, image;
    QRect rect;
    CSprite *sprite;
    int x, y;
    double coef;
    int motionIndex, currentFrame;

    void updateMetrics(void);
    void updateFrameMetrics(void);
};
//----------------------------------------------------------------------------
#endif // __CWIDGETANIMATE_H__
//----------------------------------------------------------------------------
