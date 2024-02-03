//Name : Prabhjot Singh
// Roll No. : 2210994884


// Constants for the pins
const int trigPin = 9; // Trigger pin for the ultrasonic sensor
const int echoPin = 10; // Echo pin for thetrasonic sensorconst int newLedPin = 1; // Pin for the new LED
const int pirPin = 2; // Pin for the PIR motion sensor
const int ledPin = 13; // Pin for the built-in LED

// Variables for storing the duration and distance
long duration;
float distance;

void setup() {
  // Set the pins as output or input
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(newLedPin, OUTPUT);
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // Start the serial communication
  Serial.begin(9600);

  // Attach the motionDetectedISR function to the pirPin interrupt
  attachInterrupt(digitalPinToInterrupt(pirPin), motionDetectedISR, CHANGE);
}

void loop() {
  // Send a short pulse on the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the pulse on the echo pin
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  distance = (duration / 2) / 29.1;

  // Check if the distance is less than 100 cm
  if (distance < 100) {
    // Turn on the new LED if the distance is less than 100 cm
    digitalWrite(newLedPin, HIGH);
  } else {
    // Turn off the new LED if the distance is greater than or equal to 100 cm
    digitalWrite(newLedPin, LOW);
  }

  // Delay for 100 milliseconds
  delay(100);
}

// Interrupt service routine for the pirPin interrupt
void motionDetectedISR() {
  // Check if motion is detected
  if (digitalRead(pirPin) == HIGH) {
    // Print a message to the serial monitor
    Serial.println("Motion Detected!");

    // Turn on the built-in LED if motion is detected
    digitalWrite(ledPin, HIGH);
  } else {
    // Print a message to the serial monitor
    Serial.println("Motion Ended!");

    // Turn off the built-in LED if motion ends
    digitalWrite(ledPin, LOW);
  }
}
