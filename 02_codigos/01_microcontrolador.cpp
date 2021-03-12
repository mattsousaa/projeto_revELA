#include <stdint.h>
#include <Arduino.h>

// ===================================================================================
// --- Mapeamento de Hardware ---
#define EMG1      0                   // PF0/ADC0 pin (sensor 1)
#define EMG2      1                   // PF1/ADC1 pin (sensor 2)
#define EMG3      2                   // PF2/ADC2 pin (sensor 3)
#define EMG4      3                   // PF3/ADC3 pin (sensor 4)
#define PWM1      6                   // PH3 (OC4A) pin (car 1)
#define PWM2      7                   // PH4 (OC4B) pin (car 2)
#define PWM3      8                   // PH5 (OC4C) pin (car 3)
#define PWM4      9                   // PH6 (OC2B) pin (car 4)

// ===================================================================================
// --- Constantes Auxiliares ---
#define N         100                 // Número de pontos da média móvel

// ===================================================================================
// --- Protótipo da Função ---
uint32_t moving_average(uint8_t sensorValue, uint8_t *number);  // Função de Filtro 

// ===================================================================================
// --- Variáveis Globais ---
uint8_t rawSensor1,                       // Recebe valor sensor 1 
        rawSensor2,                       // Recebe valor sensor 2
        rawSensor3,                       // Recebe valor sensor 3
        rawSensor4,                       // Recebe valor sensor 4
        dataFiltered1,                    // Recebe valor original filtrado do sensor 1
        dataFiltered2,                    // Recebe valor original filtrado do sensor 2
        dataFiltered3,                    // Recebe valor original filtrado do sensor 3
        dataFiltered4;                    // Recebe valor original filtrado do sensor 4

uint8_t valuesAvg1[N],                    // Vetor com os valores para média móvel do sensor 1
        valuesAvg2[N],                    // Vetor com os valores para média móvel do sensor 2
        valuesAvg3[N],                    // Vetor com os valores para média móvel do sensor 3
        valuesAvg4[N];                    // Vetor com os valores para média móvel do sensor 4

// ===================================================================================
// --- Interrupções ---
ISR(INT0_vect){

  PORTA ^= (1 << DDA0);

} // end ISR 1 (1st IR sensor)

ISR(INT1_vect){

  PORTB ^= (1 << DDB0);

} // end ISR 2 (2nd IR sensor)

ISR(INT4_vect){

  PORTA ^= (1 << DDA2);

} // end ISR 3 (3rd IR sensor)

ISR(INT5_vect){

  PORTB ^= (1 << DDB1);

} // end ISR 4 (4th IR sensor)

