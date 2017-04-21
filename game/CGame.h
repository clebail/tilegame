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
    void loop(void);
    void init(void);
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
    bool initalized;

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
