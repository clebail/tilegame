//----------------------------------------------------------------------------
#ifndef __CMAINWINDOW_H__
#define __CMAINWINDOW_H__
//----------------------------------------------------------------------------
#include <QMainWindow>
#include "ui_CMainWindow.h"
//----------------------------------------------------------------------------
class CMainWindow : public QMainWindow, private Ui::CMainWindow {
    Q_OBJECT
public:
    explicit CMainWindow(QWidget *parent = 0);
    ~CMainWindow();
private:
    QImage tiles;
private slots:
    void on_tileLeft_clicked(void);
    void on_tileRight_clicked(void);
    void on_tileUp_clicked(void);
    void on_tileDown_clicked(void);
};
//----------------------------------------------------------------------------
#endif //__CMAINWINDOW_H__
//----------------------------------------------------------------------------
