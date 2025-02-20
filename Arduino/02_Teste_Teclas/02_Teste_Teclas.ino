/* 
Microgenios Academy
Microgenios Tecnologia e Educação Ltda.
www.microgeniosacademy.com.br / www.microgenios.com.br
Formação: Aprenda Arduino, Programação, Eletrônica e Microcontroladores com a placa LabGenios Nano
Ano: 2023
Responsável: Gabriel Rosa Paz

LabGenios Nano - Teste 02: Teste das Teclas (Entradas Digitais)

Atenção a tecla Tecla A/Círculo (SW6) e o Buzzer estão conectados ao mesmo pino de IO Digital D3,
para desligar o Buzzer retire o Jumper J4 

Conexões de IO utilizadas neste programa:

I/Os utilizados para as Teclas:
A0 - Tecla Up/Cima (SW3)
A1 - Tecla Left/Esquerda (SW3)
A2 - Tecla Down/Baixo (SW4)
A3 - Tecla Right/Direita (SW5) 
D3 - Tecla A/Círculo (SW6)
D2 - Tecla B/Quadrado (SW7) 

I/Os Digitais utilizados para o Display de 7 Segmentos:
D4 - Segmento A
D5 - Segmento B
D6 - Segmento C
D7 - Segmento D
D8 - Segmento E
D12 - Segmento F
D13 - Segmento G
*/

//Definição de constantes ("apelidos") para as saídas (Disp 7 Seg):
#define segA 4
#define segB 5
#define segC 6
#define segD 7
#define segE 8
#define segF 12
#define segG 13

//Definição de constantes ("apelidos") para as estradas (Teclas):
#define Up A0
#define Down A2
#define Left A1
#define Right A3
#define TecA 3
#define TecB 2


void setup() {
  //Configuração dos pinos de IO ligados ao Display de 7 Segmentos como saída:
  pinMode(segA, OUTPUT);    
  pinMode(segB, OUTPUT);    
  pinMode(segC, OUTPUT);    
  pinMode(segD, OUTPUT);    
  pinMode(segE, OUTPUT);    
  pinMode(segF, OUTPUT);    
  pinMode(segG, OUTPUT);   

  //Configuração dos pinos de IO ligados as teclas como entrada:
  pinMode(Up, INPUT_PULLUP);    
  pinMode(Down, INPUT_PULLUP);    
  pinMode(Right, INPUT_PULLUP);    
  pinMode(Left, INPUT_PULLUP);    
  pinMode(TecA, INPUT_PULLUP);    
  pinMode(TecB, INPUT_PULLUP);    

  //Iniciando com todos os segmentos do Display desligados:
  digitalWrite(segA, LOW);
  digitalWrite(segB, LOW);
  digitalWrite(segC, LOW);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);

  //Iniciando pinos de entrada com 1:
  digitalWrite(Up, HIGH);
  digitalWrite(Down, HIGH);
  digitalWrite(Right, HIGH);
  digitalWrite(Left, HIGH);
  digitalWrite(TecA, HIGH);
  digitalWrite(TecB, HIGH);

}

void loop() {
  //Verfica se a Tecla Up foi pressionada e se verdadeiro -> Acende Número 0
  if(digitalRead(Up)==0){
    digitalWrite(segA, HIGH);
    digitalWrite(segB, HIGH);
    digitalWrite(segC, HIGH);
    digitalWrite(segD, HIGH);
    digitalWrite(segE, HIGH);
    digitalWrite(segF, HIGH);
    digitalWrite(segG, LOW);
    while(digitalRead(Up)==0); //Espera soltar a tecla para continuar
  }

  //Verfica se a Tecla Down foi pressionada e se verdadeiro -> Acende Número 1
  if(digitalRead(Down)==0){
    digitalWrite(segA, LOW);
    digitalWrite(segB, HIGH);
    digitalWrite(segC, HIGH);
    digitalWrite(segD, LOW);
    digitalWrite(segE, LOW);
    digitalWrite(segF, LOW);
    digitalWrite(segG, LOW);
    while(digitalRead(Down)==0); //Espera soltar a tecla para continuar
  }

  //Verfica se a Tecla Right foi pressionada e se verdadeiro -> Acende Número 2
  if(digitalRead(Right)==0){
    digitalWrite(segA, HIGH);
    digitalWrite(segB, HIGH);
    digitalWrite(segC, LOW);
    digitalWrite(segD, HIGH);
    digitalWrite(segE, HIGH);
    digitalWrite(segF, LOW);
    digitalWrite(segG, HIGH);
    while(digitalRead(Right)==0); //Espera soltar a tecla para continuar
  }

  //Verfica se a Tecla Left foi pressionada e se verdadeiro -> Acende Número 3
  if(digitalRead(Left)==0){
    digitalWrite(segA, HIGH);
    digitalWrite(segB, HIGH);
    digitalWrite(segC, HIGH);
    digitalWrite(segD, HIGH);
    digitalWrite(segE, LOW);
    digitalWrite(segF, LOW);
    digitalWrite(segG, HIGH);
    while(digitalRead(Left)==0); //Espera soltar a tecla para continuar
  }

  //Verfica se a Tecla A (Círculo) foi pressionada e se verdadeiro -> Acende Número 4
  if(digitalRead(TecA)==0){
    digitalWrite(segA, LOW);
    digitalWrite(segB, HIGH);
    digitalWrite(segC, HIGH);
    digitalWrite(segD, LOW);
    digitalWrite(segE, LOW);
    digitalWrite(segF, HIGH);
    digitalWrite(segG, HIGH);
    while(digitalRead(TecA)==0); //Espera soltar a tecla para continuar
  }
  
  //Verfica se a Tecla B (Quadrado) foi pressionada e se verdadeiro -> Acende Número 5
  if(digitalRead(TecB)==0){
    digitalWrite(segA, HIGH);
    digitalWrite(segB, LOW);
    digitalWrite(segC, HIGH);
    digitalWrite(segD, HIGH);
    digitalWrite(segE, LOW);
    digitalWrite(segF, HIGH);
    digitalWrite(segG, HIGH);
    while(digitalRead(TecB)==0); //Espera soltar a tecla para continuar
  }

}
