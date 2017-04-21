//----------------------------------------------------------------------------
#ifndef __CGAME_H__
#define __CGAME_H__
//----------------------------------------------------------------------------
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <CLevel.h>
#include <CTiles.h>
#include <QImage>
//----------------------------------------------------------------------------
class CGame {
public:
    explicit CGame(CTiles *tiles, QImage *tilesImage);
    ~CGame(void);
    void setLevel(CLevel *level);
public:
    void loop(void);
private:
    sf::RenderWindow *window;
    CTiles *tiles;
    CLevel *level;
    QHash<QString, CTilesGroup *> groups;
    QList<QPair<QPoint *, CTileMap *> > layers;
    sf::Texture tilesTexture;
    sf::Sprite tilesSprite;
    sf::Music music;
    char *musicBuffer;

    void updateScene(void);
    void drawScene(void);
    void fromQImage(const QImage& img, sf::Texture * texture, sf::Sprite * sprite);
    void addLayer(CTileMap *tileMap);
    void deleteDatas(void);
    void drawTiles(CTileMap *tileMap, int curX, int curY);
};
//----------------------------------------------------------------------------
#endif //__CGAME_H__
//----------------------------------------------------------------------------
