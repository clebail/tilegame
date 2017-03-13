//----------------------------------------------------------------------------
#include <QtDebug>
#include <QFileDialog>
#include <QFile>
#include <common.h>
#include "CMainWindow.h"
//----------------------------------------------------------------------------
CMainWindow::CMainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi(this);

    x = y = 0;

    tilesImage = QImage(":tileEdit/images/tileset.png");

    maxX = (tilesImage.size().width() - 2 * OFFSET_X) / REAL_TILE_WIDTH;
    maxY = (tilesImage.size().height() - 2 * OFFSET_Y) / REAL_TILE_HEIGHT;

    tileCount = maxX * maxY;
    tiles = new CTile[tileCount];

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

    curentFileName = "";

    updateCoords();
}
//----------------------------------------------------------------------------
CMainWindow::~CMainWindow() {
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

    currentTile = &tiles[y * maxX + x];

    cbSolidUp->setChecked(currentTile->solidUp);
    cbSolidRight->setChecked(currentTile->solidRight);
    cbSolidDown->setChecked(currentTile->solidDown);
    cbSolidLeft->setChecked(currentTile->solidLeft);
    cbAnimated->setChecked(currentTile->animated);
    cbBistable->setChecked(currentTile->bistable);
    cbBreakable->setChecked(currentTile->breakable);
    cbTouchBonus->setChecked(currentTile->touchBonus);
    cbHitBonus->setChecked(currentTile->hitBonus);
    cbDangerous->setChecked(currentTile->dangerous);
    txtAnimatedGroupeName->setText(currentTile->animatedGroupName);
    txtBisatbleGroupName->setText(currentTile->bistableGroupName);
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
    if(x < maxX-1) {
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
    currentTile->animated = state == Qt::Checked;
}
//----------------------------------------------------------------------------
void CMainWindow::on_cbBistable_stateChanged(int state) {
    currentTile->bistable = state == Qt::Checked;
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
    currentTile->animatedGroupName = text;
}
//----------------------------------------------------------------------------
void CMainWindow::on_txtBisatbleGroupName_textEdited(const QString & text) {
    currentTile->bistableGroupName = text;
}
//----------------------------------------------------------------------------
void CMainWindow::on_actOpen_triggered(bool) {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Save File"), QString(), tr("Tile data (*.dat)"));

    if(!fileName.isEmpty()) {
        QFile file(fileName);
        if(file.open(QIODevice::ReadOnly)) {
            QDataStream stream(&file);

            for(int i=0;i<tileCount;i++) {
                stream >> tiles[i];
            }

            curentFileName = fileName;
            file.close();
        }
    }

    x = y = 0;
    updateCoords();
}
//----------------------------------------------------------------------------
void CMainWindow::on_actSaveAs_triggered(bool) {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(), tr("Tile data (*.dat)"));

    if(!fileName.isEmpty()) {
        QFile file(fileName);
        if(file.open(QIODevice::WriteOnly)) {
            QDataStream stream(&file);

            for(int i=0;i<tileCount;i++) {
                stream << tiles[i];
            }

            curentFileName = fileName;
        }
        file.close();
    }
}
//----------------------------------------------------------------------------
void CMainWindow::on_actSave_triggered(bool) {
    if(!curentFileName.isEmpty()) {
        QFile file(curentFileName);
        if(file.open(QIODevice::WriteOnly)) {
            QDataStream stream(&file);

            for(int i=0;i<tileCount;i++) {
                stream << tiles[i];
            }

            file.close();
        }else {
            on_actSaveAs_triggered();
        }
    }
}
//----------------------------------------------------------------------------
