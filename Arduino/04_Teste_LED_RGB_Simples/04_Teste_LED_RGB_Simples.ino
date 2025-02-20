/* 
Microgenios Academy
Microgenios Tecnologia e Educação Ltda.
www.microgeniosacademy.com.br / www.microgenios.com.br
Formação: Aprenda Arduino, Programação, Eletrônica e Microcontroladores com a placa LabGenios Nano
Ano: 2023
Responsável: Gabriel Rosa Paz

LabGenios Nano - Teste 04: Teste do LED RGB

I/Os Digitais utilizados para os LEDs:
D9 - LED Azul (Blue)
D10 - LED Verde (Green)
D11 - LED Vermelho (Red)
*/

//Definições de "apelidos" para os pinos ligados ao sinais de entrada do LED RGB
#define redOut 11    //Vermelho
#define greenOut 10  //Verde
#define blueOut 9    //Azul

void setup() 
{
  //Configuração dos IOs como saída
  pinMode(redOut, OUTPUT);
  pinMode(greenOut, OUTPUT);
  pinMode(blueOut, OUTPUT);

  //Valor inicial dos IOs - R, G e B apagados
  digitalWrite(redOut, LOW);
  digitalWrite(greenOut, LOW);
  digitalWrite(blueOut, LOW);
}

void loop() 
{
  //Acende o Vermelho apenas
  digitalWrite(redOut, HIGH);
  digitalWrite(greenOut, LOW);
  digitalWrite(blueOut, LOW);  
  delay(500); //Tempo de 0,5 segundo

  //Acende o Verde apenas
  digitalWrite(redOut, LOW);
  digitalWrite(greenOut, HIGH);
  digitalWrite(blueOut, LOW);  
  delay(500); //Tempo de 0,5 segundo

  //Acende o Azul apenas
  digitalWrite(redOut, LOW);
  digitalWrite(greenOut, LOW);
  digitalWrite(blueOut, HIGH);  
  delay(500); //Tempo de 0,5 segundo
}
