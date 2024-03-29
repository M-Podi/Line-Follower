#include <QTRSensors.h>

// Motor control pin definitions
const int m11Pin = 7;
const int m12Pin = 6;
const int m21Pin = 5;
const int m22Pin = 4;
const int m1Enable = 11;
const int m2Enable = 10;

// Initial motor speeds
int m1Speed = 0;
int m2Speed = 0;

// PID control parameters
float kp = 12.5;  // Proportional gain
float ki = 0;     // Integral gain
float kd = 5.5;   // Derivative gain
int p = 1;        // Proportional error
int i = 0;        // Integral error
int d = 0;        // Derivative error

// Error values for PID control
int error = 0;
int lastError = 0;

// Speed constants
const int maxSpeed = 255;
const int minSpeed = -255;
const int baseSpeed = 255;

// Calibration parameters
unsigned int calibrationTime = 600;
unsigned long lastCalibrationTime = 0;

// Sensor setup
QTRSensors qtr;
const int sensorCount = 6;
int sensorValues[sensorCount];
int sensors[sensorCount] = { 0, 0, 0, 0, 0, 0 };

// Calibration function for sensors
void calibration() {
  if (millis() - lastCalibrationTime > calibrationTime) {
    int aux = m1Speed;
    m1Speed = m2Speed;
    m2Speed = aux;

    m1Speed = constrain(m1Speed, -100, maxSpeed);
    m2Speed = constrain(m2Speed, -100, maxSpeed);
    setMotorSpeed(m1Speed, m2Speed);

    lastCalibrationTime = millis();
  }
}

// Initial setup function
void setup() {
  // Setting pin modes for motor control
  pinMode(m11Pin, OUTPUT);
  pinMode(m12Pin, OUTPUT);
  pinMode(m21Pin, OUTPUT);
  pinMode(m22Pin, OUTPUT);
  pinMode(m1Enable, OUTPUT);
  pinMode(m2Enable, OUTPUT);

  // Sensor type configuration
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){ A0, A1, A2, A3, A4, A5 }, sensorCount);

  delay(500);

  // Indicate calibration mode
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  // Start sensor calibration
  m1Speed = 125;
  m2Speed = -125;
  lastCalibrationTime = millis();
  for (uint16_t i = 0; i < 150; i++) {
    qtr.calibrate();
    calibration();
  }

  // Reset motor speeds after calibration
  m1Speed = 0;
  m2Speed = 0;

  // Exit calibration mode
  digitalWrite(LED_BUILTIN, LOW);

  // Start serial communication
  Serial.begin(9600);
}

// Main control loop
void loop() {
  // Read sensors and calculate error
  error = map(qtr.readLineBlack(sensorValues), 0, 5000, -50, 50);

  // PID error components
  p = error;
  i = i + error;
  d = error - lastError;

  // Compute motor speed based on PID output
  int motorSpeed = kp * p + ki * i + kd * d;
  m1Speed = baseSpeed;
  m2Speed = baseSpeed;

  // Adjust motor speeds based on error direction
  if (error < 0) {
    m1Speed += motorSpeed;
  } else if (error > 0) {
    m2Speed -= motorSpeed;
  }

  // Constrain motor speeds to prevent exceeding limits
  m1Speed = constrain(m1Speed, -100, maxSpeed);
  m2Speed = constrain(m2Speed, -100, maxSpeed);
  setMotorSpeed(m1Speed, m2Speed);
}

// Set the speed of motors
void setMotorSpeed(int motor1Speed, int motor2Speed) {
  // Control motor direction and speed
  if (motor1Speed == 0) {
    digitalWrite(m11Pin, LOW);
    digitalWrite(m12Pin, LOW);
    analogWrite(m1Enable, motor1Speed);
  } else {
    if (motor1Speed > 0) {
      digitalWrite(m11Pin, HIGH);
      digitalWrite(m12Pin, LOW);
      analogWrite(m1Enable, motor1Speed);
    }
    if (motor1Speed < 0) {
      digitalWrite(m11Pin, LOW);
      digitalWrite(m12Pin, HIGH);
      analogWrite(m1Enable, -motor1Speed);
    }
  }
  if (motor2Speed == 0) {
    digitalWrite(m21Pin, LOW);
    digitalWrite(m22Pin, LOW);
    analogWrite(m2Enable, motor2Speed);
  } else {
    if (motor2Speed > 0) {
      digitalWrite(m21Pin, HIGH);
      digitalWrite(m22Pin, LOW);
      analogWrite(m2Enable, motor2Speed);
    }
    if (motor2Speed < 0) {
      digitalWrite(m21Pin, LOW);
      digitalWrite(m22Pin, HIGH);
      analogWrite(m2Enable, -motor2Speed);
    }
  }
}