void setup() {

  /* ############################ Configura baud rate das portas seriais ############################ */

  Serial.begin(115200);               // Porta serial COM1 com dados jogador 1 - baud rate de 115200
  Serial1.begin(115200);              // Porta serial COM2 com dados jogador 2 - baud rate de 115200
  Serial2.begin(115200);              // Porta serial COM3 com dados jogador 3 - baud rate de 115200
  Serial3.begin(115200);              // Porta serial COM4 com dados jogador 4 - baud rate de 115200

  /* ############################ Configura os sensores eletromiograficos ############################ */

  pinMode(EMG1, INPUT);               // Configura entrada para EMG do 1º jogador
  pinMode(EMG2, INPUT);               // Configura entrada para o sinal de EMG do 2º jogador
  pinMode(EMG3, INPUT);               // Configura entrada para o sinal de EMG do 3º jogador
  pinMode(EMG4, INPUT);               // Configura entrada para o sinal de EMG do 4º jogador

  /* ############################ Configura as saídas PWM para cada carro ############################ */

  pinMode(PWM1, OUTPUT);              // Configura saída PWM para controle do carro 1
  pinMode(PWM2, OUTPUT);              // Configura saída PWM para controle do carro 2
  pinMode(PWM3, OUTPUT);              // Configura saída PWM para controle do carro 3
  pinMode(PWM4, OUTPUT);              // Configura saída PWM para controle do carro 4

  /* ############################ Configura os sensores IR para cada carro ############################ */

  DDRD &= ~(1 << DDD0);               // Configura o sensor IR do carro 1 como entrada (PD0)
  DDRD &= ~(1 << DDD1);               // Configura o sensor IR do carro 2 como entrada (PD1)
  DDRE &= ~(1 << DDE4);               // Configura o sensor IR do carro 3 como entrada (PE4)
  DDRE &= ~(1 << DDE5);               // Configura o sensor IR do carro 4 como entrada (PE5)

  /* ############################ Configura os LEDs indicadores de chegada ############################ */

  DDRA |= (1 << DDA0);                // Configura o LED de chegada do carro 1 no pino PA0
  DDRB |= (1 << DDB0);                // Configura o LED de chegada do carro 2 no pino PA1
  DDRA |= (1 << DDA2);                // Configura o LED de chegada do carro 3 no pino PA2
  DDRB |= (1 << DDB1);                // Configura o LED de chegada do carro 4 no pino PA3

  /* ############################ Configura pull-up interno de cada sensor IR ############################ */

  PORTD |= (1 << PORTD0);             // Configura o pull-up interno de PD0
  PORTD |= (1 << PORTD1);             // Configura o pull-up interno de PD1
  PORTE |= (1 << PORTE4);             // Configura o pull-up interno de PE4
  PORTE |= (1 << PORTE5);             // Configura o pull-up interno de PE5

  /* ############################ Configura interrupção externa por borda de subida ############################ */

  EICRA |= (1 << ISC01) | (1 << ISC00);   // Configuta interrupção externa nos pinos INT3:0 por qualquer borda
  EICRB |= (1 << ISC01) | (1 << ISC00);   // Configuta interrupção externa nos pinos INT7:4 por qualquer borda

  /* ############################ Habilita interrupções externas para cada sensor IR ############################ */

  EIMSK |= (1 << INT0);               // Habilita interrupção externa 0
  EIMSK |= (1 << INT1);               // Habilita interrupção externa 1
  EIMSK |= (1 << INT4);               // Habilita interrupção externa 4
  EIMSK |= (1 << INT5);               // Habilita interrupção externa 5

  PORTA = 0x00;
  PORTB = 0x00;

  sei();                              // Habilita interrupções globais
  
}

void loop() {
  
  /* Normaliza valor do sensor (A/D - 10 bits) para 8 bits (PWM) */
  rawSensor1 = analogRead(EMG1)/4;
  rawSensor2 = analogRead(EMG2)/4;
  rawSensor3 = analogRead(EMG3)/4;
  rawSensor4 = analogRead(EMG4)/4;
  
  /* Filtro média móvel para amenizar flutuações de tensão dos sensores */
  dataFiltered1 = moving_average(rawSensor1, valuesAvg1);
  dataFiltered2 = moving_average(rawSensor2, valuesAvg2);
  dataFiltered3 = moving_average(rawSensor3, valuesAvg3);
  dataFiltered4 = moving_average(rawSensor4, valuesAvg4);

  /* Manda os dados pela serial para plotagem em tempo real / Armazena dados em um CSV */

  // Sends all data via a single serial port (COM1) 
  Serial.print(dataFiltered1); 
  Serial.print(",");
  Serial.print(dataFiltered2);
  Serial.print(",");
  Serial.print(dataFiltered3);
  Serial.print(",");
  Serial.println(dataFiltered4);

  // Sends all data through the 4 serial ports (COM1, COM2, COM3, COM4)
  //Serial.print(dataFiltered1)
  //Serial1.println(dataFiltered2);
  //Serial2.println(dataFiltered3);
  //Serial3.println(dataFiltered4); 

  /* Ajusta o Duty Cycle de acordo com a tensão lida por cada sensor */
  digitalWrite(PWM1, dataFiltered1);
  digitalWrite(PWM2, dataFiltered2);
  digitalWrite(PWM3, dataFiltered3);
  digitalWrite(PWM4, dataFiltered4);
      
}

// ===============================================================================
// --- Função para filtragem ---

uint32_t moving_average(uint8_t sensorValue, uint8_t *number){

  uint32_t acc = 0;                                       // Acumulador para somar os pontos da média móvel

  // Desloca os elementos do vetor de média móvel
  for(uint8_t i = N - 1; i > 0; i--) number[i] = number[i-1];

  number[0] = sensorValue;                                // Posição inicial do vetor recebe a leitura original

  for(uint8_t i = 0; i < N; i++) acc += number[i];        // Faz a somatória do número de pontos

  return acc/N;                                           // Retorna a média móvel

}
