int trigPin1 = 12;
int echoPin1 = 10;
int trigPin2 = 13;
int echoPin2 = 11;

int ledPinRed = 2;
int ledPinYell = 3;
int ledPinGreen = 4;
int buzzerPin = 5;

int distance1 = 0;
int distance2 = 0;
int lowestDistance = 0;
int maxDist = 1000;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);

  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinYell, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  delay(100);
  Serial.println("ert");
  distance1 = newMeasurement(trigPin1, echoPin1);
  distance2 = newMeasurement(trigPin2, echoPin2);

  digitalWrite(ledPinRed, LOW);
  digitalWrite(ledPinYell, LOW);
  digitalWrite(ledPinGreen, LOW);
  noTone(buzzerPin);


  if (distance1 != 0 && distance2 != 0) {
    Serial.println(distance1);
    Serial.println(distance2);
    Serial.println();

    // simplify LED control system
    if (distance2 < distance1) {
      lowestDistance = distance2;
    } else {
      lowestDistance = distance1;
    }
  }

  if (lowestDistance >= 60) {
    digitalWrite(ledPinGreen, HIGH);
  }
  if ((lowestDistance < 40) && (lowestDistance >= 10)) {
    digitalWrite(ledPinYell, HIGH);
    tone(buzzerPin, 2000);
  }
  if (lowestDistance < 20) {
    digitalWrite(ledPinRed, HIGH);
    tone(buzzerPin, 500);
  } 
}

int newMeasurement(int trigPin, int echoPin) {
  // send out ultrasonic wave
  digitalWrite(trigPin, LOW);
  delay(5);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);

  // calculate distance in cm
  long duration = pulseIn(echoPin, HIGH);
  int distance = (duration / 2) * 0.03432;

  return distance;
}