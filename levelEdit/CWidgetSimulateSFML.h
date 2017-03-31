//----------------------------------------------------------------------------
#ifndef __CWIDGETSIMULATESDL_H__
#define __CWIDGETSIMULATESDL_H__
//----------------------------------------------------------------------------
#include <SFML/Graphics.hpp>
#include "CWidgetSimulate.h"
//----------------------------------------------------------------------------
class CWidgetSimulateSFML : public CWidgetSimulate, public sf::RenderWindow {
public:
    explicit CWidgetSimulateSFML(QWidget* parent = 0);
    ~CWidgetSimulateSFML(void);
    virtual void setTilesImage(QImage *tilesImage);
protected:
    virtual QPaintEngine* paintEngine(void) const;
    virtual void showEvent(QShowEvent*);
    virtual void paintEvent(QPaintEvent*);
private:
    bool initialized;
    sf::Texture texture;
    sf::Sprite sprite;

    void update(void);
};
//----------------------------------------------------------------------------
#endif // __CWIDGETSIMULATESDL_H__
//----------------------------------------------------------------------------
