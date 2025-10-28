/*  
Microgenios Tecnologia e Educação.
www.microgenios.com.br / www.microgeniosacademy.com.br
Curso: Formação LabGenios Nano
Instrutor: Gabriel Rosa Paz
Data: 27/10/2025

Laboratório Especial: Halloween Runner — OLED 128x64 + 3 botões + buzzer (D3)
Placa: LabGenios Nano com Arduino Nano (ATmega328P)
OLED: SSD1306 128x64 I2C (0x3C)
Botões: A0=UP, A2=DOWN, A1=START/RESET (pull-up interno)
Buzzer: D3 (tone())
*/

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

//Inclusão o arquivo .h com o vetor contendo a imagem:
#include "imagem.h"

// ---------- Display OLED ----------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ---------- Pinos de IO ----------
const uint8_t PIN_BTN_UP    = A0;
const uint8_t PIN_BTN_DOWN  = A2;
const uint8_t PIN_BTN_START = A1;
const uint8_t PIN_BUZZER    = 3;

// ---------- Estados de Execução ----------
enum GameState { TITLE, RUNNING, GAMEOVER };
GameState state = TITLE;

// ---------- Jogabilidade ----------
const uint8_t PLAYER_X = 20;
int16_t playerY;                   // posição vertical do jogador
const uint8_t PLAYER_HALF = 2;     // metade do tamanho do “quadradinho”
const uint8_t PATH_HALF_WIDTH = 7; // semi-largura do corredor

//Pontuação (distância percorrida):
uint16_t distanceTraveled = 0;

//Buffer com o centro do corredor por coluna (rolagem):
int8_t centerBuf[SCREEN_WIDTH];

unsigned long lastFrame = 0;
const uint8_t FRAME_MS = 33; // ~30 FPS

// ---------- Imagem da abóbora (ou outra caso queira customizar) ----------
//IMPORTANTE: garanta que o vetor dessa imagem esteja no arquivo imagem.h
extern const unsigned char epd_bitmap_AboboraHallowen_128x64[] PROGMEM;

// ---------- Utils de botões ----------
//Função decara da como "inline" sugere que o compilador insira ela no local de sua chamada.
//Ou seja, sem custo de chamada de função (sem empilhar parâmetros, salvar registradores etc.).
inline bool pressed(uint8_t pin) 
{ 
  return digitalRead(pin) == LOW; //Aqui testa se o botão está pressionado "==", não é uma atribuição!
}

// ---------- Sons ----------
void beep(uint16_t f, uint16_t ms) 
{
  tone(PIN_BUZZER, f, ms);
}

void soundStart() 
{
  // Acorde menor “macabro”
  beep(392,120); delay(130);
  beep(466,120); delay(130);
  beep(523,160); delay(180);
}

void soundStep() 
{
  beep(880,20);
}

void soundHit() 
{
  for (int i=0;i<3;i++)
  { 
    beep(200,90); 
    delay(110); 
  }
}

void soundJumpscare() 
{
  // Trítono + queda
  beep(740,250); 
  delay(260);
  beep(1046,250); 
  delay(260);
  for (int f=1000; f>=120; f-=35)
  { 
    beep(f,20); 
    delay(22); 
  }
}

// ---------- Geração do corredor ----------
int8_t clampCenter(int8_t c)
{
  if (c < PATH_HALF_WIDTH+2) 
    return PATH_HALF_WIDTH+2;
  
  if (c > (SCREEN_HEIGHT-1) - (PATH_HALF_WIDTH+2)) 
    return (SCREEN_HEIGHT-1) - (PATH_HALF_WIDTH+2);
  
  return c;
}

int8_t nextCenter(int8_t prev)
{
  //Caminho sendo gerado aleatóriamente com variação no eixo Y: -2..+2 por coluna
  int8_t step = random(-2,3);
  int8_t c = clampCenter(prev + step);
  return c;
}

void resetPath(int8_t startCenter)
{
  for (int x=0; x<SCREEN_WIDTH; x++)
  {
    centerBuf[x] = startCenter;
  }
  // Pré-gira algumas colunas para suavizar o início
  for (int i=0; i<40; i++)
  {
    centerBuf[SCREEN_WIDTH-1] = nextCenter(centerBuf[SCREEN_WIDTH-2]);
    
    for (int x=0; x<SCREEN_WIDTH-1; x++) 
      centerBuf[x] = centerBuf[x+1];
  }
}

