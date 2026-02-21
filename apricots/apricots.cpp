// Apricots main program
// Author: M.D.Snellgrove
// Date: 17/3/2002
// History:

// Changed by M Snellgrove 3/8/2003
// Conditional compilation switch for Cygwin (thanks judebert)

#include "apricots.h"

// Definition of Main
// Cygwin expects a WinMain function
#ifdef CYGWIN
WINAPI int WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
#else
int main(int, char **) {
#endif

  atexit(SDL_Quit);
  // Initialize data
  gamedata g;
  init_data(g);

  // Setup game
  setup_game(g);

  // menu
  menu(g);

  // Enter main loop
  game(g);

  // Finish game
  finish_game(g);

  // Shutdown
  g.sound.close(); // << VA : close SDL mixer usage BEFORE  SDL_Quit
  SDL_Quit();  
  //g.sound.close(); // << VA : was ok for OpenAL close after SDL

  return 0;
}
