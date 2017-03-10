//----------------------------------------------------------------------------
#include "CMainWindow.h"
//----------------------------------------------------------------------------
CMainWindow::CMainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi(this);

    tiles = QImage(":tileEdit/images/tileset.png");

    tileBig->setImage(tiles);
    tileSmall->setImage(tiles);
}
//----------------------------------------------------------------------------
CMainWindow::~CMainWindow() {
}
//----------------------------------------------------------------------------
