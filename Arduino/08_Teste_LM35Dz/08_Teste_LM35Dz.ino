/* 
Microgenios Academy
Microgenios Tecnologia e Educação Ltda.
www.microgeniosacademy.com.br / www.microgenios.com.br
Formação: Aprenda Arduino, Programação, Eletrônica e Microcontroladores com a placa LabGenios Nano
Ano: 2023
Responsável: Gabriel Rosa Paz

LabGenios Nano - Teste 08: Teste Sensor de Temperatura LM35Dz

Entrada Analógica conectada ao LM35Dz:
A7 - LM35Dz

I/Os Digitais utilizados para conexão com o Display OLED:
A4 - Sinal SDA
A5 - Sinal SCL

Projeto original criado por ArduinoGetStarted.com
 https://arduinogetstarted.com/tutorials/arduino-display-temperature-from-lm35-sensor-on-oled
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define ADC_VREF_mV    5000.0 // in millivolt
#define ADC_RESOLUTION 1024.0

#define PIN_LM35 A7 //Pino de Entrada Analógica A7 Ligado ao LM35Dz

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // create SSD1306 display object connected to I2C

String tempString;

void setup() {
  Serial.begin(9600);

  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  delay(2000);         // wait for initializing
  oled.clearDisplay(); // clear display

  oled.setTextSize(2);      // text size
  oled.setTextColor(WHITE); // text color
  oled.setCursor(0, 10);    // position to display

  tempString.reserve(10);   // to avoid fragmenting memory when using String
}

void loop() {
  // get the ADC value from the LM35 temperature sensor
  int adcVal = analogRead(PIN_LM35);
  // convert the ADC value to voltage in millivolt
  float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION);
  // convert the voltage to the temperature in Celsius
  float tempC = milliVolt / 10;

  tempString  = String(tempC, 2); // two decimal places
  tempString += "C";

  Serial.println(tempString);    // print the temperature in Celsius to Serial Monitor
  oledDisplayCenter(tempString); // display temperature on OLED
}

void oledDisplayCenter(String text) {
  int16_t x1;
  int16_t y1;
  uint16_t width;
  uint16_t height;

  oled.getTextBounds(text, 0, 0, &x1, &y1, &width, &height);

  // display on horizontal and vertical center
  oled.clearDisplay(); // clear display
  oled.setCursor((SCREEN_WIDTH - width) / 2, (SCREEN_HEIGHT - height) / 2);
  oled.println(text); // text to display
  oled.display();
}
