//----------------------------------------------------------------------------
#ifndef __CMAINWINDOW_H__
#define __CMAINWINDOW_H__
//----------------------------------------------------------------------------
#include <QMainWindow>
#include <CTiles.h>
#include "ui_CMainWindow.h"
#include "CAnimateDialog.h"
#include "CTileSetWidget.h"
//----------------------------------------------------------------------------
#define TILE_WALL_COUNT             9
//----------------------------------------------------------------------------
class CMainWindow : public QMainWindow, private Ui::CMainWindow {
    Q_OBJECT
public:
    explicit CMainWindow(QWidget *parent = 0);
    ~CMainWindow();
    virtual bool eventFilter(QObject *object, QEvent *event);
private:
    QImage tilesImage;
    CWidgetTile *wall[TILE_WALL_COUNT];
    int x, y;
    int maxX, maxY;
    CTiles *tiles;
    CTile *currentTile;
    CAnimateDialog *animatedDialog;
    CTileSetWidget *tileSetWidget;

    void updateCoords(void);
private slots:
    void on_tileLeft_clicked(void);
    void on_tileRight_clicked(void);
    void on_tileUp_clicked(void);
    void on_tileDown_clicked(void);
    void on_cbSolidUp_stateChanged(int state);
    void on_cbSolidRight_stateChanged(int state);
    void on_cbSolidDown_stateChanged(int state);
    void on_cbSolidLeft_stateChanged(int state);
    void on_cbAnimated_stateChanged(int state);
    void on_cbClimbing_stateChanged(int state);
    void on_cbBreakable_stateChanged(int state);
    void on_cbTouchBonus_stateChanged(int state);
    void on_cbHitBonus_stateChanged(int state);
    void on_cbDangerous_stateChanged(int state);
    void on_txtAnimatedGroupeName_textEdited(const QString & text);
    void on_actOpen_triggered(bool checked = false);
    void on_actSaveAs_triggered(bool checked = false);
    void on_actSave_triggered(bool checked = false);
    void on_pbAnimate_clicked(void);
    void onTileSetWidgetMousePress(const int& x, const int &y);
};
//----------------------------------------------------------------------------
#endif //__CMAINWINDOW_H__
//----------------------------------------------------------------------------
