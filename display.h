Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5, 7, 6);
#include "draw.h"

#define BLACK 1
#define WHITE 0

boolean refreshScreen = true;
char* osc1_icon = "";
char* osc2_icon = "";

void updateDisplay() {
  if(refreshScreen) {
    refreshScreen = false;
    drawMenu(osc1_icon, osc2_icon);
    display.display();
  }
}

void setupDisplay() {
  display.begin();
  display.clearDisplay();
}
