#define ENA 11
#define IN1 9
#define IN2 8
#define IN3 7
#define IN4 6
#define ENB 5
#define SERVO_PIN 10
#define SERVO1_PIN 2
#define ir_R A0
#define ir_L A2
#define ir_F A1
#define PUMP_PIN A5
#define TRIG_PIN A3
#define ECHO_PIN A4
#define BUZZER_PIN 12
#define MAX_DISTANCE 400

#include <NewPing.h>
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

#include <Servo.h>

void measureDistance() {
  unsigned int distance = sonar.ping_cm();
  if (distance > 0 && distance <= MAX_DISTANCE) {
    Serial.println(distance);
  } else {
    Serial.println("Out of range");
  }
}

int s1, s2, s3;
Servo steeringServo;
int lastSteeringAngle = 90;

Servo servo1;
int lastServo1Angle = 90;


bool isAutoMode = true;


void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);
  
  pinMode(ir_R, INPUT);
  pinMode(ir_F, INPUT);
  pinMode(ir_L, INPUT);
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  steeringServo.attach(SERVO_PIN);
  servo1.attach(SERVO1_PIN);
  
 
  
  steeringServo.write(90);
  servo1.write(90);
  
  
  
  Serial.begin(9600);
}


void handleMotorCommands(char command) {
  switch(command) {
    case 'F':
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      analogWrite(ENA, 85);
      analogWrite(ENB, 85);
      break;
      
    case 'B':
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      analogWrite(ENA, 150);
      analogWrite(ENB, 150);
      break;
      
    case 'C':
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      analogWrite(ENA, 255);
      analogWrite(ENB, 255);
      break;
      
    case 'D':
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      analogWrite(ENA, 85);
      analogWrite(ENB, 85);
      break;
      
    case 'E':
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      analogWrite(ENA, 150);
      analogWrite(ENB, 150);
      break;
      
    case 'G':
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      analogWrite(ENA, 150);
      analogWrite(ENB, 150);
      break;
      
    case 'S':
    default:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      analogWrite(ENA, 0);
      analogWrite(ENB, 0);
      break;
  }
}

void handleSteeringServoCommands(char command) {
  int steeringAngle;
  
  switch(command) {
    case 'H':steeringAngle = 0;break;
    case 'I':steeringAngle = 30;break;
    case 'J':steeringAngle = 60;break;
    case 'K':steeringAngle = 90;break;
    case 'L':steeringAngle = 120;break;
    case 'M':steeringAngle = 150;break;
    case 'N':steeringAngle = 180;break;
    default:return;
  }
  steeringServo.write(steeringAngle);
  lastSteeringAngle = steeringAngle;
}

void handleServo1Commands(char command) {
  int servo1Angle;
  
  switch(command) {
    case 'Q':servo1Angle = 0;break;
    case 'R':servo1Angle = 30;break;
    case 'T':servo1Angle = 60;break;
    case 'U':servo1Angle = 90;break;
    case 'V':servo1Angle = 120;break;
    case 'W':servo1Angle = 150;break;
    case 'X':servo1Angle = 180;break;
    default:return;
  }
  servo1.write(servo1Angle);
  lastServo1Angle = servo1Angle;
}

void go_forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 180);
  analogWrite(ENB, 180);
}

void freeze() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void controlWaterPump_on() {
  digitalWrite(PUMP_PIN, 1);
}

void controlWaterPump_off() {
  digitalWrite(PUMP_PIN, 0);
}


void Buzzer_ON() {
  digitalWrite(BUZZER_PIN, HIGH);
}
void Buzzer_OFF() {
  digitalWrite(BUZZER_PIN, LOW);
}



void autoControl() {
  int rightValue = analogRead(ir_R);
  int frontValue = analogRead(ir_F);
  int leftValue = analogRead(ir_L);
  
  const int FIRE_THRESHOLD = 800;
  
  if (frontValue < FIRE_THRESHOLD || rightValue < FIRE_THRESHOLD || leftValue < FIRE_THRESHOLD) {
    if (frontValue < FIRE_THRESHOLD) {
      steeringServo.write(90);
      go_forward();
      if (frontValue < (FIRE_THRESHOLD - 300)) {
        steeringServo.write(90);
        freeze();
        controlWaterPump_on();
        sweepServo();
      }
    }
    else if (rightValue < FIRE_THRESHOLD) {
      steeringServo.write(30);
      go_forward();
      if (rightValue < (FIRE_THRESHOLD - 300)) {
        steeringServo.write(90);
        freeze();
        controlWaterPump_on();
        sweepServo();
      }
    }
    else if (leftValue < FIRE_THRESHOLD) {
      steeringServo.write(150);
      go_forward();
      if (leftValue < (FIRE_THRESHOLD - 300)) {
        steeringServo.write(90);
        freeze();
        controlWaterPump_on();
        sweepServo();
      }
    }
  }
  else {
    freeze();
    controlWaterPump_off();
    steeringServo.write(90);
  }
  
  delay(100);
}

void sweepServo() {
  for (int i = 90; i >= 30; i -= 1) {
    servo1.write(i);
    delay(50);
  }
  for (int i = 30; i <= 150; i += 1) {
    servo1.write(i);
    delay(50);
  }
  for (int i = 150; i >= 90; i -= 1) {
    servo1.write(i);
    delay(50);
  }
}

void loop() {
  
  
  if (Serial.available() > 0) {
    char command = Serial.read();
    
    // Toggle between manual and auto mode using '*'
    if (command == '*') {
      isAutoMode = !isAutoMode;
      handleMotorCommands('S');
      controlWaterPump_off();
      return;
    }
    
    
    // Handle manual mode commands
    if (!isAutoMode) {
      if (command == 'F' || command == 'B' || command == 'C' || 
          command == 'D' || command == 'E' || command == 'G' || command == 'S') {
        handleMotorCommands(command);
      }
      else if (command >= 'H' && command <= 'N') {
        handleSteeringServoCommands(command);
      }
      else if (command >= 'Q' && command <= 'X') {
        handleServo1Commands(command);
      }
      // manual water pump controls
      else if (command == 'A') {
        controlWaterPump_on();
      }
      else if (command == 'Z') {
        controlWaterPump_off();
      }
      else if (command == 'Y') {
        measureDistance();
      }
      else if (command == '(') {
        Buzzer_ON();
      }
      else if (command == ')') {
        Buzzer_OFF();
      }      
    }
  }

  
  // Run auto mode if enabled
  if (isAutoMode) {
    autoControl();
  }
}
