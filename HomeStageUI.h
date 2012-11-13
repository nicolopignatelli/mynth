class HomeStageUIIcon : public UIElement {
public:
  HomeStageUIIcon() { width = 26; height = 22; }
  
  void draw() {
    uint16_t color = state == SELECTED ? WHITE : BLACK;
    uint16_t bgColor = UIElement::getBgColor(color);
    
    display.fillRect(x, y, width, height, bgColor);
  }
};

class HomeStageUI : public StageUI {
public:
  HomeStageUIIcon live, osc, lfo, adsr, presets;
  
  HomeStageUI() {
    live.x = 1; live.y = 1; live.nextLeft = &presets; live.nextRight = &osc;
    osc.x = 29; osc.y = 1; osc.nextLeft = &live; osc.nextRight = &lfo;
    lfo.x = 57; lfo.y = 1; lfo.nextLeft = &osc; lfo.nextRight = &adsr;
    adsr.x = 1; adsr.y = 25; adsr.nextLeft = &lfo; adsr.nextRight = &presets;
    presets.x = 29; presets.y = 25; presets.nextLeft = &adsr; presets.nextRight = &live;
    
    focused = 0;
  }
  
  void navigate(UINavigationAction action) {
    if(focused == 0) {
      focused = &live;
      live.state = SELECTED;
      live.redraw = true;
    } else if(action == LEFT) {
      focused->state = NORMAL;
      focused->redraw = true;
      focused = focused->nextLeft;
      focused->state = SELECTED;
      focused->redraw = true;
    } else if(action == RIGHT) {
      focused->state = NORMAL;
      focused->redraw = true;
      focused = focused->nextRight;
      focused->state = SELECTED;
      focused->redraw = true;
    } else if(action == SWITCH) {
      gotoStage(createStage(focused));
    }
  };

  void draw() {
    display.drawRect(0, 0, 84, 48, BLACK);
    display.drawRect(1, 23, 82, 2, BLACK);
    display.drawRect(27, 1, 2, 46, BLACK);
    display.drawRect(55, 1, 2, 46, BLACK);
    
    if(live.redraw) live.draw(); 
    if(osc.redraw) osc.draw(); 
    if(lfo.redraw) lfo.draw(); 
    if(adsr.redraw) adsr.draw(); 
    if(presets.redraw) presets.draw();
  }
  
private:
  StageUIType createStage(UIElement* icon) {
    if(icon == &osc) {
      return OSC;
    } // ...
  }
};
