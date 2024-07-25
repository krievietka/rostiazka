const int trigPin = 3;
const int echoPin = 2;
const int buzzerPin = 4;

const int numReadings = 3;
long readings[numReadings];
int readIndex = 0;
long total = 0;
long average = 0;
int measurementCount = 0; // счетчик измерений

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // инициализация массива значений
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  delay(5000);
}

void loop() {
  // Вычисление расстояния с ультразвукового датчика
  long duration;
  int distance;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
  // вычитание старого значения и добавление нового
  total = total - readings[readIndex];
  readings[readIndex] = distance;
  total = total + readings[readIndex];
  
  readIndex = readIndex + 1;
  
  // если массив значений заполнен, начать с начала
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  
  // расчет среднего значения
  average = total / numReadings;
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm, Average: ");
  Serial.print(average);
  Serial.println(" cm");

  // увеличиваем счетчик измерений
  measurementCount++;
  
  // проверка на изменение среднего значения после первых 100 измерений
  if (measurementCount > 100) {
    if (abs(distance - average) >= 20) {
      digitalWrite(buzzerPin, HIGH);
    } else {
      digitalWrite(buzzerPin, LOW);
    }
  } else {
    digitalWrite(buzzerPin, LOW);
  }
  
  delay(100); // задержка между измерениями
}
