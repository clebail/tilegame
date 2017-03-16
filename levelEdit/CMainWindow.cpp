//----------------------------------------------------------------------------
#include <QtDebug>
#include <QKeyEvent>
#include "CMainWindow.h"
//----------------------------------------------------------------------------
CMainWindow::CMainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi(this);

    x = y = 0;

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
            y--;
            setXY();
            return true;
        case Qt::Key_Right:
            x++;
            setXY();
            return true;
        case Qt::Key_Down:
            y++;
            setXY();
            return true;
        case Qt::Key_Left:
            x--;
            setXY();
            return true;
        default:
            break;
        }
    }

    return QObject::eventFilter(object, event);
}
//----------------------------------------------------------------------------
void CMainWindow::setXY(void) {
    wGamePlay->setXY(x, y);
}
//----------------------------------------------------------------------------
void CMainWindow::onTileSetWidgetMousePress(const int& x, const int &y) {
    tileSetWidget->setXY(x, y);
    tileWidget->setXY(x, y);
}
//----------------------------------------------------------------------------
