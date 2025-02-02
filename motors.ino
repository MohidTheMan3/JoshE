#include <Servo.h>

// Motor Driver 1 (Motors 1 and 2)
const int IN1_1 = 9;  // IN1 for Motor 1
const int IN2_1 = 10; // IN2 for Motor 1
const int ENA_1 = 3;  // ENA for Motor 1 

const int IN3_1 = 11; // IN3 for Motor 2
const int IN4_1 = 12; // IN4 for Motor 2
const int ENB_1 = 5;  // ENB for Motor 2 

// Motor Driver 2 (Motors 3 and 4)
const int IN1_2 = 6;  // IN1 for Motor 3
const int IN2_2 = 7;  // IN2 for Motor 3
const int ENA_2 = 8;  // ENA for Motor 3

const int IN3_2 = 4;  // IN3 for Motor 4
const int IN4_2 = 2;  // IN4 for Motor 4
const int ENB_2 = A0; // ENB for Motor 4 

Servo servo1, servo2, servo3, servo4;
const int servo1Pin = A5; // Servo 1 control pin
const int servo2Pin = A2; // Servo 2 control pin
const int servo3Pin = A3; // Servo 3 control pin
const int servo4Pin = A4; // Servo 4 control pin

const int rightSpeed = 220;

void setup() {
  pinMode(IN1_1, OUTPUT);
  pinMode(IN2_1, OUTPUT);
  pinMode(ENA_1, OUTPUT);

  pinMode(IN3_1, OUTPUT);
  pinMode(IN4_1, OUTPUT);
  pinMode(ENB_1, OUTPUT);

  pinMode(IN1_2, OUTPUT);
  pinMode(IN2_2, OUTPUT);
  pinMode(ENA_2, OUTPUT);

  pinMode(IN3_2, OUTPUT);
  pinMode(IN4_2, OUTPUT);
  pinMode(ENB_2, OUTPUT);

  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);
  servo4.attach(servo4Pin);

  // Initialize servos to neutral position
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(150);
  // Stop all motors initially
  stopMotors();

  Serial.begin(9600); 

  
}

void loop() {

  if (Serial.available() > 0) { // Check if data is available to read
       String receivedMessage = Serial.readStringUntil('\n'); // Read the incoming message
        Serial.println(receivedMessage);
        
        float parsedMessage = receivedMessage.toFloat();
        if(parsedMessage >= 0.43){
          Serial.println("Moved forward\n"); // Respond

          moveForward();
          delay(300);
          stopMotors();
          
        }
        

        
    }
}

void moveForward() {
  // All motors move forward
  digitalWrite(IN1_1, LOW);
  digitalWrite(IN2_1, HIGH);
  analogWrite(ENA_1, rightSpeed); // Speed for Motor 1

  digitalWrite(IN3_1, LOW);
  digitalWrite(IN4_1, HIGH);
  analogWrite(ENB_1, rightSpeed); // Speed for Motor 2

  digitalWrite(IN1_2, HIGH);
  digitalWrite(IN2_2, LOW);
  analogWrite(ENA_2, 255); // Speed for Motor 3

  digitalWrite(IN3_2, HIGH);
  digitalWrite(IN4_2, LOW);
  analogWrite(ENB_2, 255); // Speed for Motor 4
}

void moveBackward() {
  // All motors move backward
  digitalWrite(IN1_1, HIGH);
  digitalWrite(IN2_1, LOW);
  analogWrite(ENA_1, rightSpeed); // Speed for Motor 1

  digitalWrite(IN3_1, HIGH);
  digitalWrite(IN4_1, LOW);
  analogWrite(ENB_1, rightSpeed); // Speed for Motor 2

  digitalWrite(IN1_2, LOW);
  digitalWrite(IN2_2, HIGH);
  analogWrite(ENA_2, 255); // Speed for Motor 3

  digitalWrite(IN3_2, LOW);
  digitalWrite(IN4_2, HIGH);
  analogWrite(ENB_2, 255); // Speed for Motor 4
}

