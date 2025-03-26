// Definição dos pinos
const int sensorNivelMinimo = 2;    // Pino do sensor de nível mínimo (usaremos um sensor de contato simples)
const int sensorNivelMaximo = 3;    // Pino do sensor de nível máximo
const int bomba = 4;                // Pino que controla a bomba (usaremos um relé)

// Variáveis de estado
bool nivelMinimoAlcancado = false;
bool nivelMaximoAlcancado = false;

void setup() {
  // Inicialização dos pinos
  pinMode(sensorNivelMinimo, INPUT_PULLUP);  // Sensor como entrada com resistor pull-up interno
  pinMode(sensorNivelMaximo, INPUT_PULLUP);  // Sensor como entrada com resistor pull-up interno
  pinMode(bomba, OUTPUT);                   // Bomba como saída
  
  // Inicialmente a bomba está desligada
  digitalWrite(bomba, LOW);
  
  // Inicializa a comunicação serial para monitoramento (opcional)
  Serial.begin(9600);
  Serial.println("Sistema de controle de armazenamento de água iniciado");
}

void loop() {
  // Lê o estado dos sensores (LOW significa que o sensor está ativado - água detectada)
  nivelMinimoAlcancado = (digitalRead(sensorNivelMinimo) == LOW);
  nivelMaximoAlcancado = (digitalRead(sensorNivelMaximo) == LOW);
  
  // Lógica de controle da bomba
  if (nivelMaximoAlcancado) {
    // Desliga a bomba se o nível máximo foi atingido
    digitalWrite(bomba, LOW);
    Serial.println("Nível máximo atingido - Bomba DESLIGADA");
  } else if (!nivelMinimoAlcancado) {
    // Liga a bomba se o nível está abaixo do mínimo
    digitalWrite(bomba, HIGH);
    Serial.println("Nível abaixo do mínimo - Bomba LIGADA");
  } else {
    // Mantém o estado atual (nível entre mínimo e máximo)
    Serial.println("Nível adequado - Mantendo estado atual");
  }
  
  // Pequeno atraso para evitar leituras muito rápidas
  delay(500);
}