void scrollPath()
{
  for (int x=0; x<SCREEN_WIDTH-1; x++)
  {
    centerBuf[x] = centerBuf[x+1];
  }
  centerBuf[SCREEN_WIDTH-1] = nextCenter(centerBuf[SCREEN_WIDTH-2]);
}

bool playerInsideCorridor()
{
  int8_t c = centerBuf[PLAYER_X];
  
  return (playerY >= c - PATH_HALF_WIDTH) && (playerY <= c + PATH_HALF_WIDTH);
}

// ---------- Desenho ----------
void drawTitle()
{
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(8,10);
  display.println(F("HALLOWEEN"));
  display.setTextSize(1);
  display.setCursor(10,34);
  display.println(F("A0=UP  A2=DOWN"));
  display.setCursor(10,46);
  display.println(F("A1=START/RESET"));
  display.display();
}

void drawPathAndPlayer()
{
  display.clearDisplay();

  // Paredes
  for (int x=0; x<SCREEN_WIDTH; x++)
  {
    int8_t c = centerBuf[x];
    int8_t topWallEnd = c - PATH_HALF_WIDTH - 1;
    int8_t bottomWallStart = c + PATH_HALF_WIDTH + 1;

    if (topWallEnd >= 0) 
      display.drawFastVLine(x, 0, topWallEnd+1, SSD1306_WHITE);

    if (bottomWallStart < SCREEN_HEIGHT)
      display.drawFastVLine(x, bottomWallStart, SCREEN_HEIGHT - bottomWallStart, SSD1306_WHITE);
  }

  // Player
  display.fillRect(PLAYER_X-PLAYER_HALF, playerY-PLAYER_HALF, 2*PLAYER_HALF+1, 2*PLAYER_HALF+1, SSD1306_WHITE);

  //HUD (pontuação):
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print(F("m: "));
  display.print(distanceTraveled);

  display.display();
}

void showPumpkin()
{
  display.clearDisplay();
  //Desenha sua abóbora 128x64:
  display.drawBitmap(0, 0, epd_bitmap_AboboraHallowen_128x64, 128, 64, SSD1306_WHITE);
  display.display();
}

// ---------- Setup ----------
void setup() 
{
  pinMode(PIN_BTN_UP,    INPUT_PULLUP);
  pinMode(PIN_BTN_DOWN,  INPUT_PULLUP);
  pinMode(PIN_BTN_START, INPUT_PULLUP);
  pinMode(PIN_BUZZER,    OUTPUT);

  Wire.begin();
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  {
    for(;;); // falhou — verifique I2C/endereçamento
  }
  display.clearDisplay();
  display.display();

  randomSeed(analogRead(A3)); // seed simples

  playerY = SCREEN_HEIGHT/2;
  resetPath(playerY);
  drawTitle();
  soundStart();
}

// ---------- Loop ----------
void loop() 
{
  unsigned long now = millis();

  switch(state)
  {
    case TITLE:
      if (pressed(PIN_BTN_START))
      {
        playerY = SCREEN_HEIGHT/2;
        resetPath(playerY);
        distanceTraveled = 0;
        state = RUNNING;
        delay(200); // anti-repique
      }
      break;

    case RUNNING:
      if (now - lastFrame >= FRAME_MS)
      {
        lastFrame = now;

        // Controles
        if (pressed(PIN_BTN_UP))   
        { 
          if (playerY > 1) 
          { 
            playerY--; soundStep(); 
          } 
        }
        if (pressed(PIN_BTN_DOWN)) 
        { 
          if (playerY < SCREEN_HEIGHT-2) 
          { 
            playerY++; soundStep(); 
          } 
        }

        scrollPath();
        distanceTraveled++;

        // Colisão => susto + abóbora + game over
        if (!playerInsideCorridor())
        {
          // 1) Mostra a abóbora
          showPumpkin();
          // 2) Toca som assustador
          soundJumpscare();
          delay(1200);

          // 3) Mensagem de Game Over
          display.clearDisplay();
          display.setTextColor(SSD1306_WHITE);
          display.setTextSize(2);
          display.setCursor(15,20);
          display.println(F("GAME"));
          display.setCursor(15,40);
          display.println(F("OVER"));
          display.display();

          state = GAMEOVER;
          break;
        }

        // Render normal
        drawPathAndPlayer();
      }

      // Reset a qualquer momento
      if (pressed(PIN_BTN_START))
      {
        state = TITLE;
        drawTitle();
        delay(200);
      }
      break;

    case GAMEOVER:
      // Volta ao título ao apertar START
      if (pressed(PIN_BTN_START))
      {
        state = TITLE;
        drawTitle();
        delay(200);
      }
      break;
  }
}
