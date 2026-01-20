#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>
#include <U8x8lib.h>

#define LED_pin 2
#define BME_ADDR 0x76   // Confirmed by scanner

Adafruit_BME680 bme;
U8X8_SSD1306_128X64_NONAME_HW_I2C oled(U8X8_PIN_NONE);
const char* humStatus;
const char* gasStatus;

void moduleScanner(){
  byte error;   
  int devices = 0;

  Serial.println("Scanning...");

  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Device found at 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      devices++;
    }
  }
  
  if (devices == 0) {
    Serial.println("No devices found");
  } else {
    Serial.println("Scan completed.. " + String(devices) + " devices found");
  }

  delay(2000);  
}

void BME_setup(){
  Serial.println("Initializing BME680...");

  if (!bme.begin(BME_ADDR)) {
    Serial.println("BME680 not found!"); // Stops the operation when BME680 is missing
    while (1); 
  }

  // Settings
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setGasHeater(320, 150); // temp (°C), duration (ms)

  Serial.println("BME680 initialized.");

}

void OLED_setup(){
  oled.begin();
  oled.setPowerSave(0);
  oled.setFont(u8x8_font_7x14_1x2_f);
  oled.drawString (0, 0, "-----------------");
  delay(500);
  oled.drawString (0, 1, "-----------------");
  delay(500);
  oled.drawString (0, 2, "-----------------");
  delay(500);
  oled.drawString (0, 3, "-----------------");
  delay(500);
  oled.drawString (0, 4, "-----------------");
  delay(500);
  oled.drawString (0, 5, "-----------------");
  delay(500);
  oled.drawString (0, 6, "-----------------");
  delay(500);
  oled.clear();
  oled.drawString(1, 3, "Initializing....");
  delay(30000);
  oled.clear();

  oled.drawString (2, 0, "Temp");
  oled.drawString (10, 0, "Hum");
  oled.drawString (10, 4, "Air");
}

void OLED_Runner(){

  char buf[16];

  int temp = (int)(bme.temperature);
  int Ftemp = (int)((bme.temperature * 1.8) + 32);
  int hum = (int)(bme.humidity);
  int gas = (int)(bme.gas_resistance / 1000.0);

  if (hum < 30) {humStatus = "DRY  ";}
  else if (hum <= 50) {humStatus = "OK   ";}
  else if (hum <=60) {humStatus = "HUMID";}
  else {humStatus = "HIGH ";}

  if (gas > 100) {gasStatus = "GOOD";}
  else if (gas > 50) {gasStatus = "OK  ";}
  else if (gas > 20) {gasStatus = "LOW ";}
  else {gasStatus = "BAD ";}

  // Left column (Temperature)
  snprintf(buf, sizeof(buf), "%d C", temp);
  oled.drawString(2, 3, buf);

  snprintf(buf, sizeof(buf), "%d F", Ftemp);
  oled.drawString(2, 6, buf);

  // Right column (Humidity + Air)
  oled.drawString(10, 2, humStatus);
  oled.drawString(10, 6, gasStatus);

  oled.drawString(8, 0, "|");
  oled.drawString(8, 1, "|");
  oled.drawString(8, 2, "|");
  oled.drawString(8, 3, "|");
  oled.drawString(8, 4, "|");
  oled.drawString(8, 5, "|");
  oled.drawString(8, 6, "|");
}

void setup() {
  Serial.begin(9600);
    while (!Serial) {}

  Wire.begin();
  pinMode(LED_pin, OUTPUT);
  for (int i = 1; i <= 5 ; i++){
    digitalWrite (LED_pin, HIGH);
    delay(200);
    digitalWrite (LED_pin, LOW);
    delay(200);
  }

  BME_setup();
  OLED_setup();
     
  // Serial.println("I2C Scanner"); //To Test out the I2C connection    
}

void loop() {

  if (!bme.performReading()) {
    Serial.println("Failed to read BME680");
    return;
  }
  
  OLED_Runner();
  delay(2000);
}
