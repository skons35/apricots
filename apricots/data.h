#include <filesystem>

/* VA added, for CMake based build, explicit value needed in code : */   
#ifndef AP_PATH
// #define AP_PATH "/usr/local/share/apricots/"
 #define AP_PATH "./data/"
#endif

// font info
struct fontinfo {
  std::filesystem::path path;
  int height;
  int width;
  int chars_count;
};

const fontinfo FONT = {std::filesystem::path(AP_PATH) / "alt-8x16.psf", 16, 8, 256};
