//----------------------------------------------------------------------------
#ifndef __CMAINWINDOW_H__
#define __CMAINWINDOW_H__
//----------------------------------------------------------------------------
#include <QMainWindow>
#include <QImage>
#include <CTileSetWidget.h>
#include <CTiles.h>
#include <CTileMap.h>
#include <CLevel.h>
#include "ui_CMainWindow.h"
#include "CWidgetGamePlay.h"
//----------------------------------------------------------------------------
class CMainWindow : public QMainWindow, private Ui::CMainWindow {
    Q_OBJECT
public:
    explicit CMainWindow(QWidget *parent = 0);
    ~CMainWindow();
    virtual bool eventFilter(QObject *object, QEvent *event);
private:
    QImage tilesImage;
    CTileSetWidget *tileSetWidget;
    int x, y;
    int xTileMax;
    CLevel level;
    CTileMap *currentMap;
    int currentTileIndex;
    QLabel lblMax, lblCurrent;
    QString fileName;
    CTiles *tiles;

    void setXY(void);
private slots:
    void onTileSetWidgetMousePress(const int& x, const int &y);
    void on_pbAdd_clicked(void);
    void on_pbDelete_clicked(void);
    void onMapResize(const QSize& size);
    void on_actNew_triggered(bool checked = false);
    void on_actOpen_triggered(bool checked = false);
    void on_actSaveAs_triggered(bool checked = false);
    void on_actSave_triggered(bool checked = false);
    void on_cbView_currentIndexChanged(int);
    void onWGamePlayViewPortChanged(const QPoint& point);
    void on_pbSetOrigin_clicked(void);
    void on_actQuit_triggered(bool checked = false);
    void on_actSimulate_triggered(bool checked = false);
    void on_pbInsertRow_clicked(void);
    void on_pbInsertColumn_clicked(void);
    void onWGamePlayMousePress(const int& x, const int& y);
    void on_pbSetPlayer_clicked(void);
    void on_pbToggleMonster_clicked(void);
    void on_rbBombe_clicked(void);
    void on_rbCoin_clicked(void);
    void on_rbOneUp_clicked(void);
    void on_rbFood_clicked(void);
    void on_rbWin_clicked(void);
    void on_leScore_editingFinished(void);
};
//----------------------------------------------------------------------------
#endif //__CMAINWINDOW_H__
//----------------------------------------------------------------------------
