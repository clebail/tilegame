//----------------------------------------------------------------------------
#include <QtDebug>
#include <QPainter>
#include "CTileSetWidget.h"
//----------------------------------------------------------------------------
CTileSetWidget::CTileSetWidget(QImage *image, QWidget *parent) : QWidget(parent) {
    setupUi(this);

    resize(image->size());
    this->image = image;
}
//----------------------------------------------------------------------------
CTileSetWidget::~CTileSetWidget() {
}
//----------------------------------------------------------------------------
void CTileSetWidget::paintEvent(QPaintEvent *) {
    if(image) {
        QPainter painter(this);

        painter.drawImage(QPoint(0, 0), *image);
    }
}
//----------------------------------------------------------------------------
