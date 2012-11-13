#include <EventDelay.h>

#define PIN_ROTENC_A 14
#define PIN_ROTENC_B 15
#define ROTENC_PORT PINC
#define PIN_ROTENC_SWITCH 10
#define ROTARY_STATE_DEFAULT 128

EventDelay switchDelay = EventDelay(CONTROL_RATE);
boolean rotaryLeft = false;
boolean rotaryRight = false;
boolean rotarySwitch = false;
uint8_t rotaryState = ROTARY_STATE_DEFAULT;

int8_t readEncoder() {
  static int8_t enc_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
  static uint8_t old_AB = 0;
  
  old_AB <<= 2;                   //remember previous state
  old_AB |= ( ROTENC_PORT & 0x03 );  //add current state
  
  return ( enc_states[( old_AB & 0x0f )]);
}

void updateInput(){
  int8_t encData;
  
  if(encData = readEncoder()) {
      rotaryState += encData;
  }
  
  if(switchDelay.ready()) {
    if(rotaryState > ROTARY_STATE_DEFAULT && encData) {
      rotaryRight = true;
      rotaryState = ROTARY_STATE_DEFAULT;
    } else if (rotaryState < ROTARY_STATE_DEFAULT && encData) {
      rotaryLeft = true;
      rotaryState = ROTARY_STATE_DEFAULT;
    }
    
    if(digitalRead(PIN_ROTENC_SWITCH) == LOW) {
      rotarySwitch = true;
    }
  }
}

void setupInput() {
  switchDelay.set(200);
  switchDelay.start();
  
  pinMode(PIN_ROTENC_A, INPUT);
  pinMode(PIN_ROTENC_B, INPUT);
  pinMode(PIN_ROTENC_SWITCH, INPUT);
  
  digitalWrite(PIN_ROTENC_A, HIGH);
  digitalWrite(PIN_ROTENC_B, HIGH);
  digitalWrite(PIN_ROTENC_SWITCH, HIGH);
}


