//----------------------------------------------------------------------------
#ifndef __CMAINWINDOW_H__
#define __CMAINWINDOW_H__
//----------------------------------------------------------------------------
#include <QMainWindow>
#include <QImage>
#include <CTileSetWidget.h>
#include "ui_CMainWindow.h"
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
private slots:
    void onTileSetWidgetMousePress(const int& x, const int &y);
};
//----------------------------------------------------------------------------
#endif //__CMAINWINDOW_H__
//----------------------------------------------------------------------------
