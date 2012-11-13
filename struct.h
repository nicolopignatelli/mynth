typedef enum { SILENCE, SINE, SQUARE, SAW, TRIANGLE } WaveForm;

// single oscillator
struct Oscillator {
  Oscillator() : waveForm(SILENCE),tune(0),octave(0),pw(50){}
  
  WaveForm waveForm;
  byte tune;
  byte octave;
  byte pw;
};

//first synth stage, oscillator couple and 1-2 mix
struct OscStage {
  OscStage() : mix(50){}
  
  Oscillator osc1;
  Oscillator osc2;
  byte mix;
};
