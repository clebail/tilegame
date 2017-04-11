//----------------------------------------------------------------------------
#ifndef __CSPRITE_H__
#define __CSPRITE_H__
//----------------------------------------------------------------------------
#include <QImage>
#include <QList>
#include <QDataStream>
#include <CSpriteFrame.h>
//----------------------------------------------------------------------------
#define NB_MOTION                   9
//----------------------------------------------------------------------------
class CSprite {
public:
    typedef enum  { emNothing = 0, emWalk, emJump, emClimb, emHit, emBomb, emGameOver, emWin, emStroke } EMotion;

    explicit CSprite(void);
    ~CSprite(void);
    void setSpriteSheet(const QImage& spriteSheet);
    QImage getSpriteSheet(void);
    int getFrameCount(int motionIndex);
    CSpriteFrame * getFrame(int motionIndex, int frameIndex);
    void addFrame(int motionIndex, CSpriteFrame * spriteFrame);
private:
    QImage spriteSheet;
    QList<CSpriteFrame *> motions[NB_MOTION];

    friend QDataStream& operator<<(QDataStream& out, const CSprite& sprite);
    friend QDataStream& operator>>(QDataStream& in, CSprite& sprite);
};
//----------------------------------------------------------------------------
#endif // __CSPRITE_H__
//----------------------------------------------------------------------------
