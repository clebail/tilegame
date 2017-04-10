//----------------------------------------------------------------------------
#ifndef __CSPRITEFRAMEWIDGET_H__
#define __CSPRITEFRAMEWIDGET_H__
//----------------------------------------------------------------------------
#include <QWidget>
//----------------------------------------------------------------------------
class CSpriteFrameWidget : public QWidget {
    Q_OBJECT
public:
    explicit CSpriteFrameWidget(QWidget *parent = 0);
    void setImage(const QImage &image);
protected:
    virtual void paintEvent(QPaintEvent *event);
private:
    QImage image, backImage;
};
//----------------------------------------------------------------------------
#endif // __CSPRITEFRAMEWIDGET_H__
//----------------------------------------------------------------------------
