/* 
Microgenios Tecnologia e Educação.
www.microgenios.com.br / www.microgeniosacademy.com.br
Curso: Formação LabGenios Nano
Instrutor: Gabriel Rosa Paz
Data: 20/09/2025

Laboratórios para estudo de utilização do Display OLED 0,96"
Laboratório 90 - Animação com imagens
*/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <avr/pgmspace.h> //Para PROGMEM
#include "imagens.h" //Arquivo para guardar os vetores das imagens

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET   -1
#define OLED_ADDR    0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() 
{
  //Configuração e Inicialização:
  Wire.begin(); //Arduino Nano: SDA=A4, SCL=A5
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();//Limpa o Display
}

void loop() 
{
  //Animação da carinha:
  //Envio da imagem para o display OLED:
  //Carinha 1:
  display.clearDisplay();//Limpa o Display
  display.drawBitmap(0, 0, epd_bitmap_CarinhaPiscando01, 128, 64, WHITE); //display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.display();

  delay(3000);
  
  //Carinha 2:
  display.clearDisplay();//Limpa o Display
  display.drawBitmap(0, 0, epd_bitmap_CarinhaPiscando02, 128, 64, WHITE); //display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.display();

  delay(30);

  //Carinha 3:
  display.clearDisplay();//Limpa o Display
  display.drawBitmap(0, 0, epd_bitmap_CarinhaPiscando03, 128, 64, WHITE); //display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.display();

  delay(30);

  //Carinha 4:
  display.clearDisplay();//Limpa o Display
  display.drawBitmap(0, 0, epd_bitmap_CarinhaPiscando04, 128, 64, WHITE); //display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.display();

  delay(1000);

}
