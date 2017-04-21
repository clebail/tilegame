//----------------------------------------------------------------------------
#include <common.h>
#include <QApplication>
#include <QKeyEvent>
#include <QtDebug>
#include "CGame.h"
#include <sys/time.h>
#include <unistd.h>

#include <Qt/qx11info_x11.h>
#include <X11/Xlib.h>
//----------------------------------------------------------------------------
CGame::CGame(CTiles *tiles, QImage *tilesImage) {
    window = new sf::RenderWindow(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), "Game");

    this->tiles = tiles;
    fromQImage(*tilesImage, &tilesTexture, &tilesSprite);

    groups = this->tiles->getGroups();
}
//----------------------------------------------------------------------------
CGame::~CGame(void) {
    QHashIterator<QString, CTilesGroup *> i(groups);
    while (i.hasNext()) {
        i.next();

        delete i.value();
    }

    deleteDatas();

    delete window;
}
//----------------------------------------------------------------------------
void CGame::setLevel(CLevel *level) {
    int i;
    QByteArray baMusic;

    deleteDatas();

    this->level = level;
    baMusic = level->getMusic();

    for(i=0;i<level->getNbLayer();i++) {
        addLayer(level->getLayer(i));
    }

    if(baMusic.size() != 0) {
        musicBuffer = new char[baMusic.size()];
        memcpy(musicBuffer, baMusic.data(), baMusic.size());
    }

    if(music.openFromMemory((const void *)musicBuffer, baMusic.size())) {
        music.setLoop(true);
        music.play();
    }
}
//----------------------------------------------------------------------------
void CGame::loop(void) {
    sf::Clock clock;

    do {
        sf::Event event;
        int debut = clock.getElapsedTime().asMilliseconds();
        int fin;

        updateScene();
        drawScene();

        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }

        fin = clock.getElapsedTime().asMilliseconds();
        usleep((40 - (fin - debut)) * 1000);
    }while(window->isOpen());
}
//----------------------------------------------------------------------------
void CGame::updateScene(void) {
    QHashIterator<QString, CTilesGroup *> i(groups);
    while (i.hasNext()) {
        i.next();

        i.value()->next();
    }
}
//----------------------------------------------------------------------------
void CGame::drawScene(void) {
    int i;

    window->clear(sf::Color(74, 115, 207));

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
            /*if(!level->getPlayerStartPos().isNull()) {
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
            }*/
        }
    }

    window->display();
}
//----------------------------------------------------------------------------
void CGame::fromQImage(const QImage& img, sf::Texture * texture, sf::Sprite *sprite) {
    sf::Image image;
    QImage res;

    res = img.rgbSwapped();

    image.create(res.width(), res.height(), reinterpret_cast<const sf::Uint8*>(res.bits()));
    texture->loadFromImage(image);
    sprite->setTexture(*texture);
}
//----------------------------------------------------------------------------
void CGame::addLayer(CTileMap *tileMap) {
    QPoint *p = new QPoint(tileMap->getOrigin().x() * GAME_TILE_WIDTH, tileMap->getOrigin().y() * GAME_TILE_HEIGHT);
    QPair<QPoint *, CTileMap *> pair(p, tileMap);

    layers.append(pair);
}
//----------------------------------------------------------------------------
void CGame::deleteDatas(void) {
    for(int j=0;j<layers.size();j++) {
        QPair<QPoint *, CTileMap *> pair = layers.at(j);

        delete pair.first;
    }

    if(musicBuffer != 0 && music.getStatus() == sf::SoundSource::Playing) {
        music.stop();
        delete[] musicBuffer;
    }
}
//----------------------------------------------------------------------------
void CGame::drawTiles(CTileMap *tileMap, int curX, int curY) {
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
                    tilesSprite.setPosition(screenX - GAME_TILE_WIDTH + w, screenY - GAME_TILE_HEIGHT + h);
                    tilesSprite.setTextureRect(rectSourceSprite);
                    window->draw(tilesSprite);
                }
            }
        }
    }
}
//----------------------------------------------------------------------------
