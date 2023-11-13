const int relayPin = 2; // Pino do relé
int computerON = 1; // Inicialmente, o computador está ligado
unsigned long relayActivationTime =  8 * 3600; // 10 horas em segundos

unsigned long secondsCounter = 0; // Variável para contar os segundos

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
  pinMode(relayPin, OUTPUT); // Define o pino do relé como saída
  digitalWrite(relayPin, HIGH); // Desliga o relé inicialmente
   pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    int computerStatus = Serial.parseInt(); // Lê o valor de computerON
    char receivedChar = Serial.read();
    Serial.print("Caractere recebido: ");
    Serial.println(receivedChar);
    
    if (computerStatus == 0) {
      computerON = 0;
      secondsCounter = 0;
      digitalWrite(LED_BUILTIN, HIGH);
    } else if (computerStatus == 1) {
      computerON = 1;
      secondsCounter = 0;
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
  
  if (computerON == 0 && (secondsCounter >= relayActivationTime)) {
    digitalWrite(relayPin, LOW); // Liga o relé para ligar o computador
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
    secondsCounter = 0;
    computerON = 1;
  } else {
    digitalWrite(relayPin, HIGH); // Desliga o relé
   
  }
  
  // Incrementa a contagem dos segundos a cada ciclo do loop
  delay(1000); // Espera 1 segundo
  if(computerON == 0){
    secondsCounter++;
    
  Serial.println(secondsCounter);
  }
  
}
