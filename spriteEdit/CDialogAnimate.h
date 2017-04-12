//----------------------------------------------------------------------------
#ifndef __CDIALOGANIMATE_H__
#define __CDIALOGANIMATE_H__
//----------------------------------------------------------------------------
#include <QDialog>
#include <QTimer>
#include <CSprite.h>
#include "ui_CDialogAnimate.h"
//----------------------------------------------------------------------------
class CDialogAnimate : public QDialog, private Ui::CDialogAnimate {
    Q_OBJECT
public:
    explicit CDialogAnimate(QWidget *parent = 0);
    ~CDialogAnimate(void);
    void setSprite(CSprite *sprite);
    void setMotionIndex(int index);
private:
    CSprite *sprite;
    QTimer *timer;
    int motionIndex;
    int currentFrame;
    int x, y;
    double coef;
private slots:
    void on_pbPlay_clicked(void);
    void on_pbStop_clicked(void);
    void on_slTime_valueChanged(int value);
    void timeout(void);
};
//----------------------------------------------------------------------------
#endif // __CDIALOGANIMATE_H__
//----------------------------------------------------------------------------
