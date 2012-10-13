#include <EventDelay.h>

#define PIN_SWITCH_OSC1 10
#define PIN_SWITCH_OSC2 11

EventDelay switch1Delay = EventDelay(CONTROL_RATE);
EventDelay switch2Delay = EventDelay(CONTROL_RATE);
byte switchOsc1Pressed = 0;
byte switchOsc2Pressed = 0;

void updateInput(){
  if(digitalRead(PIN_SWITCH_OSC1) == LOW && switch1Delay.ready()) {
    switchOsc1Pressed = 1;
  }
  
  if(digitalRead(PIN_SWITCH_OSC2) == LOW && switch2Delay.ready()) {
    switchOsc2Pressed = 1;
  }
}

void setupInput() {
  switch1Delay.set(200);
  switch2Delay.set(200);
  switch1Delay.start();
  switch2Delay.start();
  
  pinMode(PIN_SWITCH_OSC1, INPUT);
  pinMode(PIN_SWITCH_OSC2, INPUT);
  
  digitalWrite(PIN_SWITCH_OSC1, HIGH);
  digitalWrite(PIN_SWITCH_OSC2, HIGH);
}


