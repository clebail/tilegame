//----------------------------------------------------------------------------
#include <common.h>
#include "CDialogSimulate.h"
//----------------------------------------------------------------------------
CDialogSimulate::CDialogSimulate(QWidget *parent) :QDialog(parent) {
    //QLayout *layout;

    setupUi(this);

    //layout = layout();
    resize(GAME_WIDTH + layout()->margin() * 2, GAME_HEIGHT + layout()->margin() * 2);

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
