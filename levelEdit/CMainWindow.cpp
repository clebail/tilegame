//----------------------------------------------------------------------------
#include <QtDebug>
#include <QKeyEvent>
#include "CMainWindow.h"
//----------------------------------------------------------------------------
CMainWindow::CMainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi(this);

    tilesImage = QImage(":levelEdit/images/tileset.png");

    tileWidget->setImage(&tilesImage);

    tileSetWidget = new CTileSetWidget(&tilesImage, this);
    connect(tileSetWidget, SIGNAL(mousePress(int,int)), this, SLOT(onTileSetWidgetMousePress(int,int)));
    scrollArea->setWidget(tileSetWidget);

    qApp->installEventFilter(this);
}
//----------------------------------------------------------------------------
CMainWindow::~CMainWindow() {
    delete tileSetWidget;
}
//----------------------------------------------------------------------------
bool CMainWindow::eventFilter(QObject *object, QEvent *event) {
    if(event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        switch(keyEvent->key()) {
        case Qt::Key_Up:
            return true;
        case Qt::Key_Right:
            return true;
        case Qt::Key_Down:
            return true;
        case Qt::Key_Left:
            return true;
        default:
            break;
        }
    }

    return QObject::eventFilter(object, event);
}
//----------------------------------------------------------------------------
void CMainWindow::onTileSetWidgetMousePress(const int& x, const int &y) {
    tileSetWidget->setXY(x, y);
    tileWidget->setXY(x, y);
}
//----------------------------------------------------------------------------
