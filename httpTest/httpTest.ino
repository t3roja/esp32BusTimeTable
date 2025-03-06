#include <WiFi.h>
#include <HTTPClient.h>

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

// Input buttons
#define httpButton 22

int buttonState = HIGH;
int lastButtonState = HIGH;
bool connection = false;

// Wifi SSID and password
const char* WIFI_SSD = "SSD";
const char* WIFI_PASSWORD = "PASSWORD";


// hostname, pathname and query
const char* SERVER_URL = "URL";

// TFT Screen
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {

  // Start serial and wifi
  Serial.begin(115200);
  WiFi.begin(WIFI_SSD, WIFI_PASSWORD);

  pinMode(httpButton, INPUT_PULLUP);

  tft.init(170, 320);
  Serial.println("ST7789 Initialized!");
  tft.setRotation(0);  // Try 0, 1, 2, 3
  tft.fillScreen(ST77XX_BLUE);

  // Draw test rectangle
  //tft.fillRect(30, 100, 130, 40, ST77XX_BLUE); //(X-coordinate of top-left of the rectangle, Y-coordinate of top-left, width(pixels), height(pixels), color)
  tft.setCursor(10, 110);
  tft.setTextColor(ST77XX_WHITE);  // White text on blue
  tft.setTextSize(2);
  tft.println("Starting up");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }


  tft.fillScreen(ST77XX_BLUE);
  tft.println("Wifi connected!");
  Serial.println("Wifi connected!");
}

void textToScreen(String text) {
  tft.fillScreen(ST77XX_BLUE);
  tft.setCursor(10, 110);
  tft.println(text);
}

void loop() {

  //buttonState = digitalRead(httpButton);

//  if (buttonState == LOW && lastButtonState == HIGH) {
    Serial.println("Sending http request...");
   if (!connection){
      textToScreen("Sending http request...");
    delay(500);
    }

    HTTPClient http;
    http.begin(SERVER_URL);
    http.setTimeout(10000);
    //http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      connection = true;
      String response = http.getString();
      Serial.print("response: ");
      Serial.println(response);

      DynamicJsonDocument doc(1024);
      DeserializationError error = deserializeJson(doc, response);

       if (!error) {
        
                JsonArray data = doc["data"];
                Serial.println("\nArrival Times:");
                textToScreen("");

                for (JsonObject arrival : data) {
                    const char* route = arrival["route_name"];
                    const char* time = arrival["formatted_time"];

                    tft.print("Linja: ");
                    tft.print(route);
                    tft.println("Saapuu: ");
                    tft.println(time);
                }
            } else {
                Serial.println("JSON Parsing failed!");
            }
      
    } else {
      Serial.print("HTTP Error: ");
      Serial.println(httpResponseCode);
    }
    
    //textToScreen(String(httpResponseCode));
    delay(1500);
    
    http.end();
  //}
  //lastButtonState = buttonState;
}
