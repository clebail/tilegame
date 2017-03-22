//----------------------------------------------------------------------------
#include <QtDebug>
#include <QKeyEvent>
#include <QFileDialog>
#include <common.h>
#include "CMainWindow.h"
//----------------------------------------------------------------------------
CMainWindow::CMainWindow(QWidget *parent) : QMainWindow(parent) {
    int yTileMax;

    setupUi(this);

    x = y = 0;
    currentTileIndex = 0;
    fileName = "";

    tilesImage = QImage(":/levelEdit/images/tileset.png");

    xTileMax = (tilesImage.size().width() - 2 * OFFSET_X) / REAL_TILE_WIDTH + 1;
    yTileMax = (tilesImage.size().height() - 2 * OFFSET_Y) / REAL_TILE_HEIGHT + 1;

    tiles = new CTiles(xTileMax, yTileMax);
    tiles->load(":/levelEdit/datas/tiles.dat");

    tileWidget->setImage(&tilesImage);

    currentMap = &front;

    wGamePlay->resize(GAME_WIDTH, GAME_HEIGHT);
    wGamePlay->setTilesImage(&tilesImage);
    wGamePlay->setTileMap(currentMap);
    connect(wGamePlay, SIGNAL(viewPortChange(QPoint)), this, SLOT(onWGamePlayViewPortChanged(QPoint)));

    wPreview->setTilesImage(&tilesImage);
    wPreview->setTileMap(currentMap);

    tileSetWidget = new CTileSetWidget(&tilesImage, this);
    connect(tileSetWidget, SIGNAL(mousePress(int,int)), this, SLOT(onTileSetWidgetMousePress(int,int)));
    scrollArea->setWidget(tileSetWidget);

    lblCurrent.setFrameStyle(QFrame::Panel | QFrame::Sunken);;
    lblMax.setFrameStyle(QFrame::Panel | QFrame::Sunken);;

    Ui::CMainWindow::statusBar->addPermanentWidget(&lblCurrent);
    Ui::CMainWindow::statusBar->addPermanentWidget(&lblMax);

    onMapResize(QSize(0, 0));
    setXY();

    onTileSetWidgetMousePress(0, 0);

    connect(&front, SIGNAL(mapResize(QSize)), this, SLOT(onMapResize(QSize)));
    connect(&back, SIGNAL(mapResize(QSize)), this, SLOT(onMapResize(QSize)));

    qApp->installEventFilter(this);
}
//----------------------------------------------------------------------------
CMainWindow::~CMainWindow() {
    delete tileSetWidget;
    delete tiles;
}
//----------------------------------------------------------------------------
bool CMainWindow::eventFilter(QObject *object, QEvent *event) {
    if(event->type() == QEvent::KeyPress && !object->inherits("QLineEdit")) {
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

    lblCurrent.setText("Position in map : "+QString::number(x + 1)+", "+QString::number(y + 1));
}
//----------------------------------------------------------------------------
void CMainWindow::onTileSetWidgetMousePress(const int& x, const int &y) {
    CTile *tile;

    tileSetWidget->setXY(x, y);
    tileWidget->setXY(x, y);

    currentTileIndex = y * xTileMax + x;

    tile = tiles->getTile(currentTileIndex);

    cbSolidUp->setChecked(tile->solidUp);
    cbSolidRight->setChecked(tile->solidRight);
    cbSolidDown->setChecked(tile->solidDown);
    cbSolidLeft->setChecked(tile->solidLeft);
    cbAnimated->setChecked(tile->animated.active);
    cbClimbing->setChecked(tile->climbing);
    cbBreakable->setChecked(tile->breakable);
    cbDangerous->setChecked(tile->dangerous);
    cbHitBonus->setChecked(tile->hitBonus);
    cbTouchBonus->setChecked(tile->touchBonus);
}
//----------------------------------------------------------------------------
void CMainWindow::on_pbAdd_clicked(void) {
    currentMap->add(x, y, currentTileIndex);
    wGamePlay->update();
    wPreview->update();
}
//----------------------------------------------------------------------------
void CMainWindow::on_pbDelete_clicked(void) {
    currentMap->remove(x, y);
    wGamePlay->update();
    wPreview->update();
}
//----------------------------------------------------------------------------
void CMainWindow::onMapResize(const QSize& size) {
    lblMax.setText("Map size : "+QString::number(size.width())+" x "+QString::number(size.height()));
}
//----------------------------------------------------------------------------
void CMainWindow::on_actOpen_triggered(bool) {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Save File"), QString(), tr("Tile data (*.dat)"));

    if(!fileName.isEmpty()) {
        QFile file(fileName);
        if(file.open(QIODevice::ReadOnly)) {
            QDataStream stream(&file);

            front.clear();
            back.clear();
            stream >> front;
            stream >> back;

            file.close();

            this->fileName = fileName;

            on_cbView_currentIndexChanged(0);
        }
    }
}
//----------------------------------------------------------------------------
void CMainWindow::on_actSaveAs_triggered(bool) {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(), tr("Tile data (*.dat)"));

    if(!fileName.isEmpty()) {
        QFile file(fileName);
        if(file.open(QIODevice::WriteOnly)) {
            QDataStream stream(&file);

            stream << front;
            stream << back;

            file.close();

            this->fileName = fileName;
        }
    }
}
//----------------------------------------------------------------------------
void CMainWindow::on_actSave_triggered(bool) {
    if(fileName.isEmpty()) {
        on_actSaveAs_triggered();
    }else {
        QFile file(fileName);
        if(file.open(QIODevice::WriteOnly)) {
            QDataStream stream(&file);

            stream << front;
            stream << back;

            file.close();

            this->fileName = fileName;
        }
    }
}
//----------------------------------------------------------------------------
void CMainWindow::on_cbView_currentIndexChanged(int index) {
    if(index == 0) {
        currentMap = &front;
    } else {
        currentMap = &back ;
    }

    x = y = 0;

    wGamePlay->setTileMap(currentMap);
    wPreview->setTileMap(currentMap);
    onMapResize(currentMap->getSize());

    setXY();

}
//----------------------------------------------------------------------------
void CMainWindow::onWGamePlayViewPortChanged(const QPoint& point) {
    wPreview->setViewPort(point.x(), point.y());
}
//----------------------------------------------------------------------------
void CMainWindow::on_pbSetOrigin_clicked(void) {
    QPoint p = QPoint(x, y);

    currentMap->setOrigin(p);
    wPreview->setOrigin(p);
}
//----------------------------------------------------------------------------
void CMainWindow::on_actQuit_triggered(bool) {
    qApp->quit();
}
//----------------------------------------------------------------------------
