/* 
Microgenios Tecnologia e Educação.
www.microgenios.com.br / www.microgeniosacademy.com.br
Curso: Formação LabGenios Nano
Instrutor: Gabriel Rosa Paz
Data: 19/02/2025

Laboratório 15: Desenvolva um programa capaz de medir a largura de pulsos 
que forem aplicados na Entrada de Interrupção Externa INT1 (D3).
Dica a função micros() pode ser útil
*/

const int pinoSinal = 3;  //Pino de entrada do sinal INT1 (D3)
//volatile unsigned long tempoSubida = 0;
//volatile unsigned long tempoDescida = 0;
volatile unsigned long larguraPulsoAlto = 0;
volatile unsigned long larguraPulsoBaixo = 0;
volatile unsigned long inicioAlto = 0;
volatile unsigned long fimAlto = 0;
volatile unsigned long inicioBaixo = 0;
volatile unsigned long fimBaixo = 0;
unsigned int tempoAtualiza = 3000;

void detectarSubida() 
{
  //tempoSubida = micros();  // Salva o tempo da borda de subida
  inicioAlto = micros();
  fimBaixo = inicioAlto;
  larguraPulsoBaixo = fimBaixo - inicioBaixo;
  attachInterrupt(digitalPinToInterrupt(pinoSinal), detectarDescida, FALLING);
}

void detectarDescida() {
  //tempoDescida = micros();  // Salva o tempo da borda de descida
  //larguraPulso = tempoDescida - tempoSubida;
  inicioBaixo = micros();
  fimAlto = inicioBaixo;
  larguraPulsoAlto = fimAlto - inicioAlto;
  attachInterrupt(digitalPinToInterrupt(pinoSinal), detectarSubida, RISING);
}

void setup() {
  Serial.begin(9600);
  pinMode(pinoSinal, INPUT);
  attachInterrupt(digitalPinToInterrupt(pinoSinal), detectarSubida, RISING);
}

void loop() 
{
  static float frequencia = 0;
  static unsigned int tempoAnterior = 0;
  static unsigned int tempoAtual = 0;
  
  frequencia = 1./((larguraPulsoAlto/1000000.) + (larguraPulsoBaixo/1000000.)); //f = 1/T

  tempoAtual = millis(); //Pega a contagem atual de milisegundos

  if((tempoAtual - tempoAnterior) >= tempoAtualiza) //Testa para verificar se atigiu o tempo definido
  {
    tempoAnterior = tempoAtual; //Atualiza contagemAnterior om o último valor lido
  
    Serial.print("Largura do pulso em Nivel Alto: ");
    Serial.print(larguraPulsoAlto);
    Serial.println(" us");
    larguraPulsoAlto = 0;

    Serial.print("Largura do pulso em Nivel Baixo: ");
    Serial.print(larguraPulsoBaixo);
    Serial.println(" us");
    larguraPulsoBaixo = 0;

    Serial.print("Frequencia do sinal: ");
    Serial.print(frequencia,2);
    Serial.println(" Hz");
  }
}
