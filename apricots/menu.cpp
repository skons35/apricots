// Apricots finish game routine
// Author: M.D.Snellgrove
// Date: 26/3/2002
// History:

// Changes by M Harman for Windows version, June 2003:
//   Changes for graphics and font related stuff.

// Changes by M Snellgrove 15/7/2003
//   SDLfont used for fonts

#include "apricots.h"

// Draw a winnerbox

void menubox(gamedata &g) {

  int boxcolour = 4; // red
  SDL_Rect rect;
  rect.x = 200;
  rect.y = 64;
  rect.w = 240;
  rect.h = 80;
  SDL_FillRect(g.virtualscreen, &rect, 1);
  rect.x = 201;
  rect.y = 65;
  rect.w = 238;
  rect.h = 78;
  SDL_FillRect(g.virtualscreen, &rect, boxcolour);

  char apricotsstring[] = "Apricots!";
  g.whitefont.writemask(g.virtualscreen, 288, 72, apricotsstring);
  char start[] = "Press any key";
  g.whitefont.writemask(g.virtualscreen, 260, 122, start);
}

// Main finish game routine

void menu(gamedata &g) {

  // Update display
  SDL_Rect rect;
  rect.x = 0;
  rect.y = 0;
  rect.w = SCREEN_WIDTH;
  rect.h = SCREEN_HEIGHT;

  Uint32 next_time = SDL_GetTicks() + TICK_INTERVAL;

  SDL_Event event;
  while (true) {
    SDL_PollEvent(&event);
    if (event.type == SDL_KEYDOWN) {
      break;
    }
    all(g);
    drawall(g);
    menubox(g);
    updateScreen(g);

    // Delay for time remaining in TICK_INTERVAL
    SDL_Delay(time_left(next_time));
    next_time = SDL_GetTicks() + TICK_INTERVAL;
  }
}
