void drawSineIcon(int16_t x, int16_t y, uint16_t color) {
  uint16_t bgColor = ~color & 0x01;
  
  display.fillRect(x, y, 9, 8, bgColor);
  display.drawPixel(x+1, y+3, color);
  display.drawPixel(x+1, y+4, color);
  display.drawPixel(x+2, y+2, color);
  display.drawPixel(x+3, y+2, color);
  display.drawPixel(x+4, y+3, color);
  display.drawPixel(x+4, y+4, color);
  display.drawPixel(x+5, y+5, color);
  display.drawPixel(x+6, y+5, color);
  display.drawPixel(x+7, y+3, color);
  display.drawPixel(x+7, y+4, color);
}

void drawSquareIcon(int16_t x, int16_t y, uint16_t color) {
  uint16_t bgColor = ~color & 0x01;
  
  display.fillRect(x, y, 9, 8, bgColor);
  display.drawFastVLine(x+1, y+2, 5, color);
  display.drawFastHLine(x+2, y+2, 2, color);
  display.drawFastVLine(x+3, y+3, 4, color);
  display.drawFastHLine(x+4, y+6, 3, color);
  display.drawFastVLine(x+6, y+2, 4, color);
}

void drawSawIcon(int16_t x, int16_t y, uint16_t color) {
  uint16_t bgColor = ~color & 0x01;
  
  display.fillRect(x, y, 9, 8, bgColor);
  display.drawFastVLine(x+1, y+2, 5, color);
  display.drawLine(x+2, y+2, x+6, y+6, color);
}

void drawTriangleIcon(int16_t x, int16_t y, uint16_t color) {
  uint16_t bgColor = ~color & 0x01;
  
  display.fillRect(x, y, 9, 8, bgColor);
  display.drawLine(x+1, y+6, x+4, y+3, color);
  display.drawLine(x+5, y+4, x+7, y+6, color);
}


void drawMenu(char* osc1, char* osc2) {
  //frame
  display.drawRect(0, 0, 84, 48, BLACK);
  display.drawFastHLine(1, 45, 82, BLACK);
  display.drawFastHLine(1, 46, 82, BLACK);
  
  //cell borders
  display.drawFastHLine(1, 9, 82, BLACK); // headers line
  display.drawFastVLine(30, 1, 44, BLACK); // 1st col
  display.drawFastVLine(61, 1, 44, BLACK); //2nd col
  display.drawFastVLine(10, 10, 35, BLACK); //osc1 col
  display.drawFastVLine(40, 10, 35, BLACK); //osc1 col
  display.drawFastHLine(1, 18, 9, BLACK); //osc1 icons separators
  display.drawFastHLine(1, 27, 9, BLACK);
  display.drawFastHLine(1, 36, 9, BLACK);
  display.drawFastHLine(31, 18, 9, BLACK); //osc2 icons separators
  display.drawFastHLine(31, 27, 9, BLACK);
  display.drawFastHLine(31, 36, 9, BLACK);
  
  //titles
  
  
  //waves
  drawSineIcon(1, 10, osc1 == "sine" ? WHITE : BLACK);
  drawSineIcon(31, 10, osc2 == "sine" ? WHITE : BLACK);
  drawSquareIcon(1, 19, osc1 == "square" ? WHITE : BLACK);
  drawSquareIcon(31, 19, osc2 == "square" ? WHITE : BLACK);
  drawSawIcon(1, 28, osc1 == "saw" ? WHITE : BLACK);
  drawSawIcon(31, 28, osc2 == "saw" ? WHITE : BLACK);
  drawTriangleIcon(1, 37, osc1 == "triangle" ? WHITE : BLACK);
  drawTriangleIcon(31, 37, osc2 == "triangle" ? WHITE : BLACK);
}
