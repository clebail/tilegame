//----------------------------------------------------------------------------
#include <QKeyEvent>
#include <QtDebug>
#include <common.h>
#include "CDialogSimulate.h"
//----------------------------------------------------------------------------
CDialogSimulate::CDialogSimulate(QWidget *parent, CWidgetSimulate *wSimulate) :QDialog(parent) {
    setupUi(this);

    resize(GAME_WIDTH + layout()->margin() * 2, GAME_HEIGHT + layout()->margin() * 2);

    this->wSimulate = wSimulate;
    if(wSimulate != 0) {
        this->layout()->addWidget(wSimulate);
    }

    timer = new QTimer(this);
    timer->setInterval(40);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    timer->start();

    qApp->installEventFilter(this);
}
//----------------------------------------------------------------------------
CDialogSimulate::~CDialogSimulate(void) {
    delete timer;
}
//----------------------------------------------------------------------------
void CDialogSimulate::setLevel(CLevel *level) {
    if(wSimulate != 0) {
        wSimulate->setLevel(level);
    }
}
//----------------------------------------------------------------------------
void CDialogSimulate::setTiles(CTiles *tiles) {
    if(wSimulate != 0) {
        wSimulate->setTiles(tiles);
    }
}
//----------------------------------------------------------------------------
void CDialogSimulate::setTilesImage(QImage *tilesImage) {
    if(wSimulate != 0) {
        wSimulate->setTilesImage(tilesImage);
    }
}
//----------------------------------------------------------------------------
bool CDialogSimulate::eventFilter(QObject *object, QEvent *event) {
    if(wSimulate != 0) {
        if(event->type() == QEvent::KeyPress && !object->inherits("QLineEdit")) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

            switch(keyEvent->key()) {
            case Qt::Key_Up:
                wSimulate->decY();
                return true;
            case Qt::Key_Right:
                wSimulate->incX();
                return true;
            case Qt::Key_Down:
                wSimulate->incY();
                return true;
            case Qt::Key_Left:
                wSimulate->decX();
                return true;
            default:
                break;
            }
        }
    }

    return QObject::eventFilter(object, event);
}
//----------------------------------------------------------------------------
void CDialogSimulate::timeout(void) {
    if(wSimulate != 0) {
        wSimulate->updateAnimate();
        wSimulate->update();
    }
}
//----------------------------------------------------------------------------
