//----------------------------------------------------------------------------
#ifndef CTILESETWIDGET_H
#define CTILESETWIDGET_H
//----------------------------------------------------------------------------
#include <QWidget>
#include "ui_CTileSetWidget.h"
//----------------------------------------------------------------------------
class CTileSetWidget : public QWidget, private Ui::CTileSetWidget {
    Q_OBJECT
public:
    explicit CTileSetWidget(QImage *image, QWidget *parent = 0);
    ~CTileSetWidget();
protected:
    virtual void paintEvent(QPaintEvent *event);
private:
    QImage *image;
};
//----------------------------------------------------------------------------
#endif // CTILESETWIDGET_H
//----------------------------------------------------------------------------
