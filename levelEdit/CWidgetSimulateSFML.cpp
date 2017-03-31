//----------------------------------------------------------------------------
#include <QtDebug>
#include <common.h>
#include "CWidgetSimulateSFML.h"

#include <Qt/qx11info_x11.h>
#include <X11/Xlib.h>
//----------------------------------------------------------------------------
CWidgetSimulateSFML::CWidgetSimulateSFML(QWidget *parent) : CWidgetSimulate(parent) {
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    setFocusPolicy(Qt::StrongFocus);

    initialized = false;
}
//----------------------------------------------------------------------------
CWidgetSimulateSFML::~CWidgetSimulateSFML(void) {

}
//----------------------------------------------------------------------------
void CWidgetSimulateSFML::showEvent(QShowEvent*) {
    if (!initialized) {
        XFlush(QX11Info::display());

        sf::RenderWindow::create(winId());

        init();

        initialized = true;
    }
}
//----------------------------------------------------------------------------
QPaintEngine* CWidgetSimulateSFML::paintEngine() const {
    return 0;
}
//----------------------------------------------------------------------------
void CWidgetSimulateSFML::paintEvent(QPaintEvent*) {
    update();

    sf::RenderWindow::display();
}
//----------------------------------------------------------------------------
void CWidgetSimulateSFML::init(void) {
}
//----------------------------------------------------------------------------
void CWidgetSimulateSFML::update(void) {
}
//----------------------------------------------------------------------------
