//----------------------------------------------------------------------------
#include <QtDebug>
#include <common.h>
#include "CWidgetSimulateSFML.h"

#include <Qt/qx11info_x11.h>
#include <X11/Xlib.h>
//----------------------------------------------------------------------------
#define INC             (GAME_TILE_WIDTH / 2)
//----------------------------------------------------------------------------
CWidgetSimulateSFML::CWidgetSimulateSFML(QWidget *parent) : QWidget(parent) {
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

    for(int j=0;j<layers.size();j++) {
        QPair<QPoint *, CTileMap *> pair = layers.at(j);

        delete pair.first;
    }
}
//----------------------------------------------------------------------------
void CWidgetSimulateSFML::setLevel(CLevel *level) {
    int i;
    this->level = level;

    for(i=0;i<level->getNbLayer();i++) {
        addLayer(level->getLayer(i));
    }

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
    int i;

    for(i=0;i<layers.size();i++) {
        QPair<QPoint *, CTileMap *> pair = layers.at(i);
        QPoint *p = pair.first;
        CTileMap *tileMap = pair.second;

        if(p->x() + GAME_WIDTH < tileMap->getSize().width() * GAME_TILE_WIDTH) {
            p->rx() += INC / (1 << i);
        }
    }
}
//----------------------------------------------------------------------------
void CWidgetSimulateSFML::incY(void) {
    int i;

    for(i=0;i<layers.size();i++) {
        QPair<QPoint *, CTileMap *> pair = layers.at(i);
        QPoint *p = pair.first;
        CTileMap *tileMap = pair.second;

        if(p->y() + GAME_HEIGHT < tileMap->getSize().height() * GAME_TILE_HEIGHT) {
            p->ry() += INC / (1 << i);
        }
    }
}
//----------------------------------------------------------------------------
void CWidgetSimulateSFML::decX(void) {
    int i;

    for(i=0;i<layers.size();i++) {
        QPair<QPoint *, CTileMap *> pair = layers.at(i);
        QPoint *p = pair.first;
        int inc = INC / (1 << i);

        if(p->x() >= inc) {
            p->rx() -= inc;
        }
    }
}
//----------------------------------------------------------------------------
void CWidgetSimulateSFML::decY(void) {
    int i;

    for(i=0;i<layers.size();i++) {
        QPair<QPoint *, CTileMap *> pair = layers.at(i);
        QPoint *p = pair.first;
        int inc = INC / (1 << i);

        if(p->y() >= inc) {
            p->ry() -= inc;
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
        QPoint *p = 0;
        CTileMap *tileMap = 0;

        for(i=layers.size()-1;i>=0;i--) {
            QPair<QPoint *, CTileMap *> pair = layers.at(i);
            p = pair.first;
            tileMap = pair.second;

            drawTiles(tileMap, p->x(), p->y());
        }

        if(p != 0 && tileMap != 0) {
            if(!level->getPlayerStartPos().isNull()) {
                int px = level->getPlayerStartPos().x() * GAME_TILE_WIDTH;
                int py = level->getPlayerStartPos().y() * GAME_TILE_HEIGHT;

                if(px - p->x() + GAME_TILE_WIDTH >= 0 && py - p->y() + GAME_TILE_HEIGHT >= 0) {
                    sf::FloatRect r = sGentil.getGlobalBounds();
                    sGentil.setPosition(px - p->x(), py - p->y() - r.height + GAME_TILE_HEIGHT);
                    sf::RenderWindow::draw(sGentil);
                }
            }

            for(i=0;i<level->getMonsterStartPoss().size();i++) {
                QPoint mp = level->getMonsterStartPoss().at(i);
                int px = mp.x() * GAME_TILE_WIDTH;
                int py = mp.y() * GAME_TILE_HEIGHT;

                if(px - p->x() + GAME_TILE_WIDTH >= 0 && py - p->y() + GAME_TILE_HEIGHT >= 0) {
                    sMechant.setPosition(px - p->x(), py - p->y());
                    sf::RenderWindow::draw(sMechant);
                }
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
void CWidgetSimulateSFML::addLayer(CTileMap *tileMap) {
    QPoint *p = new QPoint(tileMap->getOrigin().x() * GAME_TILE_WIDTH, tileMap->getOrigin().y() * GAME_TILE_HEIGHT);
    QPair<QPoint *, CTileMap *> pair(p, tileMap);

    layers.append(pair);
}
//----------------------------------------------------------------------------
