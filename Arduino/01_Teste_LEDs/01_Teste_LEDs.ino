/* 
Microgenios Academy
Microgenios Tecnologia e Educação Ltda.
www.microgeniosacademy.com.br / www.microgenios.com.br
Formação: Aprenda Arduino, Programação, Eletrônica e Microcontroladores com a placa LabGenios Nano
Ano: 2023
Responsável: Gabriel Rosa Paz

LabGenios Nano - Teste 01: Teste dos LEDs e Display de 7 Segmentos (Saídas Digitais)

Jumper J3 seleciona o uso dos LEDs ou do Display de 7 Segmentos.
Posições:
* 7SEG (Esquerda)
* LEDS (Direita)


I/Os Digitais utilizados para os LEDs:
D4 - LED Vermelho
D5 - LED Amarelo
D6 - LED Verde
D7 - LED Vermelho
D8 - LED Amarelo
D12 - LED Verde
D13 - LED Azul

I/Os Digitais utilizados para o Display de 7 Segmentos:
D4 - Segmento A
D5 - Segmento B
D6 - Segmento C
D7 - Segmento D
D8 - Segmento E
D12 - Segmento F
D13 - Segmento G
*/

void setup() 
{
  //Configuração dos pinos de IO como saída:
  pinMode(4, OUTPUT);    
  pinMode(5, OUTPUT);    
  pinMode(6, OUTPUT);    
  pinMode(7, OUTPUT);    
  pinMode(8, OUTPUT);    
  pinMode(12, OUTPUT);    
  pinMode(13, OUTPUT);    

  //Iniciando os pinos de IO em nível lógico baixo (ZERO) - LEDs e Display de 7 Segmentos Apagados:
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
}

void loop() 
{
  //LED ligado ao IO Digital D4:
  digitalWrite(4, HIGH); 
  delay(500);            
  digitalWrite(4, LOW);  
  delay(500); 

  //LED ligado ao IO Digital D5:
  digitalWrite(5, HIGH); 
  delay(500);            
  digitalWrite(5, LOW);  
  delay(500); 

  //LED ligado ao IO Digital D6:
  digitalWrite(6, HIGH); 
  delay(500);            
  digitalWrite(6, LOW);  
  delay(500); 

  //LED ligado ao IO Digital D7:
  digitalWrite(7, HIGH); 
  delay(500);            
  digitalWrite(7, LOW);  
  delay(500);

  //LED ligado ao IO Digital D8:
  digitalWrite(8, HIGH); 
  delay(500);            
  digitalWrite(8, LOW);  
  delay(500); 

  //LED ligado ao IO Digital D12:
  digitalWrite(12, HIGH); 
  delay(500);            
  digitalWrite(12, LOW);  
  delay(500); 

  //LED ligado ao IO Digital D13:
  digitalWrite(13, HIGH); 
  delay(500);            
  digitalWrite(13, LOW);  
  delay(500);
}
