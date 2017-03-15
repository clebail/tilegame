//----------------------------------------------------------------------------
#include <QtDebug>
#include <QScrollBar>
#include "CTileSetDialog.h"
//----------------------------------------------------------------------------
CTileSetDialog::CTileSetDialog(QImage *image, QWidget *parent) : QDialog(parent) {
    setupUi(this);

    setModal(false);
    setWindowFlags(Qt::FramelessWindowHint);

    tileSetWidget = new CTileSetWidget(image, this);
    scrollArea->setWidget(tileSetWidget);
}
//----------------------------------------------------------------------------
CTileSetDialog::~CTileSetDialog() {
}
//----------------------------------------------------------------------------
void CTileSetDialog::setXY(int x, int y) {
    tileSetWidget->setXY(x, y);
}
//----------------------------------------------------------------------------
