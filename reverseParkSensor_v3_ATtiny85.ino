int buttonPin = 0; //Physical 5
int led2Pin = 1; //Physical 6
int ledPin = 2; //Physical 7
const int trigPin = 3; //Physical 2
const int echoPin = 4; //Physical 3

long duration;
unsigned long distance;
int stillCounter = 0;
int buttonState = 0;

volatile int stopDistance = 10; // the default ideal partking distance in cm
int blinkRate = 4; // the speed of the blink
int stillTurnOffAfter = 2000; // time in (approx) ms before turning LED off after car is parked
int distanceMultiplier = 4; // the stopDistance * this value sets the range of the sensor before it blinks

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(buttonPin, INPUT);

  // Turn the LEDs off to start with
  digitalWrite(ledPin, LOW);
  digitalWrite(led2Pin, LOW);
}

void loop() {
  // GET DISTANCE
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  distance = pulseIn(echoPin, HIGH) * 0.034 / 2; // Calculating the distance in cm

  // IF WE ARE IN THE STOP ZONE
  if (distance <= stopDistance) {
    stillCounter++;
    if (stillCounter > stillTurnOffAfter) {
      stillCounter = stillTurnOffAfter + 1; // keeps the counter high, avoids overflow
      digitalWrite(ledPin, LOW);
    } else {
      digitalWrite(ledPin, HIGH);
    }
    
  // ELSE, BLINK IF WE ARE IN RANGE
  } else if (distance > stopDistance && distance <= stopDistance * distanceMultiplier) {
    stillCounter = 0;
    digitalWrite(ledPin, HIGH);
    delay(distance * blinkRate);
    digitalWrite(ledPin, LOW);
    delay(distance * blinkRate);
    
  // ELSE, WE ARE TOO FAR AWAY
  } else if (distance > stopDistance * distanceMultiplier) {
    digitalWrite(ledPin, LOW);
  }

  // SET DESIRED DISTANCE IF BUTTON IS PRESSED
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    //digitalWrite(ledPin, HIGH);
    digitalWrite(led2Pin, HIGH);
    delay(1500);
    stopDistance = distance;
    delay(1500);
    //digitalWrite(ledPin, LOW);
    digitalWrite(led2Pin, LOW);
  }
}
