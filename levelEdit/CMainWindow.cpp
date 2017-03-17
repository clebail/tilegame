//----------------------------------------------------------------------------
#include <QtDebug>
#include <QKeyEvent>
#include <common.h>
#include "CMainWindow.h"
//----------------------------------------------------------------------------
CMainWindow::CMainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi(this);

    x = y = 0;
    currentTile = 0;

    tilesImage = QImage(":/levelEdit/images/tileset.png");

    xTileMax = (tilesImage.size().width() - 2 * OFFSET_X) / REAL_TILE_WIDTH;

    tileWidget->setImage(&tilesImage);

    wGamePlay->resize(GAME_WIDTH, GAME_HEIGHT);
    wGamePlay->setTilesImage(&tilesImage);
    wGamePlay->setTileMap(&map);

    tileSetWidget = new CTileSetWidget(&tilesImage, this);
    connect(tileSetWidget, SIGNAL(mousePress(int,int)), this, SLOT(onTileSetWidgetMousePress(int,int)));
    scrollArea->setWidget(tileSetWidget);

    lblCurrent.setFrameStyle(QFrame::Panel | QFrame::Sunken);;
    lblMax.setFrameStyle(QFrame::Panel | QFrame::Sunken);;

    Ui::CMainWindow::statusBar->addPermanentWidget(&lblCurrent);
    Ui::CMainWindow::statusBar->addPermanentWidget(&lblMax);

    onMapResize(QSize(0, 0));
    setXY();

    connect(&map, SIGNAL(mapResize(QSize)), this, SLOT(onMapResize(QSize)));

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
            if(y > 0) {
                y--;
                setXY();
            }
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
            if(x > 0) {
                x--;
                setXY();
            }
            return true;
        case Qt::Key_Plus:
            on_pbAdd_clicked();
            return true;
        case Qt::Key_Minus:
            on_pbDelete_clicked();
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

    lblUp->setEnabled(y >= GAME_NB_Y);
    lblLeft->setEnabled(x >= GAME_NB_X);

    lblCurrent.setText("Position in map : "+QString::number(x + 1)+", "+QString::number(y + 1));
}
//----------------------------------------------------------------------------
void CMainWindow::onTileSetWidgetMousePress(const int& x, const int &y) {
    tileSetWidget->setXY(x, y);
    tileWidget->setXY(x, y);

    currentTile = y * xTileMax + x;
}
//----------------------------------------------------------------------------
void CMainWindow::on_pbAdd_clicked(void) {
    map.add(x, y, currentTile);
    wGamePlay->update();
}
//----------------------------------------------------------------------------
void CMainWindow::on_pbDelete_clicked(void) {
    map.remove(x, y);
    wGamePlay->update();
}
//----------------------------------------------------------------------------
void CMainWindow::onMapResize(const QSize& size) {
    lblMax.setText("Map size : "+QString::number(size.width())+" x "+QString::number(size.height()));
}
//----------------------------------------------------------------------------
