//----------------------------------------------------------------------------
#ifndef __CWIDGETSPRITESHEET_H__
#define __CWIDGETSPRITESHEET_H__
//----------------------------------------------------------------------------
#include <QWidget>
#include "ui_CWidgetSpriteSheet.h"
//----------------------------------------------------------------------------
class CWidgetSpriteSheet : public QWidget, private Ui::CWidgetSpriteSheet {
    Q_OBJECT
public:
    explicit CWidgetSpriteSheet(QWidget *parent = 0);
    void loadImage(QString fileName);
    void incZoomScale(void);
    void decZoomScale(void);
    int getZoomScale(void);
    QImage getImage(void);
protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
private:
    QImage image, backImage;
    int zoomScale;
    bool mousePress;
    QPoint mouseOrigin, currentMousePos;

    int getMinX(const QPoint& topLeft, const QPoint& bottomRight);
    int getMaxX(const QPoint& topLeft, const QPoint& bottomRight);
    int getMinY(const QPoint& topLeft, const QPoint& bottomRight);
    int getMaxY(const QPoint& topLeft, const QPoint& bottomRight);
signals:
    void capture(const QPoint& topLeft, const QPoint& bottomRight);
};
//----------------------------------------------------------------------------
#endif // __CWIDGETSPRITESHEET_H__
//----------------------------------------------------------------------------
