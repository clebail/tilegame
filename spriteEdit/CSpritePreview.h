//----------------------------------------------------------------------------
#ifndef __CSPRITEPREVIEW_H__
#define __CSPRITEPREVIEW_H__
//----------------------------------------------------------------------------
#include <QWidget>
#include <CSprite.h>
//----------------------------------------------------------------------------
class CSpritePreview : public QWidget {
    Q_OBJECT
public:
    explicit CSpritePreview(QWidget *parent = 0);
    void setSprite(CSprite *sprite);
    void setCurrentMotion(CSprite::EMotion currentMotion);
    void setCurrentFrameIndex(int currentFrameIndex);
    void updateFrameRects(void);
protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
private:
    CSprite *sprite;
    CSprite::EMotion currentMotion;
    QImage backImage;
    int currentFrameIndex;
    QList<QRect> frameRects;
signals:
    void currentFrameChanged(int index);
};
//----------------------------------------------------------------------------
#endif // __CSPRITEPREVIEW_H__
//----------------------------------------------------------------------------