void turnLeftInPlace() {
  // Left motors move forward, right motors move backward
  digitalWrite(IN1_1, HIGH);
  digitalWrite(IN2_1, LOW);
  analogWrite(ENA_1, rightSpeed); // Speed for Motor 1

  digitalWrite(IN3_1, HIGH);
  digitalWrite(IN4_1, LOW);
  analogWrite(ENB_1, rightSpeed); // Speed for Motor 2

  digitalWrite(IN1_2, HIGH);
  digitalWrite(IN2_2, LOW);
  analogWrite(ENA_2, 255); // Speed for Motor 3

  digitalWrite(IN3_2, HIGH);
  digitalWrite(IN4_2, LOW);
  analogWrite(ENB_2, 255); // Speed for Motor 4
}

void turnRightInPlace() {
   // Left motors move forward, right motors move backward
  digitalWrite(IN1_1, LOW);
  digitalWrite(IN2_1, HIGH);
  analogWrite(ENA_1, rightSpeed); // Speed for Motor 1

  digitalWrite(IN3_1, LOW);
  digitalWrite(IN4_1, HIGH);
  analogWrite(ENB_1, rightSpeed); // Speed for Motor 2

  digitalWrite(IN1_2, LOW);
  digitalWrite(IN2_2, HIGH);
  analogWrite(ENA_2, 255); // Speed for Motor 3

  digitalWrite(IN3_2, LOW);
  digitalWrite(IN4_2, HIGH);
  analogWrite(ENB_2, 255); // Speed for Motor 4
}

void turnLeftForward() {
  // Left motors move forward at full speed, right motors move forward at reduced speed
  digitalWrite(IN1_1, LOW);
  digitalWrite(IN2_1, HIGH);
  analogWrite(ENA_1, 255); // Full speed for Motor 1

  digitalWrite(IN3_1, LOW);
  digitalWrite(IN4_1, HIGH);
  analogWrite(ENB_1, 255); // Full speed for Motor 2

  digitalWrite(IN1_2, HIGH);
  digitalWrite(IN2_2, LOW);
  analogWrite(ENA_2, 160); // Reduced speed for Motor 3

  digitalWrite(IN3_2, HIGH);
  digitalWrite(IN4_2, LOW);
  analogWrite(ENB_2, 160); // Reduced speed for Motor 4
}

void turnRightForward() {
  // Right motors move forward at full speed, left motors move forward at reduced speed
  digitalWrite(IN1_1, LOW);
  digitalWrite(IN2_1, HIGH);
  analogWrite(ENA_1, rightSpeed/2); // Reduced speed for Motor 1

  digitalWrite(IN3_1, LOW);
  digitalWrite(IN4_1, HIGH);
  analogWrite(ENB_1, rightSpeed/2); // Reduced speed for Motor 2

  digitalWrite(IN1_2, HIGH);
  digitalWrite(IN2_2, LOW);
  analogWrite(ENA_2, 255); // Full speed for Motor 3

  digitalWrite(IN3_2, HIGH);
  digitalWrite(IN4_2, LOW);
  analogWrite(ENB_2, 255); // Full speed for Motor 4
}


void stopMotors() {
  // Stop Motors on Driver 1
  digitalWrite(IN1_1, LOW);
  digitalWrite(IN2_1, LOW);
  digitalWrite(IN3_1, LOW);
  digitalWrite(IN4_1, LOW);
  analogWrite(ENA_1, 0);
  analogWrite(ENB_1, 0);

  // Stop Motors on Driver 2
  digitalWrite(IN1_2, LOW);
  digitalWrite(IN2_2, LOW);
  digitalWrite(IN3_2, LOW);
  digitalWrite(IN4_2, LOW);
  analogWrite(ENA_2, 0);
  analogWrite(ENB_2, 0);
}
