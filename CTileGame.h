//----------------------------------------------------------------------------
#ifndef __CTILEGAME_H__
#define __CTILEGAME_H__
//----------------------------------------------------------------------------
#include <QDataStream>
//----------------------------------------------------------------------------
class CTileGame {
public:
    typedef enum { ebtNone = 0, ebtBombe, ebtOneUp, ebtFood, ebtCoin, ebtWin } EBonusType;

    int *tileIndex;
    int score;
    EBonusType bonusType;

    explicit CTileGame(void);
private:
    friend QDataStream& operator<<(QDataStream& out, const CTileGame& tileGame);
    friend QDataStream& operator>>(QDataStream& in, CTileGame& tileGame);
};
//----------------------------------------------------------------------------
#endif //__CTILEGAME_H__
//----------------------------------------------------------------------------
