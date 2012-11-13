//Mozzi proxy function
void updateControl() {
  updateInput();
  
  if(rotaryLeft) {
    switchDelay.start();
    rotaryLeft = false;
    
    currentStage->navigate(LEFT);
    
    refreshScreen = true;
  } else if(rotaryRight) {
    switchDelay.start();
    rotaryRight = false;
    
    currentStage->navigate(RIGHT);

    refreshScreen = true;
  } else if(rotarySwitch) {
    switchDelay.start();
    rotarySwitch = false;

    currentStage->navigate(SWITCH);
    
    refreshScreen = true;
  }
  
  updateDisplay();
}
