#include <QtDebug>
#include <QFileDialog>
#include "CMainWindow.h"
//----------------------------------------------------------------------------
CMainWindow::CMainWindow(QWidget *parent) : QMainWindow(parent) {
    QSizePolicy sp(QSizePolicy::Preferred, QSizePolicy::Preferred);

    setupUi(this);

    wSpriteSheet = new CWidgetSpriteSheet(this);

    scrollArea->setWidget(wSpriteSheet);

    sp.setVerticalStretch(1);
    wEdit->setSizePolicy(sp);
    gbSpriteSheet->setSizePolicy(sp);
}
//----------------------------------------------------------------------------
CMainWindow::~CMainWindow(void) {
    delete wSpriteSheet;
}
//----------------------------------------------------------------------------
void CMainWindow::on_actQuit_triggered(bool) {
    qApp->quit();
}
//----------------------------------------------------------------------------
void CMainWindow::on_actSSopen_triggered(bool) {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Sprite Sheet Image"), QString(), tr("Image file (*.png)"));

    if(!fileName.isEmpty()) {
        wSpriteSheet->loadImage(fileName);
    }
}
//----------------------------------------------------------------------------
void CMainWindow::on_pbZoomPlus_clicked(void) {
    wSpriteSheet->incZoomScale();
}
//----------------------------------------------------------------------------
void CMainWindow::on_pbZoomMoins_clicked(void) {
    wSpriteSheet->decZoomScale();
}
//----------------------------------------------------------------------------
