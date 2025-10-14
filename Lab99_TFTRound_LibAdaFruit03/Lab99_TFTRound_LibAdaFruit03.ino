/*
Microgenios Tecnologia e Educação.
www.microgenios.com.br / www.microgeniosacademy.com.br
Curso: Formação LabGenios Nano
Instrutor: Gabriel Rosa Paz
Data: 04/10/2025

Laboratórios para estudo de utilização do Display TFT Circular
Utilização da Biblioteca Adafruit de Display Gráfico
Laboratório 99 - Controle raio de círculo preenchido com a leitura do ADC
*/

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>

// Pinos SPI do display
#define TFT_CS   10
#define TFT_DC    9
#define TFT_RST   8

Adafruit_GC9A01A tft(TFT_CS, TFT_DC, TFT_RST);

//Definições das cores:
#define WHITE  tft.color565(255,255,255)
#define BLACK  tft.color565(0,0,0)
#define RED    tft.color565(255,0,0)

const int16_t CX = 120;   // centro X
const int16_t CY = 120;   // centro Y
const int16_t R_MAX = 115;

int16_t lastR = -1;       // raio anterior (inicialmente “nenhum”)

void setup() 
{
  tft.begin();            //Inicializa o Display
  tft.setRotation(0);     //Rotação inicial do Display 0°
  tft.fillScreen(BLACK);   //Cor de fundo

  //Serial para depuração:
  Serial.begin(9600);
}

void loop() 
{
  unsigned int leituraADC = 0;  
  
  //Faz uma média das leituras do ADC
  for(unsigned char i = 0; i < 10; i++)
  {
    leituraADC += analogRead(A6);
    //Apenas para verirficar se os valores estavam corretos:
    //Serial.print("leituraADC = ");
    //Serial.println(leituraADC);
    //delay(1000);
  }
  leituraADC = leituraADC / 10; //0..1023
  int16_t raio = map(leituraADC, 0, 1023, 0, R_MAX);   //Mapeia para o intervalo de valores do raio 0..115
  //Apenas para verirficar se os valores estavam corretos:
  //Serial.print("raio = ");
  //Serial.println(raio);
  //delay(1000);
  
  //Apaga o círculo anterior se a entrada variar
  if (raio != lastR) 
  {
    tft.fillCircle(CX, CY, lastR, BLACK);
  }

  // desenha o novo círculo
  tft.fillCircle(CX, CY, raio, RED);

  lastR = raio;
  //delay(30);   // suaviza a atualização
}

