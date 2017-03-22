//----------------------------------------------------------------------------
#include <QtDebug>
#include "CAnimatedDialog.h"
//----------------------------------------------------------------------------
CAnimatedDialog::CAnimatedDialog(QWidget *parent) : QDialog(parent) {
    setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
}
//----------------------------------------------------------------------------
void CAnimatedDialog::setImage(QImage *image) {
    tileImage->setImage(image);
}
//----------------------------------------------------------------------------
void CAnimatedDialog::setTilesGroup(CTilesGroup *group) {
    this->group = group;
    if(group != 0) {
        CTile *tile;

        tile = group->getCurrentTile();

        tileImage->setXY(tile->getX(), tile->getY());
    }
}
//----------------------------------------------------------------------------
void CAnimatedDialog::timeout(void) {
    if(tileImage->getImage() != 0 && group != 0) {
        CTile *tile;

        group->next();
        tile = group->getCurrentTile();

        tileImage->setXY(tile->getX(), tile->getY());
    }
}
//----------------------------------------------------------------------------
void CAnimatedDialog::on_pbPlay_clicked(void) {
    timer->start(42);
}
//----------------------------------------------------------------------------
void CAnimatedDialog::on_pbStop_clicked(void) {
    timer->stop();
    if(group) {
        group->reset();
    }
}
//----------------------------------------------------------------------------
