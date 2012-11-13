#include <MozziGuts.h>
#include <EventDelay.h>
#include <Oscil.h>
#include <tables/sin256_int8.h>
#include <tables/square256_int8.h>
#include <tables/saw256_int8.h>
#include <tables/triangle512_int8.h> //temp!

#define CONTROL_RATE 64

Oscil<SIN256_NUM_CELLS, AUDIO_RATE> sine1(SIN256_DATA), sine2(SIN256_DATA);
Oscil<SAW256_NUM_CELLS, AUDIO_RATE> saw1(SAW256_DATA), saw2(SAW256_DATA), 
                                    sqr1_saw1(SAW256_DATA), sqr1_saw2(SAW256_DATA), sqr2_saw1(SAW256_DATA), sqr2_saw2(SAW256_DATA);
Oscil<TRIANGLE512_NUM_CELLS, AUDIO_RATE> triangle1(TRIANGLE512_DATA), triangle2(TRIANGLE512_DATA);

void setupAudio() {
  startMozzi(CONTROL_RATE);
  
  unsigned int freq = 440u; //A4
  
  sine1.setFreq(freq);
  sqr1_saw1.setFreq(freq);
  sqr1_saw2.setFreq(freq);
  sqr2_saw1.setFreq(freq);
  sqr2_saw2.setFreq(freq);
  saw1.setFreq(freq);
  triangle1.setFreq(freq);
  sine2.setFreq(freq);
  saw2.setFreq(freq);
  triangle2.setFreq(freq);
}

void resetPhase(Oscillator osc, unsigned int channel) {
  if(osc.waveForm == SINE) {
    if(channel == 0) {
      sine1.setPhase(0);
    } else {
      sine2.setPhase(0);
    }
  } else if(osc.waveForm == SQUARE) {
    if(channel == 0) {
      sqr1_saw1.setPhase(0);
      sqr1_saw2.setPhase(osc.pw);
    } else {
      sqr2_saw1.setPhase(0);
      sqr2_saw2.setPhase(osc.pw);
    }
  } else if(osc.waveForm == SAW) {
    if(channel == 0) {
      saw1.setPhase(0);
    } else {
      saw2.setPhase(0);
    }
  } else if(osc.waveForm == TRIANGLE) {
    if(channel == 0) {
      triangle1.setPhase(0);
    } else {
      triangle2.setPhase(0);
    }
  }
}

void changeFreq(Oscillator osc, unsigned int channel) {
  unsigned int freq = (unsigned int)(440u * pow(2, (double)osc.octave));
  float ratio;
  if(osc.tune > 0) {
    ratio = osc.tune * .059463 + 1;
    freq *= ratio;
    Serial.println(freq);
  } else if (osc.tune < 0) {
    ratio = (-osc.tune) * .059463 + 1;
    freq /= ratio;
    Serial.println(freq);
  }

  if(osc.waveForm == SINE) {
    if(channel == 0) {
      sine1.setFreq(freq);
    } else {
      sine2.setFreq(freq);
    }
  } else if(osc.waveForm == SQUARE) {
    if(channel == 0) {
      sqr1_saw1.setFreq(freq);
      sqr1_saw2.setFreq(freq);
    } else {
      sqr2_saw1.setFreq(freq);
      sqr2_saw2.setFreq(freq);
    }
  } else if(osc.waveForm == SAW) {
    if(channel == 0) {
      saw1.setFreq(freq);
    } else {
      saw2.setFreq(freq);
    }
  } else if(osc.waveForm == TRIANGLE) {
    if(channel == 0) {
      triangle1.setFreq(freq);
    } else {
      triangle2.setFreq(freq);
    }
  }
}

int nextSample(WaveForm wv, unsigned int channel) {
  if(wv == SINE) {
    return channel == 0 ? sine1.next() : sine2.next();
  } else if(wv == SQUARE) {
    return channel == 0 ? (sqr1_saw1.next() - sqr1_saw2.next())/2 : (sqr2_saw1.next() - sqr2_saw2.next())/2;
  } else if(wv == SAW) {
    return channel == 0 ? saw1.next() : saw2.next();
  } else if(wv == TRIANGLE) {
    return channel == 0 ? triangle1.next() : triangle2.next();
  }
  
  return 0;
}

WaveForm nextOscillator(Oscillator osc) {
  if(osc.waveForm == SINE) {
    return SQUARE;
  }
  else if(osc.waveForm == SQUARE) {
    return SAW;
  }
  else if(osc.waveForm == SAW) {
    return TRIANGLE;
  }
  else if(osc.waveForm == TRIANGLE) {
    return SILENCE;
  }
  else if(osc.waveForm == SILENCE){
    return SINE;
  }
}

WaveForm prevOscillator(Oscillator osc) {
  if(osc.waveForm == SINE) {
    return SILENCE;
  }
  else if(osc.waveForm == SQUARE) {
    return SINE;
  }
  else if(osc.waveForm == SAW) {
    return SQUARE;
  }
  else if(osc.waveForm == TRIANGLE) {
    return SAW;
  }
  else if(osc.waveForm == SILENCE){
    return TRIANGLE;
  }
}

int updateAudio(){
  int osc1Sample = nextSample(oscStage.osc1.waveForm, 0);
  int osc2Sample = nextSample(oscStage.osc2.waveForm, 1);

  return (int)((osc1Sample * (1 - oscStage.mix)) + (osc2Sample * oscStage.mix));
}
