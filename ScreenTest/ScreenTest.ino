#include <ArduinoJson.h>

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

// IO pin definitions
#define TFT_CS 5     // CS connected to GPIO 5
#define TFT_RST 4    // Reset pin
#define TFT_DC 2     // Data/Command
#define TFT_MOSI 23  // MOSI
#define TFT_SCLK 18  // SCLK

// TFT Screen
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

//  To draw a line: tft.drawLine(51, 0, 51, 80, ST77XX_BLACK); // Starting point X, y, ending point x, y, color

void textToScreen(String text) {
  tft.fillScreen(ST77XX_BLUE);
  tft.setCursor(10, 110);
  tft.println(text);
}

void setup() {

  // Initialization
  Serial.begin(115200);
  tft.init(170, 320);
  tft.fillScreen(ST77XX_MAGENTA);
  tft.setRotation(1);  // 0, 1, 2, 3

  tft.drawRect(0, 0, 320, 170, ST77XX_WHITE); //(X-coordinate of top-left of the rectangle, Y-coordinate of top-left, width(pixels), height(pixels), color)
  tft.drawRect(0, 40, 80, 60, ST77XX_WHITE);
  tft.drawRect(80,40,240, 60, ST77XX_WHITE);

  tft.setTextSize(2);
  tft.setCursor(10,10);
  tft.print("-12'C A");
  tft.setCursor(220, 10);
  tft.print("06:27");

  tft.setTextSize(6);
  tft.setCursor(5, 50);
  tft.setTextColor(ST77XX_WHITE);
  
  tft.println("10");

  tft.setTextSize(3);
  tft.setCursor(90, 60);
  tft.print("SAAPUU ");

  tft.print("06:32");

  tft.setCursor(10, 110);
  tft.setTextSize(2);
  tft.print("Seuraavat ");


  tft.setCursor(160, 110);
  tft.print("10");
  tft.setCursor(220, 110);
  tft.print("06:47");


  tft.setCursor(160, 140);
  tft.print("9");
  tft.setCursor(220, 140);
  tft.print("07:02");

  // Draw test rectangle
  //tft.fillRect(30, 100, 130, 40, ST77XX_BLUE); //(X-coordinate of top-left of the rectangle, Y-coordinate of top-left, width(pixels), height(pixels), color)

}


void loop() {

}
