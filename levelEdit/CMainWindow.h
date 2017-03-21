//----------------------------------------------------------------------------
#ifndef __CMAINWINDOW_H__
#define __CMAINWINDOW_H__
//----------------------------------------------------------------------------
#include <QMainWindow>
#include <QImage>
#include <CTileSetWidget.h>
#include "ui_CMainWindow.h"
#include "CWidgetGamePlay.h"
#include "CTileMap.h"
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
    CTileMap front, back, *currentMap;
    int currentTile;
    QLabel lblMax, lblCurrent;
    QString fileName;

    void setXY(void);
private slots:
    void onTileSetWidgetMousePress(const int& x, const int &y);
    void on_pbAdd_clicked(void);
    void on_pbDelete_clicked(void);
    void onMapResize(const QSize& size);
    void on_actOpen_triggered(bool checked = false);
    void on_actSaveAs_triggered(bool checked = false);
    void on_actSave_triggered(bool checked = false);
    void on_cbView_currentIndexChanged(int);
    void onWGamePlayViewPortChanged(const QPoint& point);
    void on_pbSetOrigin_clicked(void);
};
//----------------------------------------------------------------------------
#endif //__CMAINWINDOW_H__
//----------------------------------------------------------------------------
