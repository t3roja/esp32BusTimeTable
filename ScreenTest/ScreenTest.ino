#include <WiFi.h>
#include <HTTPClient.h>

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

// IO pin definitions
#define TFT_CS 5     // CS connected to GPIO 5
#define TFT_RST 4    // Reset pin
#define TFT_DC 2     // Data/Command
#define TFT_MOSI 23  // MOSI
#define TFT_SCLK 18  // SCLK

// Wifi SSID and password
const char WIFI_SSD[] = "SSID";
const char WIFI_PASSWORD[] = "PASSWORD";

// hostname, pathname and query
const char SERVER_URL = "192.168.1:5000/data";

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
int rotation = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing ST7789...");

  tft.init(170, 320);
  Serial.println("ST7789 Initialized!");

  tft.setRotation(0);  // Try 0, 1, 2, 3
  Serial.println("Rotation set!");

  tft.fillScreen(ST77XX_WHITE);
  delay(100);  // Allow screen refresh

  // Draw test rectangle
  tft.fillRect(30, 100, 130, 40, ST77XX_BLUE); //(X-coordinat of top-left of the rectangle, Y-coordinate of top-left, width(pixels), height(pixels), color)
  tft.setCursor(40, 110);
  tft.setTextColor(ST77XX_WHITE);  // White text on blue
  tft.setTextSize(2);
  tft.println("Screen test");
  Serial.println("Text printed!");
}

void loop() {
}
