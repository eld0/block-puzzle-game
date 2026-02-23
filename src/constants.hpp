#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL2/SDL_pixels.h>
#define FALSE 0
#define TRUE 1

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)

#define LEVEL_UP_THRLD 10
#define INITIAL_SPEED 8

typedef unsigned char byte_t;

// #define GAME_FONT "/usr/share/fonts/TTF/DejaVuSans.ttf"
#define GAME_FONT "rexlia.ttf"

inline const SDL_Color SDL_FC_WHITE{200, 200, 200, 255};
inline const SDL_Color SDL_FC_GRAY{120, 120, 120, 255};
inline const SDL_Color SDL_FC_LYELLOW{252, 244, 163, 255};

#endif // !CONSTANTS_H
