//----------------------------------------------------------------------------
#ifndef __CSPRITEFRAME_H__
#define __CSPRITEFRAME_H__
//----------------------------------------------------------------------------
#include <QRect>
#include <QDataStream>

//----------------------------------------------------------------------------
class CSpriteFrame {
public:
    explicit CSpriteFrame(void);
    QRect getRect(void);
    void setRect(QRect rect);
private:
    QRect rect;
    bool hurt;
    QString soundName;
    QByteArray sound;

    friend QDataStream& operator<<(QDataStream& out, const CSpriteFrame& spriteFrame);
    friend QDataStream& operator>>(QDataStream& in, CSpriteFrame& spriteFrame);
};
//----------------------------------------------------------------------------
#endif // __CSPRITEFRAME_H__
//----------------------------------------------------------------------------
