//----------------------------------------------------------------------------
#ifndef __CWIDGETSIMULATESFML_H__
#define __CWIDGETSIMULATESFML_H__
//----------------------------------------------------------------------------
#include <QWidget>
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <CLevel.h>
#include <CTiles.h>
//----------------------------------------------------------------------------
class CWidgetSimulateSFML : public QWidget, public sf::RenderWindow {
    Q_OBJECT
public:
    explicit CWidgetSimulateSFML(QWidget* parent = 0);
    ~CWidgetSimulateSFML(void);
    void setLevel(CLevel *level);
    void setTiles(CTiles *tiles);
    void setTilesImage(QImage *tilesImage);
    void incX(void);
    void incY(void);
    void decX(void);
    void decY(void);
    void updateAnimate(void);
protected:
    virtual QPaintEngine* paintEngine(void) const;
    virtual void showEvent(QShowEvent*);
    virtual void paintEvent(QPaintEvent*);
private:
    CLevel *level;
    QList<QPair<QPoint *, CTileMap *> > layers;
    CTiles *tiles;
    QHash<QString, CTilesGroup *> groups;
    bool initialized;
    sf::Texture texture, tGentil, tMechant;
    sf::Sprite sprite, sGentil, sMechant;
    sf::Music music;
    char *musicBuffer;

    void updateScene(void);
    void fromQImage(const QImage& img, sf::Texture * texture, sf::Sprite * sprite);
    void drawTiles(CTileMap *tileMap, int curX, int curY);
    void addLayer(CTileMap *tileMap);
};
//----------------------------------------------------------------------------
#endif // __CWIDGETSIMULATESFML_H__
//----------------------------------------------------------------------------
