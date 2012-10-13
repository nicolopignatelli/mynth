#include <MozziGuts.h>
#include <EventDelay.h>
#include <Oscil.h>
#include <tables/sin256_int8.h>
#include <tables/square256_int8.h>
#include <tables/saw256_int8.h>
#include <tables/triangle256_int8.h>

#define CONTROL_RATE 64

char* current_osc1 = "---";
char* current_osc2 = "---";
Oscil<SIN256_NUM_CELLS, AUDIO_RATE> sine1(SIN256_DATA), sine2(SIN256_DATA);
Oscil<SQUARE256_NUM_CELLS, AUDIO_RATE> sqr1(SQUARE256_DATA), sqr2(SQUARE256_DATA);
Oscil<SAW256_NUM_CELLS, AUDIO_RATE> saw1(SAW256_DATA), saw2(SAW256_DATA);
Oscil<TRIANGLE256_NUM_CELLS, AUDIO_RATE> triangle1(TRIANGLE256_DATA), triangle2(TRIANGLE256_DATA);

void setupAudio() {
  startMozzi(CONTROL_RATE);
  
  sine1.setFreq(440u);
  sqr1.setFreq(440u);
  saw1.setFreq(440u);
  triangle1.setFreq(440u);
  sine2.setFreq(440u);
  sqr2.setFreq(440u);
  saw2.setFreq(440u);
  triangle2.setFreq(440u);
}

int nextSample(char* osc, unsigned int channel) {
  if(osc == "sine") {
    return channel == 0 ? sine1.next() : sine2.next();
  }
  else if(osc == "square") {
    return channel == 0 ? sqr1.next() : sqr2.next();
  }
  else if(osc == "saw") {
    return channel == 0 ? saw1.next() : saw2.next();
  }
  else if(osc == "triangle") {
    return channel == 0 ? triangle1.next() : triangle2.next();
  }
  
  return 0;
}

void resetPhases() {
  sine1.setPhase(0);
  sqr1.setPhase(0);
  saw1.setPhase(0);
  triangle1.setPhase(0);
  sine2.setPhase(0);
  sqr2.setPhase(0);
  saw2.setPhase(0);
  triangle2.setPhase(0);
}

char* nextOscillator(char* osc) {
  resetPhases();
  
  if(osc == "sine") {
    return "square";
  }
  else if(osc == "square") {
    return "saw";
  }
  else if(osc == "saw") {
    return "triangle";
  }
  else if(osc == "triangle") {
    return "---";
  }
  else if(osc == "---"){
    return "sine";
  }
}

int updateAudio(){
  return (int)((nextSample(current_osc1, 0) + nextSample(current_osc2, 1))/2);
}
