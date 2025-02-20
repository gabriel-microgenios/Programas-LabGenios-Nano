/* 
Microgenios Academy
Microgenios Tecnologia e Educação Ltda.
www.microgeniosacademy.com.br / www.microgenios.com.br
Formação: Aprenda Arduino, Programação, Eletrônica e Microcontroladores com a placa LabGenios Nano
Ano: 2023
Responsável: Gabriel Rosa Paz

LabGenios Nano - Teste 05: Teste do sensor de luminosidade LDR

Atenção! 
O LDR e o trimpot estão conectados ao mesmo pino de Entrada Analógica (A6), 
desta forma é necessário selecionar qual periférico será utilizado no Jumper J5:

TRIMPOT - Esquerda
LDR - Direita


Entrada Analógica LDR:
A6 - LDR

I/O Digital LED Azul:
D13 - LED Azul
*/

//Define "apelido" (constante) para a Entrada Analógica que será conectada ao LDR
#define LDRpin A6                     

//Define "apelido" (constante) para a Saída Digital que será conectada ao LED Azul                   
#define LedAzul 13       

void setup()
{
  //Configura o pino ligado ao LED Azul como saída
  pinMode(LedAzul, OUTPUT);
  
  //Inicia com o LED Azul desligado
  digitalWrite(LedAzul, LOW);
}

void loop()
{
  //Variável para armazenar o valor lido do sensor de luminosidade (LDR)
  int LDRValue;
  
  //Lê o sensor de luminosidade e salva o valor na variável
  LDRValue = analogRead(LDRpin);        
  
  //Testa o valor lido do sensor de luminosidade
  if (LDRValue > 300) //Se for maior que 300 -> Apaga o LED
  {
    digitalWrite(LedAzul, LOW); 
  }
  else //Ou então -> Acende o LED Azul
  {
    digitalWrite(LedAzul, HIGH);
  }
}
