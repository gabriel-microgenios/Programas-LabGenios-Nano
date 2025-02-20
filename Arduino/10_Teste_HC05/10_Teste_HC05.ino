/* 
Microgenios Academy
Microgenios Tecnologia e Educação Ltda.
www.microgeniosacademy.com.br / www.microgenios.com.br
Formação: Aprenda Arduino, Programação, Eletrônica e Microcontroladores com a placa LabGenios Nano
Ano: 2023
Responsável: Gabriel Rosa Paz

LabGenios Nano - Teste 10: Teste Expansão Bluetooth HC-05

I/Os para conexão com o Módulo Bluetooth HC-05 (conexão com a UART):
D0/RX - Conectado ao TX do HC-05
D1/TX - Conectado ao RX do HC-05

RX - Recepção
TX - Transmissão
*/

//Constantes: 
const char potPin = A6; // Potenciometro ligado a Entrada Analogica 0


void setup() 
{
  //Configuração da porta serial com Baudrate de 9600bps
  Serial.begin(9600);
}

void loop() 
{
  // Declaração de variáveis
  int valorAD = 0;

  valorAD = analogRead(potPin);//Faz a leitura do conversor AD

  //Transmite pela serial a leitura do AD
  Serial.print("Valor lido no AD: ");
  Serial.println(valorAD);
  delay(2000);

}