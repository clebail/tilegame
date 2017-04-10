//----------------------------------------------------------------------------
#include "CSprite.h"
//----------------------------------------------------------------------------
CSprite::CSprite(void) {

}
//----------------------------------------------------------------------------
void CSprite::setSpriteSheet(const QImage& spriteSheet) {
    this->spriteSheet = spriteSheet;
}
//----------------------------------------------------------------------------
QImage CSprite::getSpriteSheet(void) {
    return spriteSheet;
}
//----------------------------------------------------------------------------
int CSprite::getFrameCount(int motionIndex) {
    if(motionIndex >= 0 && motionIndex < NB_MOTION) {
        return motions[motionIndex].size();
    }

    return 0;
}
//----------------------------------------------------------------------------
CSpriteFrame CSprite::getFrame(int motionIndex, int frameIndex) {
    if(motionIndex >= 0 && motionIndex < NB_MOTION) {
        if(frameIndex >= 0 && frameIndex < motions[motionIndex].size()) {
            return motions[motionIndex].at(frameIndex);
        }
    }

    return CSpriteFrame();
}
//----------------------------------------------------------------------------
void CSprite::addFrame(int motionIndex, CSpriteFrame spriteFrame) {
    if(motionIndex >= 0 && motionIndex < NB_MOTION) {
        motions[motionIndex].append(spriteFrame);
    }
}
//----------------------------------------------------------------------------
QDataStream& operator<<(QDataStream& out, const CSprite& sprite) {
    int i;

    out << sprite.spriteSheet;

    for(i=0;i<NB_MOTION;i++) {
        out << sprite.motions[i];
    }

    return out;
}
//-----------------------------------------------------------------------------------------------
QDataStream& operator>>(QDataStream& in, CSprite& sprite) {
    int i;

    in >> sprite.spriteSheet;

    for(i=0;i<NB_MOTION;i++) {
        in >> sprite.motions[i];
    }

    return in;
}
//-----------------------------------------------------------------------------------------------
