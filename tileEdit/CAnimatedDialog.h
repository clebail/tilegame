//----------------------------------------------------------------------------
#ifndef __CANIMATEDIALOG_H__
#define __CANIMATEDIALOG_H__
//----------------------------------------------------------------------------
#include <QDialog>
#include <QTimer>
#include <CTilesGroup.h>
#include "ui_CAnimateDialog.h"
//----------------------------------------------------------------------------
class CAnimatedDialog : public QDialog, private Ui::CAnimateDialog {
    Q_OBJECT
public:
    explicit CAnimatedDialog(QWidget *parent = 0);
    void setImage(QImage *image);
    void setTilesGroup(CTilesGroup *group);
private:
    QTimer *timer;
    CTilesGroup *group;
private slots:
    void timeout(void);
    void on_pbPlay_clicked(void);
    void on_pbStop_clicked(void);
};
//----------------------------------------------------------------------------
#endif //__CANIMATEDIALOG_H__
//----------------------------------------------------------------------------
