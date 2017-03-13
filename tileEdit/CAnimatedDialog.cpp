//----------------------------------------------------------------------------
#include "CAnimateDialog.h"
//----------------------------------------------------------------------------
CAnimateDialog::CAnimateDialog(QWidget *parent) : QDialog(parent) {
    setupUi(this);

    coords = QList<QPoint>();
    image = 0;
    curCoord = 0;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
}
//----------------------------------------------------------------------------
void CAnimateDialog::setImage(QImage *image) {
    this->image = image;
}
//----------------------------------------------------------------------------
void CAnimateDialog::setCoords(const QList<QPoint>& coords) {
    this->coords = coords;
}
//----------------------------------------------------------------------------
void CAnimateDialog::timeout(void) {
    if(image != 0 && coords.size() != 0) {
        if(curCoord >= coords.size()) {
            curCoord = 0;
        }

        QPoint p = coords.at(curCoord);
        tileImage->setXY(p.x(), p.y());

        curCoord++;
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
