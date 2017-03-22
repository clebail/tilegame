//----------------------------------------------------------------------------
#include <QtDebug>
#include <QFileDialog>
#include <QFile>
#include <QKeyEvent>
#include <common.h>
#include "CMainWindow.h"
//----------------------------------------------------------------------------
CMainWindow::CMainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi(this);

    x = y = 0;

    tilesImage = QImage(":tileEdit/images/tileset.png");

    maxX = (tilesImage.size().width() - 2 * OFFSET_X) / REAL_TILE_WIDTH + 1;
    maxY = (tilesImage.size().height() - 2 * OFFSET_Y) / REAL_TILE_HEIGHT + 1;

    tiles = new CTiles(maxX, maxY);

    tileBig->setImage(&tilesImage);
    tileSmall->setImage(&tilesImage);

    wall[0] = tileWall00;
    wall[1] = tileWall10;
    wall[2] = tileWall20;
    wall[3] = tileWall01;
    wall[4] = tileWall11;
    wall[5] = tileWall21;
    wall[6] = tileWall02;
    wall[7] = tileWall12;
    wall[8] = tileWall22;

    for(int i=0;i<TILE_WALL_COUNT;i++) {
        wall[i]->setImage(&tilesImage);
    }

    tileSetWidget = new CTileSetWidget(&tilesImage, this);
    connect(tileSetWidget, SIGNAL(mousePress(int,int)), this, SLOT(onTileSetWidgetMousePress(int,int)));
    scrollArea->setWidget(tileSetWidget);

    updateCoords();

    qApp->installEventFilter(this);
}
//----------------------------------------------------------------------------
CMainWindow::~CMainWindow() {
    delete tiles;
    delete tileSetWidget;
}
//----------------------------------------------------------------------------
bool CMainWindow::eventFilter(QObject *object, QEvent *event) {
    if(event->type() == QEvent::KeyPress && !object->inherits("QLineEdit")) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        switch(keyEvent->key()) {
        case Qt::Key_Up:
            on_tileUp_clicked();
            return true;
        case Qt::Key_Right:
            on_tileRight_clicked();
            return true;
        case Qt::Key_Down:
            on_tileDown_clicked();
            return true;
        case Qt::Key_Left:
            on_tileLeft_clicked();
            return true;
        default:
            break;
        }
    }

    return QObject::eventFilter(object, event);
}
//----------------------------------------------------------------------------
void CMainWindow::updateCoords(void) {
    lblX->setText(QString::number(x)+" / "+QString::number(maxX));
    lblY->setText(QString::number(y)+" / "+QString::number(maxY));

    tileBig->setXY(x, y);
    tileSmall->setXY(x, y);

    for(int i=0;i<TILE_WALL_COUNT;i++) {
        wall[i]->setXY(x, y);
    }

    currentTile = tiles->getTile(x + y * maxX);

    cbSolidUp->setChecked(currentTile->solidUp);
    cbSolidRight->setChecked(currentTile->solidRight);
    cbSolidDown->setChecked(currentTile->solidDown);
    cbSolidLeft->setChecked(currentTile->solidLeft);
    cbAnimated->setChecked(currentTile->animated.active);
    cbClimbing->setChecked(currentTile->climbing);
    cbBreakable->setChecked(currentTile->breakable);
    cbTouchBonus->setChecked(currentTile->touchBonus);
    cbHitBonus->setChecked(currentTile->hitBonus);
    cbDangerous->setChecked(currentTile->dangerous);
    txtAnimatedGroupeName->setText(currentTile->serializeAnimated());

    tileSetWidget->setXY(x, y);
}
//----------------------------------------------------------------------------
void CMainWindow::on_tileLeft_clicked(void) {
    if(x > 0) {
        x--;

        updateCoords();
    }
}
//----------------------------------------------------------------------------
void CMainWindow::on_tileRight_clicked(void) {
    if(x < maxX - 1) {
        x++;

        updateCoords();
    }
}
//----------------------------------------------------------------------------
void CMainWindow::on_tileUp_clicked(void) {
    if(y > 0) {
        y--;

        updateCoords();
    }
}
//----------------------------------------------------------------------------
void CMainWindow::on_tileDown_clicked(void) {
    if(y < maxY - 1) {
        y++;

        updateCoords();
    }
}
//----------------------------------------------------------------------------
void CMainWindow::on_cbSolidUp_stateChanged(int state) {
    currentTile->solidUp = state == Qt::Checked;
}
//----------------------------------------------------------------------------
void CMainWindow::on_cbSolidRight_stateChanged(int state) {
    currentTile->solidRight = state == Qt::Checked;
}
//----------------------------------------------------------------------------
void CMainWindow::on_cbSolidDown_stateChanged(int state) {
    currentTile->solidDown = state == Qt::Checked;
}
//----------------------------------------------------------------------------
void CMainWindow::on_cbSolidLeft_stateChanged(int state) {
    currentTile->solidLeft = state == Qt::Checked;
}
//----------------------------------------------------------------------------
void CMainWindow::on_cbAnimated_stateChanged(int state) {
    currentTile->animated.active = state == Qt::Checked;
}
//----------------------------------------------------------------------------
void CMainWindow::on_cbClimbing_stateChanged(int state) {
    currentTile->climbing = state == Qt::Checked;
}
//----------------------------------------------------------------------------
void CMainWindow::on_cbBreakable_stateChanged(int state) {
    currentTile->breakable = state == Qt::Checked;
}
//----------------------------------------------------------------------------
void CMainWindow::on_cbTouchBonus_stateChanged(int state) {
    currentTile->touchBonus = state == Qt::Checked;
}
//----------------------------------------------------------------------------
void CMainWindow::on_cbHitBonus_stateChanged(int state) {
    currentTile->hitBonus = state == Qt::Checked;
}
//----------------------------------------------------------------------------
void CMainWindow::on_cbDangerous_stateChanged(int state) {
    currentTile->dangerous = state == Qt::Checked;
}
//----------------------------------------------------------------------------
void CMainWindow::on_txtAnimatedGroupeName_textEdited(const QString & text) {
    currentTile->parseAnimated(text);
}
//----------------------------------------------------------------------------
void CMainWindow::on_actOpen_triggered(bool) {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Save File"), QString(), tr("Tile data (*.dat)"));

    tiles->load(fileName);

    x = y = 0;
    updateCoords();
}
//----------------------------------------------------------------------------
void CMainWindow::on_actSaveAs_triggered(bool) {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(), tr("Tile data (*.dat)"));

    if(!fileName.isEmpty()) {
        tiles->save(fileName);
    }
}
//----------------------------------------------------------------------------
void CMainWindow::on_actSave_triggered(bool) {
    tiles->save(tiles->getFileName());
}
//----------------------------------------------------------------------------
void CMainWindow::on_actQuit_triggered(bool) {
    qApp->quit();
}
//----------------------------------------------------------------------------
void CMainWindow::on_pbAnimate_clicked(void) {
    QList<CTile *> group = tiles->getAnimatedGroup(currentTile->animated.groupName);

    animatedDialog = new CAnimateDialog(this);

    animatedDialog->setImage(&tilesImage);
    animatedDialog->setTiles(group);
    animatedDialog->exec();

    delete animatedDialog;
}
//----------------------------------------------------------------------------
void CMainWindow::onTileSetWidgetMousePress(const int& x, const int &y) {
    this->x = x;
    this->y = y;

    updateCoords();
}
//----------------------------------------------------------------------------
