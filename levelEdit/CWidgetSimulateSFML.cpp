//----------------------------------------------------------------------------
#include <QtDebug>
#include <common.h>
#include "CWidgetSimulateSFML.h"

#include <Qt/qx11info_x11.h>
#include <X11/Xlib.h>
//----------------------------------------------------------------------------
CWidgetSimulateSFML::CWidgetSimulateSFML(QWidget *parent) : CWidgetSimulate(parent) {
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    setFocusPolicy(Qt::StrongFocus);

    initialized = false;

    fromQImage(gentil, &tGentil, &sGentil);
    fromQImage(mechant, &tMechant, &sMechant);
}
//----------------------------------------------------------------------------
CWidgetSimulateSFML::~CWidgetSimulateSFML(void) {

}
//----------------------------------------------------------------------------
void CWidgetSimulateSFML::setTilesImage(QImage *tilesImage) {
    CWidgetSimulate::setTilesImage(tilesImage);

    fromQImage(*tilesImage, &texture, &sprite);
}
//----------------------------------------------------------------------------
void CWidgetSimulateSFML::showEvent(QShowEvent*) {
    if (!initialized) {
        XFlush(QX11Info::display());

        sf::RenderWindow::create(winId());

        initialized = true;
    }
}
//----------------------------------------------------------------------------
QPaintEngine* CWidgetSimulateSFML::paintEngine() const {
    return 0;
}
//----------------------------------------------------------------------------
void CWidgetSimulateSFML::paintEvent(QPaintEvent*) {
    update();

    sf::RenderWindow::display();
}
//----------------------------------------------------------------------------
void CWidgetSimulateSFML::update(void) {
    int i;

    sf::RenderWindow::clear(sf::Color(74, 115, 207));

    if(tilesImage != 0 && tiles != 0) {
        if(back != 0) {
            drawTiles(back, xBack, yBack);
        }
        if(front != 0) {
            drawTiles(front, xFront, yFront);
        }

        if(!level->getPlayerStartPos().isNull()) {
            int px = level->getPlayerStartPos().x() * GAME_TILE_WIDTH;
            int py = level->getPlayerStartPos().y() * GAME_TILE_HEIGHT;

            if(px - xFront + GAME_TILE_WIDTH >= 0 && py - yFront + GAME_TILE_HEIGHT >= 0) {
                sGentil.setPosition(px - xFront, py - yFront);
                sf::RenderWindow::draw(sGentil);
            }
        }

        for(i=0;i<level->getMonsterStartPoss().size();i++) {
            QPoint p = level->getMonsterStartPoss().at(i);
            int px = p.x() * GAME_TILE_WIDTH;
            int py = p.y() * GAME_TILE_HEIGHT;

            if(px - xFront + GAME_TILE_WIDTH >= 0 && py - yFront + GAME_TILE_HEIGHT >= 0) {
                sMechant.setPosition(px - xFront, py - yFront);
                sf::RenderWindow::draw(sMechant);
            }
        }
    }
}
//----------------------------------------------------------------------------
void CWidgetSimulateSFML::fromQImage(const QImage& img, sf::Texture * texture, sf::Sprite *sprite) {
    sf::Image image;
    QImage res;

    res = img.rgbSwapped();

    image.create(res.width(), res.height(), reinterpret_cast<const sf::Uint8*>(res.bits()));
    texture->loadFromImage(image);
    sprite->setTexture(*texture);
}
//----------------------------------------------------------------------------
void CWidgetSimulateSFML::drawTiles(CTileMap *tileMap, int curX, int curY) {
    int x, y;

    for(y=0;y<GAME_HEIGHT;y++) {
        int screenY = y * GAME_TILE_HEIGHT;
        int realY = curY + screenY;
        int tileY = realY / GAME_TILE_HEIGHT;
        int h = GAME_TILE_HEIGHT - curY % GAME_TILE_HEIGHT;

        for(x=0;x<GAME_WIDTH;x++) {
            int screenX = x * GAME_TILE_WIDTH;
            int realX = curX + screenX;
            int tileX = realX / GAME_TILE_WIDTH;
            int *tileIdx = tileMap->getTileIndex(tileX, tileY);

            if(tileIdx != 0) {
                CTile * tile = tiles->getTile(*tileIdx);
                if(tile) {
                    int w = GAME_TILE_WIDTH - curX % GAME_TILE_WIDTH;
                    sf::IntRect rectSourceSprite;

                    if(tile->animated.active) {
                        tile = groups.value(tile->animated.groupName)->getCurrentTile();
                    }

                    rectSourceSprite = sf::IntRect(tile->getRealX(), tile->getRealY(), TILE_WIDTH, TILE_HEIGHT);
                    sprite.setPosition(screenX - GAME_TILE_WIDTH + w, screenY - GAME_TILE_HEIGHT + h);
                    sprite.setTextureRect(rectSourceSprite);
                    sf::RenderWindow::draw(sprite);
                }
            }
        }
    }
}
//----------------------------------------------------------------------------
