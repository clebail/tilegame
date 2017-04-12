//----------------------------------------------------------------------------
#include <QtDebug>
#include "CSprite.h"
//----------------------------------------------------------------------------
CSprite::CSprite(void) {
}
//----------------------------------------------------------------------------
CSprite::~CSprite(void) {
    clear();
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
void CSprite::clear(void) {
    int i, j;

    for(i=0;i<NB_MOTION;i++) {
        for(j=0;j<motions[i].size();j++) {
            delete motions[i].at(j);
        }

        motions[i].clear();
    }

    spriteSheet = QImage();
}
//----------------------------------------------------------------------------
QDataStream& operator<<(QDataStream& out, const CSprite& sprite) {
    int i, j;

    out << sprite.spriteSheet;

    for(i=0;i<NB_MOTION;i++) {
        out << sprite.motions[i].size();
        for(j=0;j<sprite.motions[i].size();j++) {
            out << sprite.motions[i].at(j);
        }
    }

    return out;
}
//-----------------------------------------------------------------------------------------------
QDataStream& operator>>(QDataStream& in, CSprite& sprite) {
    int i, j;

    in >> sprite.spriteSheet;

    for(i=0;i<NB_MOTION;i++) {
        int nbFrame;

        in >> nbFrame;
        for(j=0;j<nbFrame;j++) {
            CSpriteFrame *spriteFrame = new CSpriteFrame();

            in >> spriteFrame;
            sprite.motions[i].append(spriteFrame);
        }
    }

    return in;
}
//-----------------------------------------------------------------------------------------------
