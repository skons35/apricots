// Wrapper Library for OpenAL
// Author: M.D.Snellgrove
// Date: 17/3/2002
// History:

// Changes by M Snellgrove 26/7/2003
//   Conditional Compilation using OpenAL

// Changes by Judebert 1/8/2003
//   Portability fix for WIN32 systems

// Changes by M Snellgrove 5/8/2003
//   Code cleanup

#include "sampleio.h"

// Constructor
sampleio ::sampleio() { initdone = false; }

// Initialize OpenAL
void sampleio ::init(float the_volume, int nsamples, char filenames[][255], int nsources, int npool) {

  // get list of audio DRIVERS, 
  // given in order normally intialized by default (starting by best to choose)
  /*
  int numAudioDrivers = SDL_GetNumAudioDrivers(); 
  std::cout << "Found audio drivers: " << numAudioDrivers << std::endl;
  if ( 0 == numAudioDrivers )
   {
    std::cerr << "NO audio drivers to init !" << std::endl;
    return;
   }
  // VA tempo display list drivers :
  for (int i = 0; i<numAudioDrivers; i++) 
  {
    std::cout << " - " <<  SDL_GetAudioDriver(i) << std::endl;
  }
  */
  // SDL init DRIVER was already called earlier, simply try to display currently loaded one
  //std::cout << "Curent Audio driver in use : " << SDL_GetCurrentAudioDriver() << std::endl;

  // Now list audio DEVICE(s) to use with this DRIVER
  /*
  int numAudioDevices = SDL_GetNumAudioDevices(0); // 0 for playback devices only
  std::cout << "Playback Audio device(s) found : " << numAudioDevices << std::endl;
  */
  
  // init SDL Mixer () freq used in our sound file, other settings as default)
  if (Mix_OpenAudio(16726, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
  {
    std::cerr << "init() Fails to init SDL Mixer with current settings..." << std::endl;
    return;
  }
  // tempo debug
  //std::cout << "init() initialized SDL Mixer." << std::endl;

  numsamples = nsamples;

  // load wav as Music ready to play in a vector
  for (int i = 0; i < numsamples; i++) 
  {
    Mix_Music* loadedSound = Mix_LoadMUS(filenames[i]);
    soundsVec.push_back( loadedSound );
  }

  // VA tempo debug :
  //std::cout << "vector size of preload Wav : " << soundsVec.size() << std::endl;

  initdone = true;
 

/* //VA tempo remove audio using OpenAL or alure
  if (initdone) {
    cerr << "sampleio: call to init when already in use" << endl;
    exit(EXIT_FAILURE);
  }

  initdone = true;
  numsamples = nsamples;
  numsources = nsources;
  numpool = npool;
  samples = new ALuint[numsamples];
  sources = new ALuint[numsources + numpool];
  poolcount = numsources;
  base_volume = the_volume;

  // Initialize audio device
  alureInitDevice(NULL, NULL);

  ALfloat zeroes[] = {0.0f, 0.0f, 0.0f};
  ALfloat back[] = {0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f};
  ALfloat front[] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};
  ALfloat position[] = {0.0f, 0.0f, -4.0f};

  // Setup Listener
  alListenerfv(AL_POSITION, zeroes);
  alListenerfv(AL_VELOCITY, zeroes);
  alListenerfv(AL_ORIENTATION, front);

  // Load in samples
  alGenBuffers(numsamples, samples);

  for (int i = 0; i < numsamples; i++) {
    // Evil OpenAL portability fix done here
#ifdef _WIN32
    ALenum format;
    ALboolean trash;
    ALsizei filelen;
    alureLoadWAVFile(filenames[i], &format, &data, &filelen, &freq, &trash);
#else
    samples[i] = alureCreateBufferFromFile(filenames[i]);
#endif
    if (samples[i] == AL_NONE) {
      cerr << "sampleio: could not open " << filenames[i] << endl;
      exit(EXIT_FAILURE);
    }
  }

  // Generate Sources
  alGenSources(numsources + numpool, sources);

  for (int j = 0; j < numsources + numpool; j++) {
    alSourcefv(sources[j], AL_POSITION, position);
    alSourcefv(sources[j], AL_VELOCITY, zeroes);
    alSourcefv(sources[j], AL_ORIENTATION, back);
    alSourcef(sources[j], AL_GAIN, ALfloat(base_volume));
  }

  // free(data);
*/ //VA tempo remove audio using OpenAL or alure
}

// Clearup routine

void sampleio ::close() {

  if (initdone) 
  {
    Mix_CloseAudio(); // includes  call to Mix_HaltMusic() stopping current play if any
    // tempo debug
    //std::cout << "close() UNinitialized SDL Mixer." << std::endl;
    
    // clear allocated data    
    while (!soundsVec.empty())
    {  
      Mix_Music* backSound = soundsVec.back();
      Mix_FreeMusic(backSound);
      backSound = NULL;
      soundsVec.pop_back();
    }
    // VA tempo debug :
    //std::cout << "vector size of preload Wav after cleanup : " << soundsVec.size() << std::endl;
  }


/* //VA tempo remove audio using OpenAL or alure
  if (initdone) {
    delete[] samples;
    delete[] sources;
    initdone = false;
    alureShutdownDevice();
  }
*/ //VA tempo remove audio using OpenAL or alure
}

// Update method (blank)

void sampleio ::update() {}

// Play a channel

void sampleio ::channel(int chan, int sample) {
/* //VA tempo remove audio using OpenAL or alure
  if (!initdone) {
    cerr << "sampleio: initialize before use" << endl;
    return;
  }
  if ((chan < 0) || (chan >= numsources)) {
    cerr << "sampleio: attempt to play nonexistant source " << chan << endl;
    return;
  }
  if ((sample < 0) || (sample >= numsamples)) {
    cerr << "sampleio: attempt to play nonexistant sample " << sample << endl;
    return;
  }

  psource(chan, sample, false);
*/ //VA tempo remove audio using OpenAL or alure
}

// Loop a sample

void sampleio ::loop(int chan, int sample) {
/* //VA tempo remove audio using OpenAL or alure

  if (!initdone) {
    cerr << "sampleio: initialize before use" << endl;
    return;
  }
  if ((chan < 0) || (chan >= numsources)) {
    cerr << "sampleio: attempt to play nonexistant source " << chan << endl;
    return;
  }
  if ((sample < 0) || (sample >= numsamples)) {
    cerr << "sampleio: attempt to play nonexistant sample " << sample << endl;
    return;
  }
  psource(chan, sample, true);
*/ //VA tempo remove audio using OpenAL or alure
}

// Play a sample

void sampleio ::play(int sample) {

  if (!initdone) {
    cerr << "play() audio not ready for use !" << endl;
    return;
  }

  Mix_PlayMusic(soundsVec[sample], 0); // 0 for play once and stop



/* //VA tempo remove audio using OpenAL or alure

  if (!initdone) {
    cerr << "sampleio: initialize before use" << endl;
    return;
  }
  if (numpool == 0) {
    cerr << "sampleio: attempt to play nonexistant pool " << endl;
    return;
  }
  if ((sample < 0) || (sample >= numsamples)) {
    cerr << "sampleio: attempt to play nonexistant sample " << sample << endl;
    return;
  }
  poolcount++;
  if (poolcount == numsources + numpool)
    poolcount = numsources;
  psource(poolcount, sample, false);
*/ //VA tempo remove audio using OpenAL or alure
}

// Stop current sample

void sampleio ::stop(int i) {

/* //VA tempo remove audio using OpenAL or alure
  if (!initdone) {
    cerr << "sampleio: initialize before use" << endl;
    return;
  }
  if ((i < 0) || (i >= numsources)) {
    cerr << "sampleio: attempt to stop nonexistant source " << i << endl;
    return;
  }
  if (sourceisplaying(sources[i])) {
    alSourceStop(sources[i]);
  }
*/ //VA tempo remove audio using OpenAL or alure
}

// Actaully start a sample

void sampleio ::psource(int i, int sample, bool loop) {
/* //VA tempo remove audio using OpenAL or alure
	
  // Stop current sample
  if (sourceisplaying(sources[i])) {
    alSourceStop(sources[i]);
  }

  // Change to new sample
  alSourcei(sources[i], AL_BUFFER, samples[sample]);
  if (loop) {
    alSourcei(sources[i], AL_LOOPING, AL_TRUE);
  } else {
    alSourcei(sources[i], AL_LOOPING, AL_FALSE);
  }

  // Play new sample
  alSourcePlay(sources[i]);
*/ //VA tempo remove audio using OpenAL or alure
}

// Volume control function

void sampleio ::volume(int i, double vol) {
/* //VA tempo remove audio using OpenAL or alure

  if (!initdone) {
    cerr << "sampleio: initialize before use" << endl;
    return;
  }
  if ((i < 0) || (i >= numsources)) {
    cerr << "sampleio: attempt to volume nonexistant source " << i << endl;
    return;
  }
  alSourcef(sources[i], AL_GAIN, ALfloat(vol * base_volume));
*/ //VA tempo remove audio using OpenAL or alure
}

// Check on playing sources function

ALboolean sampleio ::sourceisplaying(ALuint sid) {
/* //VA tempo remove audio using OpenAL or alure

  ALint state;
  if (alIsSource(sid) == AL_FALSE) {
    return AL_FALSE;
  }
  state = AL_INITIAL;

  // Evil OpenAL portability fix done here
#ifdef _WIN32
  alGetSourcei(sid, AL_SOURCE_STATE, &state);
#else
  alGetSourceiv(sid, AL_SOURCE_STATE, &state);
#endif

  switch (state) {
  case AL_PLAYING:
  case AL_PAUSED:
    return AL_TRUE;
  default:
    break;
  }
  */ //VA tempo remove audio using OpenAL or alure
  return AL_FALSE;
}
