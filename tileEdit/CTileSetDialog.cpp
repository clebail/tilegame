//----------------------------------------------------------------------------
#include <QtDebug>
#include <QScrollBar>
#include <common.h>
#include "CTileSetDialog.h"
//----------------------------------------------------------------------------
CTileSetDialog::CTileSetDialog(QImage *image, QWidget *parent) : QDialog(parent) {
    setupUi(this);

    setModal(false);
    setWindowFlags(Qt::FramelessWindowHint);

    tileSetWidget = new CTileSetWidget(image, this);
    connect(tileSetWidget, SIGNAL(mousePress(int,int)), this, SLOT(onMousePress(int,int)));
    scrollArea->setWidget(tileSetWidget);
}
//----------------------------------------------------------------------------
CTileSetDialog::~CTileSetDialog() {
}
//----------------------------------------------------------------------------
void CTileSetDialog::setXY(int x, int y) {
    tileSetWidget->setXY(x, y);
    scrollArea->ensureVisible(x * (REAL_TILE_WIDTH) + OFFSET_X, y * (REAL_TILE_HEIGHT) + OFFSET_Y);
}
//----------------------------------------------------------------------------
void CTileSetDialog::onMousePress(const int& x ,const int& y) {
    emit(mousePress(x, y));
}
//----------------------------------------------------------------------------
