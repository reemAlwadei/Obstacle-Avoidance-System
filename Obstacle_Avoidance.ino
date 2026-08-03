#include <Servo.h>

// First L293D
const int motor1A = 2;
const int motor1B = 3;
const int motor2A = 4;
const int motor2B = 5;

// Second L293D
const int motor3A = 6;
const int motor3B = 7;
const int motor4A = 8;
const int motor4B = 9;

// Servo and ultrasonic sensor
const int servoPin = 10;
const int ultrasonicPin = 11;

Servo scannerServo;

void setup() {
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);

  pinMode(motor3A, OUTPUT);
  pinMode(motor3B, OUTPUT);
  pinMode(motor4A, OUTPUT);
  pinMode(motor4B, OUTPUT);

  scannerServo.attach(servoPin);
  scannerServo.write(90);

  Serial.begin(9600);

  stopMotors();
  delay(1000);
}

void loop() {
  long distance = readDistanceCM();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 10 || distance == 0) {
    moveForward();
  } else {
    avoidObstacle();
  }

  delay(100);
}

long readDistanceCM() {
  pinMode(ultrasonicPin, OUTPUT);

  digitalWrite(ultrasonicPin, LOW);
  delayMicroseconds(2);

  digitalWrite(ultrasonicPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(ultrasonicPin, LOW);

  pinMode(ultrasonicPin, INPUT);

  long duration = pulseIn(ultrasonicPin, HIGH, 30000);

  if (duration == 0) {
    return 0;
  }

  return duration * 0.034 / 2;
}

void avoidObstacle() {
  stopMotors();
  delay(500);

  // Scan one side
  scannerServo.write(30);
  delay(700);

  // Scan the other side
  scannerServo.write(150);
  delay(700);

  // Return servo to the center
  scannerServo.write(90);
  delay(500);

  // Move backward
  moveBackward();
  delay(1000);

  // Change direction
  turnRight();
  delay(1000);

  stopMotors();
  delay(300);
}

void moveForward() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);

  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);

  digitalWrite(motor3A, HIGH);
  digitalWrite(motor3B, LOW);

  digitalWrite(motor4A, LOW);
  digitalWrite(motor4B, HIGH);
}

void moveBackward() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);

  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);

  digitalWrite(motor3A, LOW);
  digitalWrite(motor3B, HIGH);

  digitalWrite(motor4A, HIGH);
  digitalWrite(motor4B, LOW);
}

void turnRight() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);

  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);

  digitalWrite(motor3A, HIGH);
  digitalWrite(motor3B, LOW);

  digitalWrite(motor4A, HIGH);
  digitalWrite(motor4B, LOW);
}

void stopMotors() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);

  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);

  digitalWrite(motor3A, LOW);
  digitalWrite(motor3B, LOW);

  digitalWrite(motor4A, LOW);
  digitalWrite(motor4B, LOW);
}
