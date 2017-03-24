//----------------------------------------------------------------------------
#ifndef __CDIALOGSIMULATE_H__
#define __CDIALOGSIMULATE_H__
//----------------------------------------------------------------------------
#include <QDialog>
#include <QTimer>
#include <CLevel.h>
#include "ui_CDialogSimulate.h"
//----------------------------------------------------------------------------
class CDialogSimulate : public QDialog, private Ui::CDialogSimulate {
    Q_OBJECT
public:
    explicit CDialogSimulate(QWidget *parent = 0);
    ~CDialogSimulate(void);
    void setLevel(CLevel *level);
    void setTiles(CTiles *tiles);
    void setTilesImage(QImage *tilesImage);
    virtual bool eventFilter(QObject *object, QEvent *event);
private:
    QTimer *timer;
private slots:
    void timeout(void);
};
//----------------------------------------------------------------------------
#endif // __CDIALOGSIMULATE_H__
//----------------------------------------------------------------------------
