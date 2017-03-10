//----------------------------------------------------------------------------
#include "CMainWindow.h"
//----------------------------------------------------------------------------
CMainWindow::CMainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi(this);

    tiles = QImage(":tileEdit/images/tileset.png");

    tileBig->setImage(&tiles);
    tileSmall->setImage(&tiles);
}
//----------------------------------------------------------------------------
CMainWindow::~CMainWindow() {
}
//----------------------------------------------------------------------------
void CMainWindow::on_tileLeft_clicked(void) {
    tileBig->decX();
    tileSmall->decX();
}
//----------------------------------------------------------------------------
void CMainWindow::on_tileRight_clicked(void) {
    tileBig->incX();
    tileSmall->incX();
}
//----------------------------------------------------------------------------
void CMainWindow::on_tileUp_clicked(void) {
    tileBig->decY();
    tileSmall->decY();
}
//----------------------------------------------------------------------------
void CMainWindow::on_tileDown_clicked(void) {
    tileBig->incY();
    tileSmall->incY();
}
//----------------------------------------------------------------------------
