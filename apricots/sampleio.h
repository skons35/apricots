// 'sampleio' Class Header
// Author: M.D.Snellgrove
// Date: 17/3/2002
// History:

// Changes by M Snellgrove 25/7/2003
//   Conditional Compilation for OpenAL

// VA remove/replace OpenAL and alure libs refs
/*
// OpenAL includes
#include <AL/al.h>
#include <AL/alc.h>
#if defined(__APPLE__)
#include <OpenAL/alure.h>
#else
#include <AL/alure.h>
#endif
*/
#define ALuint unsigned int
#define ALboolean char
#define AL_FALSE 0
#define AL_TRUE 1
// End of VA remove/replace OpenAL and alure libs refs

  // 
#include<SDL_mixer.h>   // VA added, includes #include<SDL_audio.h>  
#include<vector>       // 

#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

// Class header

class sampleio {
private:
  int numsamples;
  int numsources;
  int numpool;
  ALuint *sources;
  bool initdone;
  ALuint *samples;
  int poolcount;
  void psource(int source, int sample, bool loop);
  ALboolean sourceisplaying(ALuint);
  float base_volume;
  // VA Added:
  //std::vector<Mix_Music *> soundsVec;
  std::vector<Mix_Chunk *> soundsVec;

public:
  sampleio();
  void init(float, int, char[][255], int, int);
  void close();
  void update();
  void channel(int, int);
  void loop(int, int);
  void play(int);
  void stop(int);
  void volume(int, double);
};
