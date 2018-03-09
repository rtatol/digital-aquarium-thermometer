
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 8                // DS18B20 sensor - oneWire pin number

OneWire oneWire(ONE_WIRE_BUS);        // setup a oneWire instance to communicate with any OneWire device
DallasTemperature sensors(&oneWire);  // pass our oneWire reference to Dallas Temperature

#define SCLK 7                        // Serial clock out (SCLK)
#define DIN  6                        // Serial data out (DIN)
#define DC   5                        // Data/Command select (D/C)
#define CS   4                        // LCD chip select (CS)
#define RST  3                        // LCD reset (RST)

Adafruit_PCD8544 display = Adafruit_PCD8544(SCLK, DIN, DC, CS, RST); // display instance

signed char fishX = 0;                // fish initial position
const unsigned long delayTime = 1000; // delay in milliseconds;

void setup() {
  sensors.begin();
  display.begin();
  display.setContrast(50);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.clearDisplay();
}

void loop() {
  sensors.requestTemperatures();
  draw();
  delay(delayTime);
}

void draw() {
  display.clearDisplay();
  drawTemperature();
  drawFish();
  drawWaterTerperature();
  display.display();
}

void drawTemperature() {
  display.setCursor(3, 1);
  display.print("Temp: ");
  display.print(sensors.getTempCByIndex(0));
  display.print(" C");
  display.drawLine(0, 10, 81, 10, BLACK);
}

void drawWaterTerperature() {
  display.setCursor(3, 39);
  display.print("Woda: ");
  display.print(sensors.getTempCByIndex(1));
  display.print(" C");
  display.drawLine(0, 36, 81, 36, BLACK);
}

void drawFish() {
  // body
  display.fillRoundRect(fishX + 8, 18, 20, 10, 5, BLACK);
  // tail
  display.fillTriangle(fishX, 28, fishX, 18, fishX + 10, 23, BLACK);
  // eye
  display.fillRect(fishX  + 21, 20, 2, 2, WHITE);
  // udpate position
  fishX = fishX < 84 ? fishX + 5 : -30;
}

