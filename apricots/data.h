#include <filesystem>

/* VA added, for CMake based build, explicit value needed in code : */   
#ifndef AP_PATH
// #define AP_PATH "/usr/local/share/apricots/"  //  trailing "/" was doubled when concatenating files name, 
// #define AP_PATH "./data/"                   //    later in code :-( 
// #define AP_PATH "data/"                    //      so changed, and code reviewed for consistency
#define AP_PATH "data" // << correct to use with std filesystem path plus filenames concatenatd using "/" operator
#endif

// font info
struct fontinfo {
  std::filesystem::path path;
  int height;
  int width;
  int chars_count;
};

const fontinfo FONT = {std::filesystem::path(AP_PATH) / "alt-8x16.psf", 16, 8, 256};
