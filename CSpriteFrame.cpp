//----------------------------------------------------------------------------
#include "CSpriteFrame.h"
//----------------------------------------------------------------------------
CSpriteFrame::CSpriteFrame(void) {

}
//----------------------------------------------------------------------------
QRect CSpriteFrame::getRect(void) {
    return rect;
}
//----------------------------------------------------------------------------
void CSpriteFrame::setRect(QRect rect) {
    this->rect = rect;
}
//----------------------------------------------------------------------------
QDataStream& operator<<(QDataStream& out, const CSpriteFrame& spriteFrame) {
    out << spriteFrame.rect;
    out << spriteFrame.hurt;
    out << spriteFrame.soundName;
    out << spriteFrame.sound;

    return out;
}
//-----------------------------------------------------------------------------------------------
QDataStream& operator>>(QDataStream& in, CSpriteFrame& spriteFrame) {
    in >> spriteFrame.rect;
    in >> spriteFrame.hurt;
    in >> spriteFrame.soundName;
    in >> spriteFrame.sound;

    return in;
}
//-----------------------------------------------------------------------------------------------
