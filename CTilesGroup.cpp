//----------------------------------------------------------------------------
#include <QtDebug>
#include "CTilesGroup.h"
//----------------------------------------------------------------------------
CTilesGroup::CTilesGroup(QString name) {
    this->name = name;

    currentTileIndex = -1;
    currentTime = 0;
}
//----------------------------------------------------------------------------
QString CTilesGroup::getName(void) {
    return name;
}
//----------------------------------------------------------------------------
void CTilesGroup::addTile(CTile *tile) {
    tiles.append(tile);
    if(currentTileIndex == -1) {
        currentTileIndex = 0;
    }
}
//----------------------------------------------------------------------------
void CTilesGroup::next(void) {
    if(tiles.size() > 0) {
        currentTime++;
        if(currentTime >= tiles[currentTileIndex]->animated.count) {
            currentTileIndex++;
            currentTime = 0;

            if(currentTileIndex >= tiles.size()) {
                currentTileIndex = 0;
            }
        }
    }
}
//----------------------------------------------------------------------------
void CTilesGroup::reset(void) {
    if(tiles.size() > 0) {
        currentTime = 0;
        currentTileIndex = 0;
    }
}
//----------------------------------------------------------------------------
CTile * CTilesGroup::getCurrentTile(void) {
    return tiles[currentTileIndex];
}
//----------------------------------------------------------------------------
