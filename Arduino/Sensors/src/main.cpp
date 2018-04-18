
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <DHT.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <SPI.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
Adafruit_BMP280 bmp280;
DHT dht(7, DHT11);
OneWire oneWire(2);
DallasTemperature sensors(&oneWire);
DeviceAddress insideThermometer, outsideThermometer;

void printAddress(DeviceAddress deviceAddress);
void printTemperature(DeviceAddress deviceAddress);
void printAlarms(uint8_t deviceAddress[]);
void printData(DeviceAddress deviceAddress);
void printThermometersInfo();
void checkAlarm(DeviceAddress deviceAddress);

void setup() {
  Serial.begin(115200);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print(F("BMP280 test"));
  bmp280.begin(0x76);

  lcd.setCursor(0, 1);
  lcd.print(F("DHT11 test"));
  dht.begin();

  lcd.setCursor(0, 2);
  lcd.print(F("DS18B20 test"));
  sensors.begin();

  // locate devices on the bus
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" I2C devices.");

  // search for devices on the bus and assign based on an index.
  if (!sensors.getAddress(insideThermometer, 0))
    Serial.println("Unable to find address for Device 0");
  if (!sensors.getAddress(outsideThermometer, 1))
    Serial.println("Unable to find address for Device 1");

  sensors.setHighAlarmTemp(insideThermometer, 30);
  sensors.setLowAlarmTemp(insideThermometer, 10);

  sensors.setHighAlarmTemp(outsideThermometer, 29);
  sensors.setLowAlarmTemp(outsideThermometer, 24);

  printThermometersInfo();

  delay(2000);

  lcd.clear();
}

void loop() {
  // lcd.clear();

  /// BMP280
  auto hPa = bmp280.readPressure() / 100.0;
  auto bmp280T = bmp280.readTemperature();
  auto meters = bmp280.readAltitude(1001.1);

  // DHT11
  auto humidity = dht.readHumidity();
  auto dht11T = dht.readTemperature();

  //  DB18B20
  sensors.requestTemperatures();
  checkAlarm(insideThermometer);
  checkAlarm(outsideThermometer);

  lcd.setCursor(0, 0);
  lcd.print("P: ");
  lcd.print(hPa);
  lcd.print(" hPa");

  lcd.setCursor(0, 1);
  lcd.print("A: ");
  lcd.print(meters);
  lcd.print(" m");
  lcd.print(" / ");
  lcd.print(bmp280T);

  lcd.setCursor(0, 2);
  lcd.print("H: ");
  lcd.print(humidity);
  lcd.print(" %");
  lcd.print("  / ");
  lcd.print(dht11T);

  lcd.setCursor(0, 3);
  lcd.print("T: ");
  lcd.print(sensors.getTempCByIndex(0));
  lcd.print(" / ");
  lcd.print(sensors.getTempCByIndex(1));

  delay(1000);
}

// function to print a device address
void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) {
    if (deviceAddress[i] < 16)
      Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress) {
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.print(tempC);
  Serial.print(" Temp F: ");
  Serial.print(DallasTemperature::toFahrenheit(tempC));
}

void printAlarms(uint8_t deviceAddress[]) {
  char temp;
  temp = sensors.getHighAlarmTemp(deviceAddress);
  Serial.print("High Alarm: ");
  Serial.print(temp, DEC);
  Serial.print("C/");
  Serial.print(DallasTemperature::toFahrenheit(temp));
  Serial.print("F | Low Alarm: ");
  temp = sensors.getLowAlarmTemp(deviceAddress);
  Serial.print(temp, DEC);
  Serial.print("C/");
  Serial.print(DallasTemperature::toFahrenheit(temp));
  Serial.print("F");
}

// main function to print information about a device
void printData(DeviceAddress deviceAddress) {
  Serial.print("Device Address: ");
  printAddress(deviceAddress);
  Serial.print(" ");
  printTemperature(deviceAddress);
  Serial.println();
}

void checkAlarm(DeviceAddress deviceAddress) {
  if (sensors.hasAlarm(deviceAddress)) {
    Serial.print("ALARM: ");
    printData(deviceAddress);
  }
}

void printThermometersInfo() {


  // show the addresses we found on the bus
  Serial.print("Device 0 Address: ");
  printAddress(insideThermometer);
  Serial.println();

  Serial.print("Device 0 Alarms: ");
  printAlarms(insideThermometer);
  Serial.println();

  Serial.print("Device 1 Address: ");
  printAddress(outsideThermometer);
  Serial.println();

  Serial.print("Device 1 Alarms: ");
  printAlarms(outsideThermometer);
  Serial.println();

  Serial.print("New Device 0 Alarms: ");
  printAlarms(insideThermometer);
  Serial.println();

  Serial.print("New Device 1 Alarms: ");
  printAlarms(outsideThermometer);
  Serial.println();
}
