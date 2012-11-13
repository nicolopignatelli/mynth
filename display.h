typedef enum {HOME, LIVE, OSC, LFO, ADSR, PRESETS} StageUIType;
void gotoStage(StageUIType);

Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5, 7, 6);
#include "ui.h"

boolean refreshScreen = true;
StageUI* currentStage = 0;
HomeStageUI homeStageUI;
OscStageUI oscStageUI(&oscStage);

void updateDisplay() {
  if(refreshScreen) {
    refreshScreen = false;
    currentStage->draw();
    display.display();
  }
}

void gotoStage(StageUIType newStageType) {
  display.clearDisplay();
  
  if(newStageType == HOME) {
    currentStage = &homeStageUI;
  } else if(newStageType == LIVE) {
    //currentStage = new LiveStageUI();
  } else if(newStageType == OSC) {
    currentStage = &oscStageUI;
  } // ...
}

void setupDisplay() {
  display.begin();
  display.clearDisplay();
  
  currentStage = &homeStageUI;
}

