typedef enum {NORMAL, SELECTED, ACTIVE} UIElementState;
typedef enum {LEFT, RIGHT, SWITCH} UINavigationAction;
typedef enum {MOVING, EDITING} UINavigationState;

class UIElement {
public:
  UIElement() : x(0),y(0),width(0),height(0),state(NORMAL),visible(true),redraw(true){}
  
  unsigned int x;
  unsigned int y;
  unsigned int width;
  unsigned int height;
  boolean visible;
  boolean redraw;
  UIElementState state;
  UIElement* nextLeft;
  UIElement* nextRight;
  
  virtual void onEdit(UINavigationAction action) {};
  static uint16_t getBgColor(uint16_t color) { return ~color & 0x01; }
};

class HomeIconUIElement : public UIElement {
public:
  void draw() {
    uint16_t color = state == SELECTED ? BLACK : WHITE;
    uint16_t bgColor = UIElement::getBgColor(color);
    
    display.drawRect(x, y, 7, 7, WHITE);
    display.fillRect(x + 1, y + 1, 5 , 5, bgColor);
    display.drawPixel(x + 3, y + 2, color);
    display.drawPixel(x + 3, y + 5, color);
    display.drawFastVLine(x + 2, y + 3, 2, color);
    display.drawFastVLine(x + 4, y + 3, 2, color);
  };
};

class WaveformUIElement : public UIElement {
public:
  void draw(WaveForm wf) {
    uint16_t color = state == ACTIVE ? WHITE : BLACK;
    uint16_t bgColor = UIElement::getBgColor(color);
    
    display.drawRect(x, y, width, height, color);
    display.drawRect(x, y - 2, width, 2, state == SELECTED ? BLACK : WHITE);
    display.fillRect(x + 1, y + 1, width - 2, height - 2, bgColor);
    
    if(wf == SINE) {
      drawSine(color);
    } else if(wf == SQUARE) {
      drawSquare(color);
    } else if (wf == SAW) {
      drawSaw(color);
    } else if (wf == TRIANGLE) {
      drawTriangle(color);
    }
  }
  
  void drawSine(uint16_t color) {
    display.drawRect(x + 2, y + 7, 2, 5, color);
    display.drawFastHLine(x + 3, y + 6, 2, color);
    display.drawFastHLine(x + 4, y + 5, 5, color);
    display.drawFastHLine(x + 5, y + 4, 3, color);
    display.drawFastHLine(x + 8, y + 6, 2, color);
    display.drawRect(x + 9, y + 7, 2, 3, color);
    display.drawFastHLine(x + 10, y + 10, 2, color);
    display.drawFastHLine(x + 11, y + 11, 6, color);
    display.drawFastHLine(x + 12, y + 12, 4, color);
    display.drawFastHLine(x + 16, y + 10, 2, color);
    display.drawRect(x + 17, y + 5, 2, 5, color);
  }
  
  void drawSquare(uint16_t color) {
    display.drawRect(x + 3, y + 5, 2, 8, color);
    display.drawRect(x + 5, y + 5, 7, 2, color);
    display.drawRect(x + 10, y + 7, 2, 6, color);
    display.drawRect(x + 12, y + 11, 6, 2, color);
    display.drawRect(x + 16, y + 5, 2, 6, color);
  }
  
  void drawSaw(uint16_t color) {
    display.drawRect(x + 5, y + 4, 2, 10, color);
    display.drawLine(x + 7, y + 4, x + 16, y + 13, color);
    display.drawLine(x + 7, y + 5, x + 15, y + 13, color);
    display.drawLine(x + 7, y + 6, x + 14, y + 13, color);
  }
  
  void drawTriangle(uint16_t color) {
    display.drawLine(x + 2, y + 12, x + 10, y + 4, color);
    display.drawLine(x + 3, y + 12, x + 10, y + 5, color);
    display.drawLine(x + 4, y + 12, x + 10, y + 6, color);
    display.drawLine(x + 11, y + 5, x + 18, y + 12, color);
    display.drawLine(x + 11, y + 6, x + 17, y + 12, color);
    display.drawLine(x + 11, y + 7, x + 16, y + 12, color);
  }
};

class PotentiometerUIElement : public UIElement {
public:
  static const double RADIUS = 3;
  
  void draw(double value, uint16_t color, uint16_t bgColor, uint16_t offset_x = 0, uint16_t offset_y = 0) {
    double percent, deg, x1, y1;
    
    percent = (value - minimum) / (maximum - minimum);
    deg = 135 + (percent * 270);
    
    x1 = RADIUS * cos(3.14f * deg / 180);
    y1 = RADIUS * sin(3.14f * deg / 180);
    
    display.drawCircle(x + offset_x + RADIUS, y + offset_y + RADIUS, RADIUS, color);
    display.drawLine(x + offset_x + RADIUS, y + offset_y + RADIUS, x + offset_x + RADIUS + round(x1), y + offset_y + RADIUS + round(y1), color);
  }
  
protected:
  float minimum;
  float maximum;
  float step;
};

class StageUI {
public:
  virtual void navigate(UINavigationAction action) = 0;
  virtual void draw() = 0;
protected:
  UINavigationState navState;
  UIElement* focused;
};

//Actual stage UIs
#include "OscStageUI.h"
#include "HomeStageUI.h"
