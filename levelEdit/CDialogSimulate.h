//----------------------------------------------------------------------------
#ifndef __CDIALOGSIMULATE_H__
#define __CDIALOGSIMULATE_H__
//----------------------------------------------------------------------------
#include <QDialog>
#include <QTimer>
#include "ui_CDialogSimulate.h"
//----------------------------------------------------------------------------
class CDialogSimulate : public QDialog, private Ui::CDialogSimulate {
    Q_OBJECT
public:
    explicit CDialogSimulate(QWidget *parent = 0);
    ~CDialogSimulate(void);
    void setTileMaps(CTileMap *front, CTileMap *back);
    void setTiles(CTiles *tiles);
    void setTilesImage(QImage *tilesImage);
private:
    QTimer *timer;
private slots:
    void timeout(void);
};
//----------------------------------------------------------------------------
#endif // __CDIALOGSIMULATE_H__
//----------------------------------------------------------------------------
