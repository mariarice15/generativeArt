#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite stext1 = TFT_eSprite(&tft); // Sprite object stext1

int textScrollX = 0;
bool increaseSize = true; // Flag to toggle between increasing and decreasing heart size
int heartX = 120; // Initial x-coordinate for the heart
int heartY = 45;  // Initial y-coordinate for the heart

void setup() {
  tft.init();
  tft.fillScreen(TFT_WHITE);
  tft.setRotation(1);

  // Create a sprite for the scrolling words
  stext1.setColorDepth(8);
  stext1.createSprite(200, 35);
  stext1.fillSprite(TFT_WHITE); 
  stext1.setScrollRect(0, 0, 200, 35, TFT_WHITE);    
  stext1.setTextColor(TFT_RED); // White text, no background
  stext1.setRotation(1);
  stext1.setTextWrap(false);
  stext1.setTextSize(2);
}

void loop() {
  // Toggle between increasing and decreasing heart size
  if (increaseSize) {
    drawHeart(heartX, heartY, 3.5, TFT_RED); // Draw the heart shape with size 4
  } else {
    drawHeart(heartX, heartY, 2.5, TFT_WHITE); // Draw the heart shape with size 3
  }

  // Push the scrolling text sprite onto the screen
  stext1.pushSprite(20, 100);

  // Delay to control the animation speed
  delay(150);

  // Scroll the text
  textScrollX -= 16;
  if (textScrollX <= -(stext1.textWidth("TO RESIST IS TO LOVE WHAT COULD BE"))) {
    textScrollX = 200;
  }
  stext1.fillSprite(TFT_WHITE); 
  stext1.setCursor(textScrollX, 10);
  stext1.print("TO RESIST IS TO LOVE WHAT COULD BE");

  // Toggle the flag to switch between increasing and decreasing heart size
  increaseSize = !increaseSize;
}

void drawHeart(int16_t x0, int16_t y0, float HeartSize, uint16_t color) {
  // Set stroke color
  tft.setTextColor(color);

  // Draw the heart shape
  for (float t = 0; t <= 2 * PI; t += 0.005) {
    float x = x0 - 16 * HeartSize * pow(sin(t), 3);
    float y = y0 - (13 * HeartSize * cos(t) - 5 * HeartSize * cos(2 * t) - 2 * HeartSize * cos(3 * t) - cos(4 * t));
    float x2 = x0 - 16 * HeartSize * pow(sin(t + 0.01), 3);
    float y2 = y0 - (13 * HeartSize * cos(t + 0.01) - 5 * HeartSize * cos(2 * (t + 0.01)) - 2 * HeartSize * cos(3 * (t + 0.01)) - cos(4 * (t + 0.01)));
    tft.drawLine(x, y, x2, y2, color);
    tft.drawLine(x, y, x0, y0, color); // Draw line to the center to fill the heart
  }
}
