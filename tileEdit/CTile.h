//----------------------------------------------------------------------------
#ifndef __CTILE_H__
#define __CTILE_H__
//----------------------------------------------------------------------------
class CTile {
public:
    bool solidUp, solidRight, solidDown, solidLeft;
    bool animated;
    bool bistable;
    bool breakable;
    bool bonus;
    bool dangerous;
    QString animatedGroupName;
    QString bistableGroupName;
};
//----------------------------------------------------------------------------
#endif //__CTILE_H__
//----------------------------------------------------------------------------
