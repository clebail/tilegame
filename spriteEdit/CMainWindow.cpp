#include <QtDebug>
#include <QFileDialog>
#include <QScrollBar>
#include <QRgb>
#include "CMainWindow.h"
#include "CDialogAnimate.h"
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
    currentSpriteFrameIndex = 0;

    connect(wSpriteSheet, SIGNAL(capture(QPoint,QPoint)), this, SLOT(onCapture(QPoint,QPoint)));
    connect(wPreview, SIGNAL(currentFrameChanged(int)), this, SLOT(onCurrentFrameChnaged(int)));
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

    currentSpriteFrameIndex = sprite.getFrameCount(cbMotionType->currentIndex()) - 1;

    wPreview->setCurrentFrameIndex(currentSpriteFrameIndex);
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

    currentSpriteFrameIndex = 0;
}
//----------------------------------------------------------------------------
void CMainWindow::on_cbHurt_stateChanged(int state) {
    if(currentSpriteFrame != 0) {
        currentSpriteFrame->setHurt((bool)state);
    }
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
void CMainWindow::onCurrentFrameChnaged(int index) {
    currentSpriteFrame = sprite.getFrame((CSprite::EMotion)cbMotionType->currentIndex(), index);

    wFrame->setImage(sprite.getSpriteSheet().copy(currentSpriteFrame->getRect()));

    cbHurt->setChecked(currentSpriteFrame->getHurt());
    leSound->setText(currentSpriteFrame->getSoundName());

    currentSpriteFrameIndex = index;
}
//----------------------------------------------------------------------------
void CMainWindow::on_pbLeft_clicked(void) {
    if(currentSpriteFrameIndex > 0) {
        sprite.swap(cbMotionType->currentIndex(), currentSpriteFrameIndex, currentSpriteFrameIndex - 1);
        currentSpriteFrameIndex--;

        wPreview->setCurrentFrameIndex(currentSpriteFrameIndex);
        wPreview->updateFrameRects();
        wPreview->repaint();
    }
}
//----------------------------------------------------------------------------
void CMainWindow::on_pbRight_clicked(void) {
    if(currentSpriteFrameIndex < sprite.getFrameCount(cbMotionType->currentIndex()) - 1) {
        sprite.swap(cbMotionType->currentIndex(), currentSpriteFrameIndex, currentSpriteFrameIndex + 1);
        currentSpriteFrameIndex++;

        wPreview->setCurrentFrameIndex(currentSpriteFrameIndex);
        wPreview->updateFrameRects();
        wPreview->repaint();
    }
}
//----------------------------------------------------------------------------
void CMainWindow::on_pbDelete_clicked(void) {
    sprite.deleteFrame(cbMotionType->currentIndex(), currentSpriteFrameIndex);

    currentSpriteFrameIndex = 0;

    wPreview->setCurrentFrameIndex(currentSpriteFrameIndex);
    wPreview->updateFrameRects();
    wPreview->repaint();
}
//----------------------------------------------------------------------------
void CMainWindow::on_actNew_triggered(bool) {
    sprite.clear();

    currentSpriteFrame = 0;
    currentSpriteFrameIndex = 0;
    wSpriteSheet->clear();

    wFrame->setImage(QImage());

    wPreview->setCurrentFrameIndex(currentSpriteFrameIndex);
    wPreview->updateFrameRects();
    wPreview->repaint();

    cbMotionType->setCurrentIndex(0);
    cbHurt->setChecked(false);
    leSound->setText("");
}
//----------------------------------------------------------------------------
void CMainWindow::on_actOpen_triggered(bool) {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(), tr("Sprite data (*.spr)"));

    if(!fileName.isEmpty()) {
        QFile file(fileName);
        if(file.open(QIODevice::ReadOnly)) {
            QDataStream stream(&file);

            sprite.clear();
            stream >> sprite;

            file.close();

            wSpriteSheet->setImage(sprite.getSpriteSheet());
            cbMotionType->setCurrentIndex(0);
            currentSpriteFrameIndex = 0;

            currentSpriteFrame = sprite.getFrame(0, 0);

            if(currentSpriteFrame != 0) {
                wFrame->setImage(sprite.getSpriteSheet().copy(currentSpriteFrame->getRect()));
                cbHurt->setChecked(currentSpriteFrame->getHurt());
                leSound->setText(currentSpriteFrame->getSoundName());
            }else {
                wFrame->setImage(QImage());
                cbHurt->setChecked(false);
                leSound->setText("");
            }

            wPreview->setCurrentFrameIndex(currentSpriteFrameIndex);
            wPreview->updateFrameRects();
            wPreview->repaint();
        }
    }
}
//----------------------------------------------------------------------------
void CMainWindow::on_actSaveAs_triggered(bool) {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(), tr("Sprite data (*.spr)"));

    if(!fileName.isEmpty()) {
        QFile file(fileName);
        if(file.open(QIODevice::WriteOnly)) {
            QDataStream stream(&file);

            stream << sprite;

            file.close();

            this->fileName = fileName;
        }
    }
}
//----------------------------------------------------------------------------
void CMainWindow::on_actSave_triggered(bool) {
    if(fileName.isEmpty()) {
        on_actSaveAs_triggered();
    }else {
        QFile file(fileName);
        if(file.open(QIODevice::WriteOnly)) {
            QDataStream stream(&file);

            stream << sprite;

            file.close();

            this->fileName = fileName;
        }
    }
}
//----------------------------------------------------------------------------
void CMainWindow::on_pbAnimate_clicked(void) {
    CDialogAnimate dialogAnimate(this);

    dialogAnimate.setData(&sprite, cbMotionType->currentIndex());

    dialogAnimate.exec();
}
//----------------------------------------------------------------------------
