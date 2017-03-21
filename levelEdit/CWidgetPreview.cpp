//----------------------------------------------------------------------------
#include <QPainter>
#include <common.h>
#include "CWidgetPreview.h"
//----------------------------------------------------------------------------
CWidgetPreview::CWidgetPreview(QWidget *parent) : QWidget(parent) {
    tilesImage = 0;
    tileMap = 0;
    xTileMax = 0;

    origin = QPoint(0, 0);

    backImage = QImage(":/levelEdit/images/fond.png");
}
//----------------------------------------------------------------------------
void CWidgetPreview::setTilesImage(QImage *tilesImage) {
    this->tilesImage = tilesImage;
    xTileMax = (tilesImage->size().width() - 2 * OFFSET_X) / REAL_TILE_WIDTH + 1;

    repaint();
}
//----------------------------------------------------------------------------
void CWidgetPreview::setTileMap(CTileMap *tileMap) {
    this->tileMap = tileMap;
    origin.setX(tileMap->getOrigin().x());
    origin.setY(tileMap->getOrigin().y());

    repaint();
}
//----------------------------------------------------------------------------
void CWidgetPreview::setViewPort(int x, int y) {
    viewPortX = x;
    viewPortY = y;

    repaint();
}
//----------------------------------------------------------------------------
void CWidgetPreview::setOrigin(const QPoint& p) {
    origin.setX(p.x());
    origin.setY(p.y());

    repaint();
}
//----------------------------------------------------------------------------
void CWidgetPreview::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    if(tileMap != 0 && tilesImage != 0) {
        drawMap(&painter);
    }
}
//----------------------------------------------------------------------------
void CWidgetPreview::drawBackground(QPainter *painter) {
    int x, y;
    QSize size = tileMap->getSize();

    for(y=0;y<size.height() * GAME_TILE_HEIGHT;y+=backImage.height()) {
        for(x=0;x<size.width() * GAME_TILE_WIDTH;x+=backImage.width()) {
            painter->drawImage(QPoint(x, y), backImage);
        }
    }
}
//----------------------------------------------------------------------------
void CWidgetPreview::drawMap(QPainter *painter) {
    int x, y;
    double w, h;
    int mX, mY;
    QSize size = tileMap->getSize();

    if(size.height() != 0 && size.width() != 0) {
        QPen pen(Qt::blue);
        QRect viewPort;;
        pen.setStyle(Qt::DotLine);
        pen.setWidth(2);

        w = ((double)this->size().width()) / ((double)size.width());
        h = ((double)this->size().height()) / ((double)size.height());

        if(w <= h) {
            h = w;
        }else {
            w = h;
        }

        mX = (this->size().width() - (w * size.width())) / 2;
        mY = (this->size().height() - (h * size.height())) / 2;

        viewPort = QRect(viewPortX * w + mX, viewPortY * h + mY, w * GAME_NB_X, h * GAME_NB_Y);

        for(y=0;y<size.height();y++) {
            for(x=0;x<size.width();x++) {
                int *tileIndex = tileMap->getTile(x, y);
                QRect dst(x * w + mX, y * h + mY, w, h);

                painter->drawImage(dst, backImage);
                if(tileIndex != 0) {
                    int xTile = (*tileIndex) % xTileMax;
                    int yTile = (*tileIndex) / xTileMax;

                    QRect src(xTile * REAL_TILE_WIDTH + OFFSET_X, yTile * REAL_TILE_HEIGHT + OFFSET_Y, TILE_WIDTH, TILE_HEIGHT);

                    painter->drawImage(dst, *tilesImage, src);
                }
            }
        }

        painter->setBrush(Qt::NoBrush);
        painter->setPen(pen);
        painter->drawRect(viewPort);

        pen.setColor(Qt::red);
        pen.setWidth(1);

        painter->setBrush(Qt::red);
        painter->setPen(pen);
        painter->drawEllipse(QPoint(origin.x() * w + mX, origin.y() * h + mY),(int)(w / 5), (int)(h / 5));
    }
}
//----------------------------------------------------------------------------
