#include <QtDebug>
#include <QFileDialog>
#include <QScrollBar>
#include <QRgb>
#include "CMainWindow.h"
//----------------------------------------------------------------------------
#define BUFFER_SIZE             1024
//----------------------------------------------------------------------------
CMainWindow::CMainWindow(QWidget *parent) : QMainWindow(parent) {
    QSizePolicy sp(QSizePolicy::Preferred, QSizePolicy::Preferred);

    setupUi(this);

    wSpriteSheet = new CWidgetSpriteSheet(this);

    scrollArea->setWidget(wSpriteSheet);

    sp.setVerticalStretch(1);
    wEdit->setSizePolicy(sp);
    gbSpriteSheet->setSizePolicy(sp);

    sp.setHorizontalStretch(1);
    gbEdit->setSizePolicy(sp);
    gbPreview->setSizePolicy(sp);

    wPreview->setSprite(&sprite);

    currentSpriteFrame = 0;

    connect(wSpriteSheet, SIGNAL(capture(QPoint,QPoint)), this, SLOT(onCapture(QPoint,QPoint)));
}
//----------------------------------------------------------------------------
CMainWindow::~CMainWindow(void) {
    delete wSpriteSheet;
}
//----------------------------------------------------------------------------
void CMainWindow::on_actQuit_triggered(bool) {
    qApp->quit();
}
//----------------------------------------------------------------------------
void CMainWindow::on_actSSopen_triggered(bool) {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Sprite Sheet Image"), QString(), tr("Image file (*.png)"));

    if(!fileName.isEmpty()) {
        wSpriteSheet->loadImage(fileName);
        sprite.setSpriteSheet(wSpriteSheet->getImage());
    }
}
//----------------------------------------------------------------------------
void CMainWindow::on_pbZoomPlus_clicked(void) {
    wSpriteSheet->incZoomScale();
}
//----------------------------------------------------------------------------
void CMainWindow::on_pbZoomMoins_clicked(void) {
    wSpriteSheet->decZoomScale();
}
//----------------------------------------------------------------------------
void CMainWindow::onCapture(const QPoint& topLeft, const QPoint& bottomRight) {
    QRect frameRect(topLeft, bottomRight);
    QImage frame = wSpriteSheet->getImage().copy(frameRect);

    tmpSpriteFrame = CSpriteFrame();
    tmpSpriteFrame.setRect(frameRect);

    wFrame->setImage(frame);
}
//----------------------------------------------------------------------------
void CMainWindow::on_pbAddFrame_clicked(void) {
    currentSpriteFrame = new CSpriteFrame();
    currentSpriteFrame->setRect(tmpSpriteFrame.getRect());

    sprite.addFrame(cbMotionType->currentIndex(), currentSpriteFrame);

    wPreview->setCurrentFrameIndex(sprite.getFrameCount(cbMotionType->currentIndex()) - 1);
}
//----------------------------------------------------------------------------
void CMainWindow::on_cbMotionType_currentIndexChanged(int index) {
    wPreview->setCurrentMotion((CSprite::EMotion)index);
    wPreview->setCurrentFrameIndex(0);

    currentSpriteFrame = sprite.getFrame((CSprite::EMotion)index, 0);

    cbHurt->setChecked(false);
    leSound->setText("");

    if(currentSpriteFrame == 0) {
        wFrame->setImage(QImage());
    } else {
        wFrame->setImage(wSpriteSheet->getImage().copy(currentSpriteFrame->getRect()));

        cbHurt->setChecked(currentSpriteFrame->getHurt());
        leSound->setText(currentSpriteFrame->getSoundName());
    }
}
//----------------------------------------------------------------------------
void CMainWindow::on_cbHurt_stateChanged(int state) {
    currentSpriteFrame->setHurt((bool)state);
}
//----------------------------------------------------------------------------
void CMainWindow::on_pbOpenSound_clicked(void) {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), QString(), tr("Sound file (*.wav *.ogg *.mp3)"));

    if(!fileName.isEmpty()) {
        QFile file(fileName);
        if(file.open(QIODevice::ReadOnly)) {
            QDataStream stream(&file);
            QByteArray sound;
            QFileInfo fi(file);

            while(!stream.atEnd()) {
                char buffer[BUFFER_SIZE];
                int len;

                len = stream.readRawData(buffer, BUFFER_SIZE);

                sound.append(buffer, len);
            }

            file.close();

            leSound->setText(fi.baseName());
            currentSpriteFrame->setSoundName(fi.baseName());
            currentSpriteFrame->setSound(sound);
        }
    }
}
//----------------------------------------------------------------------------
