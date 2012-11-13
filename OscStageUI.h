class OscWaveformUIElement : public WaveformUIElement {
public:
  Oscillator* osc;
  unsigned int channel;
  
  virtual void onEdit(UINavigationAction action) {
    if(action == LEFT) {
      (*osc).waveForm = prevOscillator(*osc);
      resetPhase(*osc, channel);
    } else if (action == RIGHT) {
      (*osc).waveForm = nextOscillator(*osc);
      resetPhase(*osc, channel);
    }
  }
};

class OscOctaveUIElement : public PotentiometerUIElement {
public:
  Oscillator* osc;
  unsigned int channel;
  
  OscOctaveUIElement() { minimum = -4; maximum = 4; step = 1; }
  
  virtual void onEdit(UINavigationAction action) {
    if(action == LEFT) {
      (*osc).octave = (*osc).octave > minimum ? (*osc).octave - step : minimum;
      changeFreq(*osc, channel);
    } else if (action == RIGHT) {
      (*osc).octave = (*osc).octave < maximum ? (*osc).octave + step : maximum;
      changeFreq(*osc, channel);
    }
  }
  
  void draw() {
    if((*osc).waveForm == SILENCE) {
      visible = false;
      display.fillRect(x, y, width, height, WHITE);
    } else {
      visible = true;
      uint16_t color = state == ACTIVE ? WHITE : BLACK;
      uint16_t bgColor = UIElement::getBgColor(color);
      
      display.fillRect(x, y, width, height, bgColor);
      display.drawRect(x, y - 2, width, 2, state == SELECTED ? BLACK : WHITE);
      display.drawRect(x + 2, y + 8, 3, 3, color);
      display.drawRect(x + 2, y + 12, 3, 3, color);
      display.drawPixel(x + 4, y + 13, bgColor);
      display.drawFastVLine(x + 2, y + 16, 3, color);
      display.drawPixel(x + 3, y + 17, color);
      
      PotentiometerUIElement::draw((*osc).octave, color, bgColor);
    }
  }
};

class OscTuneUIElement : public PotentiometerUIElement {
public:
  Oscillator* osc;
  unsigned int channel;
  
  OscTuneUIElement() { minimum = -1; maximum = 1; step = .1f; }
  
  virtual void onEdit(UINavigationAction action) {
    if(action == LEFT) {
      (*osc).tune = (*osc).tune > minimum ? (*osc).tune - step : minimum;
      changeFreq(*osc, channel);
    } else if (action == RIGHT) {
      (*osc).tune = (*osc).tune < maximum ? (*osc).tune + step : maximum;
      changeFreq(*osc, channel);
    }
  }
  
  void draw() {
    if((*osc).waveForm == SILENCE) {
      visible = false;
      display.fillRect(x, y, width, height, WHITE);
    } else {
      visible = true;
      uint16_t color = state == ACTIVE ? WHITE : BLACK;
      uint16_t bgColor = UIElement::getBgColor(color);
      
      display.fillRect(x, y, width, height, bgColor);
      display.drawRect(x, y - 2, width, 2, state == SELECTED ? BLACK : WHITE);
      display.drawFastVLine(x + 2, y + 8, 3, color);
      display.drawPixel(x + 3, y + 9, color);
      display.drawRect(x + 2, y + 12, 3, 3, color);
      display.drawPixel(x + 3, y + 12, bgColor);
      display.drawFastVLine(x + 2, y + 16, 3, color);
      display.drawFastVLine(x + 4, y + 16, 3, color);
      display.drawPixel(x + 3, y + 17, color);
      
      PotentiometerUIElement::draw((*osc).tune, color, bgColor);
    }
  }
};

class OscPwUIElement : public PotentiometerUIElement {
public:
  Oscillator* osc;
  unsigned int channel;
  
  OscPwUIElement() { minimum = 64; maximum = 192; step = 8; }
  
  virtual void onEdit(UINavigationAction action) {
    if(action == LEFT) {
      (*osc).pw = (*osc).pw > minimum ? (*osc).pw - step : minimum;
      resetPhase(*osc, channel);
    } else if (action == RIGHT) {
      (*osc).pw = (*osc).pw < maximum ? (*osc).pw + step : maximum;
      resetPhase(*osc, channel);
    }
  }
  
