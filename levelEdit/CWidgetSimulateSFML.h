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
    void exec(void);
protected:
    virtual QPaintEngine* paintEngine(void) const;
    virtual void showEvent(QShowEvent*);
    virtual void paintEvent(QPaintEvent*);
private:
    bool initialized;

    void init(void);
    void update(void);
};
//----------------------------------------------------------------------------
#endif // __CWIDGETSIMULATESDL_H__
//----------------------------------------------------------------------------
