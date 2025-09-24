/* 
Microgenios Tecnologia e Educação.
www.microgenios.com.br / www.microgeniosacademy.com.br
Curso: Formação LabGenios Nano
Instrutor: Gabriel Rosa Paz
Data: 05/09/2025

Laboratórios para estudo de Máquinas de Estados
Exemplo Básico de uso de Maquinas de Estados.
*/

/*---------------------------------------------------------------*/
// ====== Configuração de pinos ======
#define LED 9 //Cor Azul do LED RGB
#define BTN A0
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
// ====== Estados possíveis ======
enum Estado {DESLIGADO, LIGADO, LENTO, RAPIDO};
Estado estadoAtual = DESLIGADO; //Armazena o Estado Atual
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
// ====== Leitura de botão ======
bool botaoFoiPressionado() 
{
  if (digitalRead(BTN) == LOW) //INPUT_PULLUP: pressionado = LOW
  { 
    //Debounce simples:
    delay(25);                 
    if (digitalRead(BTN) == LOW) 
    {
      while (digitalRead(BTN) == LOW) { /* espera soltar */ }
      delay(10);
      return true;
    }
  }
  return false;
}
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
// === Configuração de Hardware e Estado Inicial após o RESET ===
void setup() 
{
  //Configuração do Hardware
  pinMode(LED, OUTPUT);
  pinMode(BTN, INPUT_PULLUP); // resistor interno; botão ao GND

  /*--- Estado do LED após o RESET ---*/
  digitalWrite(LED, LOW);
}
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
// ====== Rotina principal do nosso programa ======
void loop() 
{
  /*---------------------------------------------------------------*/
  //EVENTO: apertar botão -> transição de estado (carrossel):
  if (botaoFoiPressionado()) 
  {
    if (estadoAtual == DESLIGADO)      
      estadoAtual = LIGADO;
    else
      if (estadoAtual == LIGADO)     
        estadoAtual = LENTO;
      else 
        if (estadoAtual == LENTO)     
          estadoAtual = RAPIDO;
        else /* estadoAtual == RAPIDO */ 
            estadoAtual = DESLIGADO;
  }
  /*---------------------------------------------------------------*/

  /*---------------------------------------------------------------*/
  //Tarefas: o que fazer em cada estado:
  switch (estadoAtual) 
  {
    case DESLIGADO: //Estado Desligado
      digitalWrite(LED, LOW);
      delay(50); //pequena pausa
      break;
    
    case LIGADO: //Estado Ligado
      digitalWrite(LED, HIGH);
      delay(50); //pequena pausa
      break;

    case LENTO: //Estado LENTO
      digitalWrite(LED, HIGH); 
      delay(300);
      digitalWrite(LED, LOW);  
      delay(300);
      break;

    case RAPIDO: //Estado Rapido
      digitalWrite(LED, HIGH); 
      delay(100);
      digitalWrite(LED, LOW);  
      delay(100);
      break;
  }
  /*---------------------------------------------------------------*/
}

