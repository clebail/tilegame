//----------------------------------------------------------------------------
#include <common.h>
#include "CDialogSimulate.h"
//----------------------------------------------------------------------------
CDialogSimulate::CDialogSimulate(QWidget *parent) :QDialog(parent) {
    setupUi(this);

    wSimulate->resize(GAME_WIDTH, GAME_HEIGHT);

    timer = new QTimer(this);
    timer->setInterval(40);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
}
//----------------------------------------------------------------------------
CDialogSimulate::~CDialogSimulate(void) {
    delete timer;
}
//----------------------------------------------------------------------------
void CDialogSimulate::setTileMaps(CTileMap *front, CTileMap *back) {
    wSimulate->setTileMaps(front, back);
}
//----------------------------------------------------------------------------
void CDialogSimulate::setTiles(CTiles *tiles) {
    wSimulate->setTiles(tiles);
}
//----------------------------------------------------------------------------
void CDialogSimulate::setTilesImage(QImage *tilesImage) {
    wSimulate->setTilesImage(tilesImage);
}
//----------------------------------------------------------------------------
void CDialogSimulate::timeout(void) {
    wSimulate->update();
}
//----------------------------------------------------------------------------
