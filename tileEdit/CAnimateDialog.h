//----------------------------------------------------------------------------
#ifndef __CANIMATEDIALOG_H__
#define __CANIMATEDIALOG_H__
//----------------------------------------------------------------------------
#include <QDialog>
#include <QTimer>
#include <QList>
#include <QPoint>
#include "ui_CAnimateDialog.h"
//----------------------------------------------------------------------------
class CAnimateDialog : public QDialog, private Ui::CAnimateDialog {
    Q_OBJECT
public:
    explicit CAnimateDialog(QWidget *parent = 0);
    void setImage(QImage *image);
    void setCoords(const QList<QPoint>& coords);
private:
    QTimer *timer;
    QImage *image;
    QList<QPoint> coords;
    int curCoord;
private slots:
    void timeout(void);
    void on_pbPlay_clicked(void);
    void on_pbStop_clicked(void);
};
//----------------------------------------------------------------------------
#endif //__CANIMATEDIALOG_H__
//----------------------------------------------------------------------------