  void draw() {
    if((*osc).waveForm != SQUARE) {
      visible = false;
      display.fillRect(x, y, width, height, WHITE);
    } else {
      visible = true;
      uint16_t color = state == ACTIVE ? WHITE : BLACK;
      uint16_t bgColor = UIElement::getBgColor(color);
      
      display.fillRect(x, y, width, height, bgColor);
      display.drawRect(x, y - 2, width, 2, state == SELECTED ? BLACK : WHITE);
      display.drawRect(x + 3, y, 5, 3, color);
      display.drawRect(x + 7, y, 5, 3, color);
      display.drawFastHLine(x + 4, y + 2, 3, bgColor);
      display.drawFastHLine(x + 8, y, 3, bgColor);
      display.drawRect(x, y + 10, 3, 3, color);
      display.drawPixel(x + 1, y + 12, bgColor);
      display.drawFastHLine(x + 3, y + 12, 3, color);
      display.drawRect(x + 12, y + 10, 3, 3, color);
      display.drawPixel(x + 13, y + 12, bgColor);
      display.drawFastHLine(x + 9, y + 12, 3, color);
      
      display.drawFastVLine(x + 3, y + 15, 4, color);
      display.drawPixel(x + 4, y + 15, color);
      display.drawPixel(x + 4, y + 17, color);
      display.drawPixel(x + 5, y + 16, color);
      display.drawFastVLine(x + 7, y + 15, 4, color);
      display.drawFastHLine(x + 8, y + 18, 4, color);
      display.drawFastVLine(x + 11, y + 15, 3, color);
      display.drawPixel(x + 9, y + 17, color);
      
      PotentiometerUIElement::draw((*osc).pw, color, bgColor, 4, 4);
    }
  }
};

class OscMixerUIElement : public UIElement {
public:
  OscStage* oscStage;
  static const uint8_t minimum = 0;
  static const uint8_t maximum = 1;
  static const float step = .1f;
  
  virtual void onEdit(UINavigationAction action) {
    if(action == LEFT) {
      (*oscStage).mix = (*oscStage).mix > minimum ? (*oscStage).mix - step : minimum;
    } else if (action == RIGHT) {
      (*oscStage).mix = (*oscStage).mix < maximum ? (*oscStage).mix + step : maximum;
    }
  }
  
  void draw() {
      uint16_t color = state == ACTIVE ? WHITE : BLACK;
      uint16_t bgColor = UIElement::getBgColor(color);
      
      display.fillRect(x, y, width, height, bgColor);
      display.drawRect(x, y, width, 2, state == SELECTED ? BLACK : WHITE);
      display.drawFastVLine(x + 3, y + 2, 5, color);
      display.drawPixel(x + 2, y + 2, color);
      display.drawRect(x + 2, y + 38, 3, 3, color);
      display.drawPixel(x + 2, y + 39, bgColor);
      display.drawPixel(x + 2, y + 41, color);
      display.drawFastHLine(x + 2, y + 42, 3, color);
      
      display.drawFastHLine(x + 2, y + 11, 3, color);
      display.drawFastHLine(x + 2, y + 33, 3, color);
      display.drawFastVLine(x + 3, y + 12, 21, color);
      
      display.fillRect(x + 1, y + map((*oscStage).mix * 10, minimum * 10, maximum * 10, 12, 30), 5, 3, color);
  }
};

class OscStageUI : public StageUI {
public:
  OscStage* oscStage;
  OscWaveformUIElement wf1Icon;
  OscWaveformUIElement wf2Icon;
  OscOctaveUIElement osc1Oct;
  OscTuneUIElement osc1Tune;
  OscPwUIElement osc1Pw;
  OscOctaveUIElement osc2Oct;
  OscTuneUIElement osc2Tune;
  OscPwUIElement osc2Pw;
  OscMixerUIElement mixer;
  HomeIconUIElement homeIcon;
  
