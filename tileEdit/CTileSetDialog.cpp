//----------------------------------------------------------------------------
#include <QtDebug>
#include <QScrollBar>
#include "CTileSetDialog.h"
//----------------------------------------------------------------------------
CTileSetDialog::CTileSetDialog(QImage *image, QWidget *parent) : QDialog(parent) {
    setupUi(this);

    setModal(false);
    setWindowFlags(Qt::FramelessWindowHint);

    scrollArea->setWidget(new CTileSetWidget(image, this));
}
//----------------------------------------------------------------------------
CTileSetDialog::~CTileSetDialog() {
}
//----------------------------------------------------------------------------
