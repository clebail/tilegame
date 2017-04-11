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
bool CSpriteFrame::getHurt(void) {
    return hurt;
}
//----------------------------------------------------------------------------
void CSpriteFrame::setHurt(bool hurt) {
    this->hurt = hurt;
}
//----------------------------------------------------------------------------
QString CSpriteFrame::getSoundName(void) {
    return soundName;
}
//----------------------------------------------------------------------------
void CSpriteFrame::setSoundName(QString soundName) {
    this->soundName = soundName;
}
//----------------------------------------------------------------------------
QByteArray CSpriteFrame::getSound(void) {
    return sound;
}
//----------------------------------------------------------------------------
void CSpriteFrame::setSound(const QByteArray& sound) {
    this->sound = sound;
}
//----------------------------------------------------------------------------
QDataStream& operator<<(QDataStream& out, CSpriteFrame * spriteFrame) {
    out << spriteFrame->rect;
    out << spriteFrame->hurt;
    out << spriteFrame->soundName;
    out << spriteFrame->sound;

    return out;
}
//-----------------------------------------------------------------------------------------------
QDataStream& operator>>(QDataStream& in, CSpriteFrame * spriteFrame) {
    in >> spriteFrame->rect;
    in >> spriteFrame->hurt;
    in >> spriteFrame->soundName;
    in >> spriteFrame->sound;

    return in;
}
//-----------------------------------------------------------------------------------------------
