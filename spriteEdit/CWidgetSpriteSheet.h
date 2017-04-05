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
protected:
    virtual void paintEvent(QPaintEvent *event);
private:
    QImage image;
    int zoomScale;
};
//----------------------------------------------------------------------------
#endif // __CWIDGETSPRITESHEET_H__
//----------------------------------------------------------------------------
