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
};
//----------------------------------------------------------------------------
#endif //__CTILESETDIALOG_H__
//----------------------------------------------------------------------------
