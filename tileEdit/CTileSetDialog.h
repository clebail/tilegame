//----------------------------------------------------------------------------
#ifndef __CTILESETDIALOG_H__
#define __CTILESETDIALOG_H__
//----------------------------------------------------------------------------
#include <QDialog>
#include "ui_CTileSetDialog.h"
#include "CTileSetWidget.h"
//----------------------------------------------------------------------------
class CTileSetDialog : public QDialog, private Ui::CTileSetDialog {
    Q_OBJECT
public:
    explicit CTileSetDialog(QImage *image, QWidget *parent = 0);
    ~CTileSetDialog();
    void setXY(int x, int y);
private:
    CTileSetWidget *tileSetWidget;
private slots:
    void onMousePress(const int& x ,const int& y);
signals:
    void mousePress(const int &x, const int &y);
};
//----------------------------------------------------------------------------
#endif //__CTILESETDIALOG_H__
//----------------------------------------------------------------------------
