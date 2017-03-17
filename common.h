//----------------------------------------------------------------------------
#ifndef __COMMON_H__
#define __COMMON_H__
//----------------------------------------------------------------------------
#define TILE_WIDTH                  16
#define TILE_HEIGHT                 16
#define SEP_WIDTH                   2
#define SEP_HEIGHT                  2
#define REAL_TILE_WIDTH             (TILE_WIDTH + SEP_WIDTH)
#define REAL_TILE_HEIGHT            (TILE_HEIGHT + SEP_HEIGHT)
#define OFFSET_X                    (2 * SEP_WIDTH)
#define OFFSET_Y                    (2 * SEP_HEIGHT)
#define GAME_TILE_WIDTH             32
#define GAME_TILE_HEIGHT            32
#define GAME_NB_X                   20
#define GAME_NB_Y                   15
#define GAME_WIDTH                  (GAME_TILE_WIDTH * GAME_NB_X)
#define GAME_HEIGHT                 (GAME_TILE_HEIGHT * GAME_NB_Y)
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
#endif //__COMMON_H__
//----------------------------------------------------------------------------

