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
    bool getHurt(void);
    void setHurt(bool hurt);
    QString getSoundName(void);
    void setSoundName(QString soundName);
    QByteArray getSound(void);
    void setSound(const QByteArray& sound);
private:
    QRect rect;
    bool hurt;
    QString soundName;
    QByteArray sound;

    friend QDataStream& operator<<(QDataStream& out, CSpriteFrame * spriteFrame);
    friend QDataStream& operator>>(QDataStream& in, CSpriteFrame * spriteFrame);
};
//----------------------------------------------------------------------------
#endif // __CSPRITEFRAME_H__
//----------------------------------------------------------------------------
