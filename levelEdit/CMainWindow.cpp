//----------------------------------------------------------------------------
#include <QtDebug>
#include <QKeyEvent>
#include <QFileDialog>
#include <common.h>
#include "CDialogSimulate.h"
#include "CMainWindow.h"
#include "CWidgetSimulateSFML.h"
//----------------------------------------------------------------------------
CMainWindow::CMainWindow(QWidget *parent) : QMainWindow(parent) {
    int yTileMax;

    setupUi(this);

    x = y = 0;
    currentTileIndex = 0;
    fileName = "";

    tilesImage = QImage(":/levelEdit/images/tileset.png");

    xTileMax = (tilesImage.size().width() - 2 * OFFSET_X) / REAL_TILE_WIDTH + 1;
    yTileMax = (tilesImage.size().height() - 2 * OFFSET_Y) / REAL_TILE_HEIGHT + 1;

    tiles = new CTiles(xTileMax, yTileMax);
    tiles->load(":/levelEdit/datas/tiles.dat");

    tileWidget->setImage(&tilesImage);

    currentMap = level.getLayer(0);

    wGamePlay->resize(GAME_WIDTH, GAME_HEIGHT);
    wGamePlay->setTilesImage(&tilesImage);
    wGamePlay->setTileMap(currentMap);
    connect(wGamePlay, SIGNAL(viewPortChange(QPoint)), this, SLOT(onWGamePlayViewPortChanged(QPoint)));
    connect(wGamePlay, SIGNAL(mousePress(int,int)), this, SLOT(onWGamePlayMousePress(int,int)));

    wPreview->setTilesImage(&tilesImage);
    wPreview->setTileMap(currentMap);

    tileSetWidget = new CTileSetWidget(&tilesImage, this);
    connect(tileSetWidget, SIGNAL(mousePress(int,int)), this, SLOT(onTileSetWidgetMousePress(int,int)));
    scrollArea->setWidget(tileSetWidget);

    lblCurrent.setFrameStyle(QFrame::Panel | QFrame::Sunken);

    Ui::CMainWindow::statusBar->addPermanentWidget(&lblCurrent);

    setXY();

    onTileSetWidgetMousePress(0, 0);

    qApp->installEventFilter(this);
}
//----------------------------------------------------------------------------
CMainWindow::~CMainWindow() {
    delete tileSetWidget;
    delete tiles;
}
//----------------------------------------------------------------------------
bool CMainWindow::eventFilter(QObject *object, QEvent *event) {
    if(event->type() == QEvent::KeyPress && !object->inherits("QLineEdit")) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        switch(keyEvent->key()) {
        case Qt::Key_Up:
            if(y > 0) {
                y--;
                setXY();
            }
            return true;
        case Qt::Key_Right:
            x++;
            setXY();
            return true;
        case Qt::Key_Down:
            y++;
            setXY();
            return true;
        case Qt::Key_Left:
            if(x > 0) {
                x--;
                setXY();
            }
            return true;
        case Qt::Key_Plus:
            on_pbAdd_clicked();
            return true;
        case Qt::Key_Minus:
            on_pbDelete_clicked();
            return true;
        default:
            break;
        }
    }

    return QObject::eventFilter(object, event);
}
//----------------------------------------------------------------------------
void CMainWindow::setXY(void) {
    int *mapTileIndex = currentMap->getTileIndex(x, y);
    bool canSetCharacter = currentMap == level.getLayer(0) && mapTileIndex == 0;
    CTile *mapTile = (mapTileIndex != 0 ? tiles->getTile(*mapTileIndex) : 0);
    bool canSetBonus = mapTile !=0 && (mapTile->hitBonus || mapTile->touchBonus);
    CTileGame tileGame = currentMap->getTile(x, y);

    wGamePlay->setXY(x, y);

    lblCurrent.setText("Position in map : "+QString::number(x + 1)+", "+QString::number(y + 1));

    pbSetPlayer->setEnabled(canSetCharacter);
    pbToggleMonster->setEnabled(canSetCharacter);

    gbScore->setEnabled(canSetBonus);

    if(canSetBonus && tileGame.bonusType != CTileGame::ebtNone) {
        QRadioButton *rb = 0;
        switch(tileGame.bonusType) {
        case CTileGame::ebtBombe:
            rb = rbBombe;
            break;
        case CTileGame::ebtCoin:
            rb = rbCoin;
            break;
        case CTileGame::ebtFood:
            rb = rbFood;
            break;
        case CTileGame::ebtOneUp:
            rb = rbOneUp;
            break;
        case CTileGame::ebtWin:
            rb = rbWin;
            break;
        default:
            break;
        }

        rb->setChecked(true);

        leScore->setText(QString::number(tileGame.score));
    } else {
        rbBombe->setAutoExclusive(false);
        rbOneUp->setAutoExclusive(false);
        rbCoin->setAutoExclusive(false);
        rbFood->setAutoExclusive(false);
        rbWin->setAutoExclusive(false);

        rbBombe->setChecked(false);
        rbOneUp->setChecked(false);
        rbCoin->setChecked(false);
        rbFood->setChecked(false);
        rbWin->setChecked(false);

        rbBombe->setAutoExclusive(true);
        rbOneUp->setAutoExclusive(true);
        rbCoin->setAutoExclusive(true);
        rbFood->setAutoExclusive(true);
        rbWin->setAutoExclusive(true);

        leScore->setText(0);
    }
}
//----------------------------------------------------------------------------
void CMainWindow::onTileSetWidgetMousePress(const int& x, const int &y) {
    CTile *tile;

    tileSetWidget->setXY(x, y);
    tileWidget->setXY(x, y);

    currentTileIndex = y * xTileMax + x;

    tile = tiles->getTile(currentTileIndex);

    cbSolidUp->setChecked(tile->solidUp);
    cbSolidRight->setChecked(tile->solidRight);
    cbSolidDown->setChecked(tile->solidDown);
    cbSolidLeft->setChecked(tile->solidLeft);
    cbAnimated->setChecked(tile->animated.active);
    cbClimbing->setChecked(tile->climbing);
    cbBreakable->setChecked(tile->breakable);
    cbDangerous->setChecked(tile->dangerous);
    cbHitBonus->setChecked(tile->hitBonus);
    cbTouchBonus->setChecked(tile->touchBonus);
}
//----------------------------------------------------------------------------
void CMainWindow::on_pbAdd_clicked(void) {
    currentMap->add(x, y, currentTileIndex);
    wGamePlay->update();
    wPreview->update();
}
//----------------------------------------------------------------------------
void CMainWindow::on_pbDelete_clicked(void) {
    currentMap->remove(x, y);
    wGamePlay->update();
    wPreview->update();
}
//----------------------------------------------------------------------------
void CMainWindow::on_actNew_triggered(bool) {
    int i;

    fileName = "";

    level.create();
    cbView->clear();
    for(i=0;i<level.getNbLayer();i++) {
        cbView->addItem("Layer "+QString::number(i));
    }

    cbView->setCurrentIndex(0);
    on_cbView_currentIndexChanged(0);
}
//----------------------------------------------------------------------------
void CMainWindow::on_actOpen_triggered(bool) {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Save File"), QString(), tr("Tile data (*.dat)"));

    if(!fileName.isEmpty()) {
        QFile file(fileName);
        if(file.open(QIODevice::ReadOnly)) {
            int i;
            QDataStream stream(&file);

            level.clear();
            stream >> level;

            file.close();

            cbView->clear();
            for(i=0;i<level.getNbLayer();i++) {
                cbView->addItem("Layer "+QString::number(i));
            }

            this->fileName = fileName;

            cbView->setCurrentIndex(0);
            on_cbView_currentIndexChanged(0);
            wGamePlay->setPlayerStartPos(level.getPlayerStartPos());
            wPreview->setPlayerStartPos(level.getPlayerStartPos());

            wGamePlay->setMonsterStartPoss(level.getMonsterStartPoss());
            wPreview->setMonsterStartPoss(level.getMonsterStartPoss());
        }
    }
}
//----------------------------------------------------------------------------
void CMainWindow::on_actSaveAs_triggered(bool) {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(), tr("Tile data (*.dat)"));

    if(!fileName.isEmpty()) {
        QFile file(fileName);
        if(file.open(QIODevice::WriteOnly)) {
            QDataStream stream(&file);

            stream << level;

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

            stream << level;

            file.close();

            this->fileName = fileName;
        }
    }
}
//----------------------------------------------------------------------------
void CMainWindow::on_cbView_currentIndexChanged(int index) {
    currentMap = level.getLayer(index);

    if(index == 0) {
        wGamePlay->setPlayerStartPos(level.getPlayerStartPos());
        wPreview->setPlayerStartPos(level.getPlayerStartPos());

        wGamePlay->setMonsterStartPoss(level.getMonsterStartPoss());
        wPreview->setMonsterStartPoss(level.getMonsterStartPoss());
    } else {
        wGamePlay->setPlayerStartPos(QPoint());
        wPreview->setPlayerStartPos(QPoint());

        wGamePlay->setMonsterStartPoss(QList<QPoint>());
        wPreview->setMonsterStartPoss(QList<QPoint>());
    }

    x = y = 0;

    wGamePlay->setTileMap(currentMap);
    wPreview->setTileMap(currentMap);

    setXY();
}
//----------------------------------------------------------------------------
void CMainWindow::onWGamePlayViewPortChanged(const QPoint& point) {
    wPreview->setViewPort(point.x(), point.y());
}
//----------------------------------------------------------------------------
void CMainWindow::on_pbSetOrigin_clicked(void) {
    QPoint p = QPoint(x, y);

    currentMap->setOrigin(p);
    wPreview->setOrigin(p);
}
//----------------------------------------------------------------------------
void CMainWindow::on_actQuit_triggered(bool) {
    qApp->quit();
}
//----------------------------------------------------------------------------
void CMainWindow::on_pbInsertRow_clicked(void) {
    currentMap->insertRow(y);
    wGamePlay->update();
    wPreview->update();
}
//----------------------------------------------------------------------------
void CMainWindow::on_pbDeleteRow_clicked(void) {
    currentMap->deleteRow(y);
    wGamePlay->update();
    wPreview->update();
}
//----------------------------------------------------------------------------
void CMainWindow::on_pbInsertColumn_clicked(void) {
    currentMap->insertColumn(x);
    wGamePlay->update();
    wPreview->update();
}
//----------------------------------------------------------------------------
void CMainWindow::on_pbDeleteColumn_clicked(void) {
    currentMap->deleteColumn(x);
    wGamePlay->update();
    wPreview->update();
}
//----------------------------------------------------------------------------
void CMainWindow::onWGamePlayMousePress(const int& x, const int& y) {
    this->x = x;
    this->y = y;

    setXY();
}
//----------------------------------------------------------------------------
void CMainWindow::on_pbSetPlayer_clicked(void) {
    level.setPlayerStartPos(x, y);

    wGamePlay->setPlayerStartPos(x, y);
    wPreview->setPlayerStartPos(x, y);

    wGamePlay->update();
    wPreview->update();
}
//----------------------------------------------------------------------------
void CMainWindow::on_pbToggleMonster_clicked(void) {
    level.toggleMonsterStartPoss(x, y);

    wGamePlay->setMonsterStartPoss(level.getMonsterStartPoss());
    wPreview->setMonsterStartPoss(level.getMonsterStartPoss());

    wGamePlay->update();
    wPreview->update();
}
//----------------------------------------------------------------------------
void CMainWindow::on_rbBombe_clicked(void) {
    CTileGame tileGame = currentMap->getTile(x, y);

    tileGame.bonusType = CTileGame::ebtBombe;
    currentMap->setTile(tileGame, x, y);
}
//----------------------------------------------------------------------------
void CMainWindow::on_rbCoin_clicked(void) {
    CTileGame tileGame = currentMap->getTile(x, y);

    tileGame.bonusType = CTileGame::ebtCoin;
    currentMap->setTile(tileGame, x, y);
}
//----------------------------------------------------------------------------
void CMainWindow::on_rbOneUp_clicked(void) {
    CTileGame tileGame = currentMap->getTile(x, y);

    tileGame.bonusType = CTileGame::ebtOneUp;
    currentMap->setTile(tileGame, x, y);
}
//----------------------------------------------------------------------------
void CMainWindow::on_rbFood_clicked(void) {
    CTileGame tileGame = currentMap->getTile(x, y);

    tileGame.bonusType = CTileGame::ebtFood;
    currentMap->setTile(tileGame, x, y);
}
//----------------------------------------------------------------------------
void CMainWindow::on_rbWin_clicked(void) {
    CTileGame tileGame = currentMap->getTile(x, y);

    tileGame.bonusType = CTileGame::ebtWin;
    currentMap->setTile(tileGame, x, y);
}
//----------------------------------------------------------------------------
void CMainWindow::on_leScore_editingFinished(void) {
    CTileGame tileGame = currentMap->getTile(x, y);

    tileGame.score = leScore->text().toInt();
    currentMap->setTile(tileGame, x, y);
}
//----------------------------------------------------------------------------
void CMainWindow::on_actSimulateSFML_triggered(bool) {
    CDialogSimulate d(this);

    d.setLevel(&level);
    d.setTilesImage(&tilesImage);
    d.setTiles(tiles);

    d.exec();
}
//----------------------------------------------------------------------------
void CMainWindow::on_actNewLayer_triggered(bool) {
    int newLayerIndex;

    level.addLayer();

    newLayerIndex = level.getNbLayer() - 1;

    cbView->addItem("Layer "+QString::number(newLayerIndex));
    cbView->setCurrentIndex(newLayerIndex);
}
//----------------------------------------------------------------------------
void CMainWindow::on_actDeleteLayer_triggered(bool) {
    if(level.deleteLayer(cbView->currentIndex())) {
        cbView->setCurrentIndex(0);
    }
}
//----------------------------------------------------------------------------
void CMainWindow::on_actLayerUp_triggered(bool) {
    if(cbView->currentIndex() != 0) {
        level.layerUp(cbView->currentIndex());
        cbView->setCurrentIndex(cbView->currentIndex() - 1);
    }
}
//----------------------------------------------------------------------------
void CMainWindow::on_actLayerDown_triggered(bool) {
    if(cbView->currentIndex() < cbView->count() - 1) {
        level.layerDown(cbView->currentIndex());
        cbView->setCurrentIndex(cbView->currentIndex() + 1);
    }
}
//----------------------------------------------------------------------------
