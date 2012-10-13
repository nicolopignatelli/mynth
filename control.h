//Mozzi proxy function
void updateControl() {
  updateInput();
  
  //audio section
  if(switchOsc1Pressed == 1) {
    switch1Delay.start();
    switchOsc1Pressed = 0;
    current_osc1 = nextOscillator(current_osc1);
    osc1_icon = current_osc1;
    refreshScreen = true;
  }
  else if(switchOsc2Pressed == 1) {
    switch2Delay.start();
    switchOsc2Pressed = 0;
    current_osc2 = nextOscillator(current_osc2);
    osc2_icon = current_osc2;
    refreshScreen = true;
  }
  //updateAudio() is internally called by Mozzi
  
  //display section
  //...
  updateDisplay();
}
