/* 
Microgenios Academy
Microgenios Tecnologia e Educação Ltda.
www.microgeniosacademy.com.br / www.microgenios.com.br
Formação: Aprenda Arduino, Programação, Eletrônica e Microcontroladores com a placa LabGenios Nano
Ano: 2023
Responsável: Gabriel Rosa Paz

LabGenios Nano - Teste 06: Teste Trimpot e Comunicação Serial

Atenção! 
O LDR e o trimpot estão conectados ao mesmo pino de Entrada Analógica (A6), 
desta forma é necessário selecionar qual periférico será utilizado no Jumper J5:

TRIMPOT - Esquerda
LDR - Direita

Entrada Analógica Trimpot:
A6 - Trimpot

Taxa de Transmissão da Comunicação Serial:
Baudrate: 9.600bps
*/

int potPin = 6; // Potenciometro ligado a Entrada Analogica 6

int ValorAD; // Variavel para armazenar o valor do A/D
float ValorFinal; //Variável para conversão do valor de tensão elétrica

void setup()
{
  // Configuração do Baudrate serial
  Serial.begin(9600);
}

void loop()
{
  // Realiza a leitura da entrada analógica
  ValorAD = analogRead(potPin);
  
  // Converte em tensão  0V a 5V
  ValorFinal = ValorAD * 0.0049;
  
  // Envia pelo canal serial
  Serial.println(ValorFinal,2); //Formatado para 2 casas decimais
  
}