  OscStageUI(OscStage* stage) {
    oscStage = stage;
    
    homeIcon.x = 76; homeIcon.y = 39; homeIcon.nextLeft = &osc2Pw; homeIcon.nextRight = &mixer;
    mixer.x = 1; mixer.y = 1; mixer.width = 7; mixer.height = 45; mixer.nextLeft = &homeIcon; mixer.nextRight = &wf1Icon;
    wf1Icon.x = 11; wf1Icon.y = 3; wf1Icon.width = 21; wf1Icon.height = 18; wf1Icon.nextLeft = &mixer; wf1Icon.nextRight = &osc1Oct;
    osc1Oct.x = 35; osc1Oct.y = 3; osc1Oct.width = 7; osc1Oct.height = 19; osc1Oct.nextLeft = &wf1Icon; osc1Oct.nextRight = &osc1Tune;
    osc1Tune.x = 47; osc1Tune.y = 3; osc1Tune.width = 7; osc1Tune.height = 19; osc1Tune.nextLeft = &osc1Oct; osc1Tune.nextRight = &osc1Pw;
    osc1Pw.x = 58; osc1Pw.y = 3; osc1Pw.width = 15; osc1Pw.height = 19; osc1Pw.nextLeft = &osc1Tune; osc1Pw.nextRight = &wf2Icon;
    wf2Icon.x = 11; wf2Icon.y = 26; wf2Icon.width = 21; wf2Icon.height = 18; wf2Icon.nextLeft = &osc1Pw; wf2Icon.nextRight = &osc2Oct;
    osc2Oct.x = 35; osc2Oct.y = 26; osc2Oct.width = 7; osc2Oct.height = 19; osc2Oct.nextLeft = &wf2Icon; osc2Oct.nextRight = &osc2Tune;
    osc2Tune.x = 47; osc2Tune.y = 26; osc2Tune.width = 7; osc2Tune.height = 19; osc2Tune.nextLeft = &osc2Oct; osc2Tune.nextRight = &osc2Pw;
    osc2Pw.x = 58; osc2Pw.y = 26; osc2Pw.width = 15; osc2Pw.height = 19; osc2Pw.nextLeft = &osc2Tune; osc2Pw.nextRight = &homeIcon;
    
    navState = MOVING;
    focused = &homeIcon;
    homeIcon.state = SELECTED;
    
    wf1Icon.osc = &((*stage).osc1); wf1Icon.channel = 0;
    wf2Icon.osc = &((*stage).osc2); wf2Icon.channel = 1;
    osc1Oct.osc = &((*stage).osc1); osc1Oct.channel = 0;
    osc2Oct.osc = &((*stage).osc2); osc2Oct.channel = 1;
    osc1Tune.osc = &((*stage).osc1); osc1Tune.channel = 0;
    osc2Tune.osc = &((*stage).osc2); osc2Tune.channel = 1;
    osc1Pw.osc = &((*stage).osc1); osc1Pw.channel = 0;
    osc2Pw.osc = &((*stage).osc2); osc2Pw.channel = 1;
    mixer.oscStage = stage;
  }
  
  void navigate(UINavigationAction action) {
    if(navState == MOVING) {
      if(action == LEFT) {
        focused->state = NORMAL;
        focused->redraw = true;
        do { focused = focused->nextLeft; } while(focused->visible == false);
        focused->state = SELECTED;
        focused->redraw = true;
      } else if(action == RIGHT) {
        focused->state = NORMAL;
        focused->redraw = true;
        do { focused = focused->nextRight; } while(focused->visible == false);
        focused->state = SELECTED;
        focused->redraw = true;
      } else if(action == SWITCH && focused != 0 && focused != &homeIcon) {
        navState = EDITING;
        focused->state = ACTIVE;
        focused->redraw = true;
      } else if(action == SWITCH && focused == &homeIcon) {
        gotoStage(HOME);
      }
    } else if(navState == EDITING) {
      if(action == LEFT || action == RIGHT) {
        focused->onEdit(action);
        focused->redraw = true;
      } else if(action == SWITCH) {
        navState = MOVING;
        focused->state = SELECTED;
        focused->redraw = true;
      }
    } 
  }
  
  void draw() {
    //frame
    display.drawRect(0, 0, 84, 48, BLACK);
    display.drawFastHLine(1, 46, 82, BLACK);
    display.drawFastHLine(9, 23, 66, BLACK);
    display.drawFastVLine(8, 1, 45, BLACK);
    display.drawFastVLine(75, 1, 45, BLACK);
    
    //OSC
    display.fillRect(76, 1, 8, 45, BLACK);
    display.drawRect(78, 14, 3, 5, WHITE);
    display.drawFastHLine(78, 21, 3, WHITE);
    display.drawFastVLine(78, 22, 2, WHITE);
    display.drawFastHLine(79, 23, 2, WHITE);
    display.drawFastVLine(80, 24, 2, WHITE);
    display.drawFastHLine(78, 25, 2, WHITE);
    display.drawRect(78, 28, 3, 5, WHITE);
    display.drawFastVLine(80, 29, 3, BLACK);
    
    if(wf1Icon.redraw) wf1Icon.draw((*oscStage).osc1.waveForm);
    if(wf2Icon.redraw) wf2Icon.draw((*oscStage).osc2.waveForm);
    
    if(osc1Oct.redraw) osc1Oct.draw();
    if(osc2Oct.redraw) osc2Oct.draw();

    if(osc1Tune.redraw) osc1Tune.draw();
    if(osc2Tune.redraw) osc2Tune.draw();

    if(osc1Pw.redraw) osc1Pw.draw();
    if(osc2Pw.redraw) osc2Pw.draw();
    
    if(mixer.redraw) mixer.draw();
    
    if(homeIcon.redraw) homeIcon.draw();
  };
};

