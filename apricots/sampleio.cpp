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
