//----------------------------------------------------------------------------
#include <QtDebug>
#include "CMainWindow.h"
//----------------------------------------------------------------------------
CMainWindow::CMainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi(this);

    tiles = QImage(":tileEdit/images/tileset.png");

    tileBig->setImage(&tiles);
    tileSmall->setImage(&tiles);

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
        wall[i]->setImage(&tiles);
    }

    qDebug() << lblX->font();

    updateCoords();
}
//----------------------------------------------------------------------------
CMainWindow::~CMainWindow() {
}
//----------------------------------------------------------------------------
void CMainWindow::updateCoords(void) {
    lblX->setText(QString::number(tileBig->getX())+" / "+QString::number(tileBig->getXMax()));
    lblY->setText(QString::number(tileBig->getY())+" / "+QString::number(tileBig->getYMax()));
}
//----------------------------------------------------------------------------
void CMainWindow::on_tileLeft_clicked(void) {
    tileBig->decX();
    tileSmall->decX();

    for(int i=0;i<TILE_WALL_COUNT;i++) {
        wall[i]->decX();
    }

    updateCoords();
}
//----------------------------------------------------------------------------
void CMainWindow::on_tileRight_clicked(void) {
    tileBig->incX();
    tileSmall->incX();

    for(int i=0;i<TILE_WALL_COUNT;i++) {
        wall[i]->incX();
    }

    updateCoords();
}
//----------------------------------------------------------------------------
void CMainWindow::on_tileUp_clicked(void) {
    tileBig->decY();
    tileSmall->decY();

    for(int i=0;i<TILE_WALL_COUNT;i++) {
        wall[i]->decY();
    }

    updateCoords();
}
//----------------------------------------------------------------------------
void CMainWindow::on_tileDown_clicked(void) {
    tileBig->incY();
    tileSmall->incY();

    for(int i=0;i<TILE_WALL_COUNT;i++) {
        wall[i]->incY();
    }

    updateCoords();
}
//----------------------------------------------------------------------------
