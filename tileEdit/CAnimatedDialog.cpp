//----------------------------------------------------------------------------
#include "CAnimateDialog.h"
//----------------------------------------------------------------------------
CAnimateDialog::CAnimateDialog(QWidget *parent) : QDialog(parent) {
    setupUi(this);

    tiles = QList<CTile *>();
    curTile = 0;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
}
//----------------------------------------------------------------------------
void CAnimateDialog::setImage(QImage *image) {
    tileImage->setImage(image);
}
//----------------------------------------------------------------------------
void CAnimateDialog::setTiles(const QList<CTile *>& tiles) {
    this->tiles = tiles;
}
//----------------------------------------------------------------------------
void CAnimateDialog::timeout(void) {
    if(tileImage->getImage() != 0 && tiles.size() != 0) {
        if(curTile >= tiles.size()) {
            curTile = 0;
        }

        CTile *tile = tiles.at(curTile);
        tileImage->setXY(tile->getX(), tile->getY());

        curTile++;
    }
}
//----------------------------------------------------------------------------
void CAnimateDialog::on_pbPlay_clicked(void) {
    timer->start(42);
}
//----------------------------------------------------------------------------
void CAnimateDialog::on_pbStop_clicked(void) {
    timer->stop();
}
//----------------------------------------------------------------------------
