//----------------------------------------------------------------------------
#ifndef __CANIMATEDIALOG_H__
#define __CANIMATEDIALOG_H__
//----------------------------------------------------------------------------
#include <QDialog>
#include <QTimer>
#include <QList>
#include <CTile.h>
#include "ui_CAnimateDialog.h"
//----------------------------------------------------------------------------
class CAnimateDialog : public QDialog, private Ui::CAnimateDialog {
    Q_OBJECT
public:
    explicit CAnimateDialog(QWidget *parent = 0);
    void setImage(QImage *image);
    void setTiles(const QList<CTile *>& tiles);
private:
    QTimer *timer;
    QList<CTile *> tiles;
    int curTile;
private slots:
    void timeout(void);
    void on_pbPlay_clicked(void);
    void on_pbStop_clicked(void);
};
//----------------------------------------------------------------------------
#endif //__CANIMATEDIALOG_H__
//----------------------------------------------------------------------------
