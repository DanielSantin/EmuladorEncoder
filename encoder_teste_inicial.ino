const int enc1 = 5;  // gpio5  -> D1   //passo do encoder 1
const int dir1 = 14; // gpio14 -> D5   //direção do encoder 1

const int enc2 = 4;  // gpio4  -> D2   //passo do encoder 2
const int dir2 = 12; // gpio12 -> D6   //direção do encoder 2

const int enc3 = 15; // gpio15 -> D8   //passo do encoder 3
const int dir3 = 13; // gpio13 -> D7   //direção do encoder 3

const int led_builtin = 2;


const float freq = 1000;                //Frequência desejada em Hz, valor padrão: 1000Hz.
const float percentualDefaultDuty = 10; //Quantidade percentual de Duty cycle

// Calculando os delays para utilizar no PWM Manual, estes valores são calculados baseados nos dois valores acima 
const float delaySinalAtivo = ((100-percentualDefaultDuty)/100)*(1/freq)*1000*1000; //Multiplica por 1000 duas vezes, já que o delay será aplicado em microsegundos
const float delaySinalDesativado = (percentualDefaultDuty/100)*(1/freq)*1000*1000;  


void setup() {  
  Serial.begin(115200);
  Serial.println("Inciando Setup");

  pinMode(led_builtin, OUTPUT);
  digitalWrite(led_builtin, LOW); //logica invertida
  
  
  //Definindo pinos para direção como saída
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(dir3, OUTPUT);
  //Definindo pinos para direção como valor padrão DESLIGADO
  digitalWrite(dir1, LOW);
  digitalWrite(dir2, LOW);
  digitalWrite(dir3, LOW);

  //Definindo pinos de mudança de posição de cada encoder como saída
  pinMode(enc1, OUTPUT);
  pinMode(enc2, OUTPUT);
  pinMode(enc3, OUTPUT);
  //Definindo pinos para valor padrão DESLIGADO
  digitalWrite(enc1, LOW);
  digitalWrite(enc2, LOW);
  digitalWrite(enc3, LOW);

  Serial.println("Setup concluído");

}

void loop() {
  //O intúito do seguinte código é simular um sinal PWM controlado, para assim simular um encoder.

  Serial.println("Iniciando passos do encoder 1");
  //loop para criar 100 passos
  for (int i = 0; i <= 100; i++) {
    //Simulando PWM para enc1 (OBS: a idéia é subistituir a função delay por vTaskDelayUntil() que é bem mais preciso)
    digitalWrite(enc1, HIGH);
    delayMicroseconds(delaySinalAtivo);
    digitalWrite(enc1, LOW);
    delayMicroseconds(delaySinalDesativado);
  }
  Serial.println("Passos encoder 1 finalizado");

  delay(1000);

  Serial.println("Iniciando passos do encoder 2");

  //Simulando PWM para enc2
  for (int i = 0; i <= 100; i++) {
    digitalWrite(enc2, HIGH);
    delayMicroseconds(delaySinalAtivo);
    digitalWrite(enc2, LOW);
    delayMicroseconds(delaySinalDesativado);
  }
  Serial.println("Passos encoder 2 finalizado");

  delay(1000);


  Serial.println("Iniciando passos do encoder 3");
  //Simulando PWM para enc3
  for (int i = 0; i <= 100; i++) {
    digitalWrite(enc3, HIGH);
    delayMicroseconds(delaySinalAtivo);
    digitalWrite(enc3, LOW);
    delayMicroseconds(delaySinalDesativado);
  }
  Serial.println("Passos encoder 3 finalizado");

  delay(1000);

  Serial.println("Iniciando passos de todos os encoders");
  //Simulando PWM para enc1, enc2, enc3 em conjunto
  for (int i = 0; i <= 100; i++) {
    digitalWrite(enc1, HIGH);
    digitalWrite(enc2, HIGH);
    digitalWrite(enc3, HIGH);
    delayMicroseconds(delaySinalAtivo);
    digitalWrite(enc1, LOW);
    digitalWrite(enc2, LOW);
    digitalWrite(enc3, LOW);
    delayMicroseconds(delaySinalDesativado);
  }

  Serial.println("Passos de todos os encoders finalizados");

  delay(5000); // esperando 5 segundos entre os envios de sinais
  
}
