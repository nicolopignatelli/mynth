#include <MozziGuts.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "model.h"
#include "audio.h"
#include "display.h"
#include "input.h"
#include "control.h"

void setup() {
  //Serial.begin(9600);
  
  setupInput();
  setupDisplay();
  setupAudio();
}  
 
void loop() {
  audioHook(); //Mozzi engine loop callback
}


