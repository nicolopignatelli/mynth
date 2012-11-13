typedef enum { SILENCE, SINE, SQUARE, SAW, TRIANGLE } WaveForm;

// single oscillator
struct Oscillator {
  Oscillator() : waveForm(SILENCE),tune(0),octave(0),pw(128){}
  
  WaveForm waveForm;
  float tune;
  int octave;
  byte pw;
};

//first synth stage, oscillator couple and 1-2 mix
struct OscStage {
  OscStage() : mix(0.5f){}
  
  Oscillator osc1;
  Oscillator osc2;
  float mix;
};
OscStage oscStage;

//LFO
struct LFO {
  LFO() : waveForm(SILENCE),delay(0){}
  
  WaveForm waveForm;
  unsigned int delay; //milliseconds
};

//second synth stage, two lfo with common rate
struct LFOStage {
  LFOStage() : rate(10.f){}
  
  LFO lfo1;
  LFO lfo2;
  float rate; //0.1 to 20Hz
};
LFOStage lfoStage;

//third stage, Attack/Decay/Sustain/Release
struct ADSRStage {
  unsigned int attack;
  unsigned int decay;
  unsigned int sustain;
  unsigned int release;
};
ADSRStage adsrStage;

//last stage, cutoff and resonance filters
struct FilterStage {
};
FilterStage filterStage;

