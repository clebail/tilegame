//----------------------------------------------------------------------------
#ifndef __CWIDGETSIMULATESDL_H__
#define __CWIDGETSIMULATESDL_H__
//----------------------------------------------------------------------------
#include <SFML/Graphics.hpp>
#include "CWidgetSimulate.h"
//----------------------------------------------------------------------------
class CWidgetSimulateSFML : public CWidgetSimulate, public sf::RenderWindow {
    Q_OBJECT
public:
    explicit CWidgetSimulateSFML(QWidget* parent = 0);
    ~CWidgetSimulateSFML(void);
    void setTilesImage(QImage *tilesImage);
protected:
    virtual QPaintEngine* paintEngine(void) const;
    virtual void showEvent(QShowEvent*);
    virtual void paintEvent(QPaintEvent*);
private:
    bool initialized;
    sf::Texture texture, tGentil, tMechant;
    sf::Sprite sprite, sGentil, sMechant;

    void update(void);
    void fromQImage(const QImage& img, sf::Texture * texture, sf::Sprite * sprite);
    void drawTiles(CTileMap *tileMap, int curX, int curY);
};
//----------------------------------------------------------------------------
#endif // __CWIDGETSIMULATESDL_H__
//----------------------------------------------------------------------------
