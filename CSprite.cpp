//----------------------------------------------------------------------------
#include "CSprite.h"
//----------------------------------------------------------------------------
CSprite::CSprite(void) {
}
//----------------------------------------------------------------------------
CSprite::~CSprite(void) {
    int i, j;

    for(i=0;i<NB_MOTION;i++) {
        for(j=0;j<motions[i].size();j++) {
            delete motions[i].at(j);
        }

        motions[i].clear();
    }
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
CSpriteFrame * CSprite::getFrame(int motionIndex, int frameIndex) {
    if(motionIndex >= 0 && motionIndex < NB_MOTION) {
        if(frameIndex >= 0 && frameIndex < motions[motionIndex].size()) {
            return motions[motionIndex].at(frameIndex);
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
void CSprite::addFrame(int motionIndex, CSpriteFrame * spriteFrame) {
    if(motionIndex >= 0 && motionIndex < NB_MOTION) {
        motions[motionIndex].append(spriteFrame);
    }
}
//----------------------------------------------------------------------------
void CSprite::swap(int motionIndex, int index1, int index2) {
    if(motionIndex >= 0 && motionIndex < NB_MOTION) {
        motions[motionIndex].swap(index1, index2);
    }
}
//----------------------------------------------------------------------------
void CSprite::deleteFrame(int motionIndex, int frameIndex) {
    if(motionIndex >= 0 && motionIndex < NB_MOTION) {
        if(frameIndex >= 0 && frameIndex < motions[motionIndex].size()) {
            CSpriteFrame *spriteFrame = motions[motionIndex].takeAt(frameIndex);

            delete spriteFrame;
        }
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
