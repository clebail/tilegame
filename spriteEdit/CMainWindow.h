//----------------------------------------------------------------------------
#ifndef __CMAINWINDOW_H__
#define __CMAINWINDOW_H__
//----------------------------------------------------------------------------
#include <QMainWindow>
#include "ui_CMainWindow.h"
#include "CWidgetSpriteSheet.h"
//----------------------------------------------------------------------------
class CMainWindow : public QMainWindow, private Ui::CMainWindow {
    Q_OBJECT
public:
    explicit CMainWindow(QWidget *parent = 0);
    ~CMainWindow(void);
private:
    CWidgetSpriteSheet *wSpriteSheet;
private slots:
    void on_actQuit_triggered(bool checked = false);
    void on_actSSopen_triggered(bool checked = false);
    void on_pbZoomPlus_clicked(void);
    void on_pbZoomMoins_clicked(void);
};
//----------------------------------------------------------------------------
#endif //__CMAINWINDOW_H__
//----------------------------------------------------------------------------
