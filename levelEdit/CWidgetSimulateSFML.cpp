//----------------------------------------------------------------------------
#include <QtDebug>
#include <common.h>
#include "CWidgetSimulateSFML.h"

#include <Qt/qx11info_x11.h>
#include <X11/Xlib.h>
//----------------------------------------------------------------------------
#define INC_FRONT           10
#define INC_BACK            (INC_FRONT / 2)
//----------------------------------------------------------------------------
CWidgetSimulateSFML::CWidgetSimulateSFML(QWidget *parent) : QWidget(parent) {
    front = back = 0;
    tiles = 0;

    QImage gentil(":/levelEdit/images/gentil.png");
    QImage mechant(":/levelEdit/images/mechant.png");

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
    QHashIterator<QString, CTilesGroup *> i(groups);
    while (i.hasNext()) {
        i.next();

        delete i.value();
    }
}
//----------------------------------------------------------------------------
void CWidgetSimulateSFML::setLevel(CLevel *level) {
    this->level = level;
    front = level->getFront();
    back = level->getBack();

    xFront = front->getOrigin().x() * GAME_TILE_WIDTH;
    yFront = front->getOrigin().y() * GAME_TILE_HEIGHT;

    xBack = back->getOrigin().x() * GAME_TILE_WIDTH;
    yBack = back->getOrigin().y() * GAME_TILE_HEIGHT;

    repaint();
}
//----------------------------------------------------------------------------
void CWidgetSimulateSFML::setTiles(CTiles *tiles) {
    this->tiles = tiles;

    groups = tiles->getGroups();

    repaint();
}
//----------------------------------------------------------------------------
void CWidgetSimulateSFML::setTilesImage(QImage *tilesImage) {
    fromQImage(*tilesImage, &texture, &sprite);

    repaint();
}
//----------------------------------------------------------------------------
void CWidgetSimulateSFML::incX(void) {
    if(front != 0 && back != 0) {
        if(xFront + GAME_WIDTH < front->getSize().width() * GAME_TILE_WIDTH) {
            xFront += INC_FRONT;
        }

        if(xBack + GAME_WIDTH < back->getSize().width() * GAME_TILE_WIDTH) {
            xBack += INC_BACK;
        }
    }
}
//----------------------------------------------------------------------------
void CWidgetSimulateSFML::incY(void) {
    if(front != 0 && back != 0) {
        if(yFront + GAME_HEIGHT < front->getSize().height() * GAME_TILE_HEIGHT) {
            yFront += INC_FRONT;
        }

        if(yBack + GAME_HEIGHT < back->getSize().height() * GAME_TILE_HEIGHT) {
            yBack += INC_BACK;
        }
    }
}
//----------------------------------------------------------------------------
void CWidgetSimulateSFML::decX(void) {
    if(front != 0 && back != 0) {
        if(xFront >= INC_FRONT) {
            xFront -= INC_FRONT;
        }

        if(xBack >= INC_BACK) {
            xBack -= INC_BACK;
        }
    }
}
//----------------------------------------------------------------------------
void CWidgetSimulateSFML::decY(void) {
    if(front != 0 && back != 0) {
        if(yFront >= INC_FRONT) {
            yFront -= INC_FRONT;
        }

        if(yBack >= INC_BACK) {
            yBack -= INC_BACK;
        }
    }
}
//----------------------------------------------------------------------------
void CWidgetSimulateSFML::updateAnimate(void) {
    QHashIterator<QString, CTilesGroup *> i(groups);
    while (i.hasNext()) {
        i.next();

        i.value()->next();
    }
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
    updateScene();

    sf::RenderWindow::display();
}
//----------------------------------------------------------------------------
void CWidgetSimulateSFML::updateScene(void) {
    int i;

    sf::RenderWindow::clear(sf::Color(74, 115, 207));

    if(tiles != 0) {
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
