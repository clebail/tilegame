//----------------------------------------------------------------------------
#ifndef __CMAINWINDOW_H__
#define __CMAINWINDOW_H__
//----------------------------------------------------------------------------
#include <QMainWindow>
#include <CSprite.h>
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
    CSprite sprite;
    CSpriteFrame * currentSpriteFrame;
    CSpriteFrame tmpSpriteFrame;
private slots:
    void on_actQuit_triggered(bool checked = false);
    void on_actSSopen_triggered(bool checked = false);
    void on_pbZoomPlus_clicked(void);
    void on_pbZoomMoins_clicked(void);
    void onCapture(const QPoint& topLeft, const QPoint& bottomRight);
    void on_pbAddFrame_clicked(void);
    void on_cbMotionType_currentIndexChanged(int index);
    void on_cbHurt_stateChanged(int state);
    void on_pbOpenSound_clicked(void);
};
//----------------------------------------------------------------------------
#endif //__CMAINWINDOW_H__
//----------------------------------------------------------------------------
