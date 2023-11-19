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
int maxDist = 400;

void setup() {
  Serial.begin (9600);
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
  distance1 = newMeasurement(trigPin1, echoPin1);
  distance2 = newMeasurement(trigPin2, echoPin2);

  if (distance1 != 0 && distance2 != 0){
    Serial.println(distance1);
    Serial.println(distance2);
    Serial.println();
  }
  
  if (distance1 < 10 || distance2 < 10) { 
    digitalWrite(ledPinRed, HIGH);
    tone(buzzerPin, 500);
    if (distance1 < 20 || distance2 < 20 ) {
      digitalWrite(ledPinYell, HIGH);
      tone(buzzerPin, 400);
      if (distance1 < 30 || distance2 < 30) {
        digitalWrite(ledPinGreen, HIGH);
      }
    }
  }

  delay(200);
}

int newMeasurement(int trigPin, int echoPin){
  // send out ultrasonic wave 
  digitalWrite(trigPin, LOW);
  delay(5);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  int distance = (duration / 2) * 0.03432;
  
  if (distance <= 0 || distance > maxDist ){
    return 0;
  }
  else{
    return distance;
  }  
} 