/**
 * Arduino Crawlspace Inspection Robot - Main Code
 * 
 * Hardware:
 * - Arduino Uno
 * - L298N Motor Driver (Tank Treads)
 * - 2x SG90 Servos (2-DOF Arm)
 * - NRF24L01 Wireless Module
 * - BME688 Sensor (Modulino Thermo)
 * - VL53L4CD Sensor (Modulino Distance)
 * 
 * Libraries Required:
 * - RF24
 * - Adafruit_BME680
 * - Adafruit_VL53L4CD
 * - Servo
 */

#include <SPI.h>
#include <RF24.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>
#include <Adafruit_VL53L4CD.h>
#include "config.h"

// ===== Object Instances =====
RF24 radio(NRF_CE_PIN, NRF_CSN_PIN);
Servo servoBase;
Servo servoArm;
Adafruit_BME680 bme;
Adafruit_VL53L4CD vl53l4cd = Adafruit_VL53L4CD();

// ===== Control Data Structure =====
struct ControlData {
  int leftMotorSpeed;   // -255 to 255
  int rightMotorSpeed;  // -255 to 255
  int servoBaseAngle;   // 0 to 180
  int servoArmAngle;    // 0 to 180
};

ControlData receivedData;

// ===== Timing Variables =====
unsigned long lastDistanceUpdate = 0;
unsigned long lastTempUpdate = 0;

// ===== Sensor Variables =====
int currentDistance = 1000;  // Current distance in mm
bool safetyStop = false;

// ===== Function Prototypes =====
void setupMotors();
void setupServos();
void setupWireless();
void setupSensors();
void updateDistance();
void updateTemperature();
void controlMotors(int leftSpeed, int rightSpeed);
void stopMotors();
void receiveData();
void applySafetyCheck();

void setup() {
  Serial.begin(115200);
  Serial.println(F("Arduino Crawlspace Robot Starting..."));
  
  setupMotors();
  setupServos();
  setupWireless();
  setupSensors();
  
  Serial.println(F("Robot Ready!"));
}

void loop() {
  // Receive control commands
  receiveData();
  
  // Update sensors
  updateDistance();
  updateTemperature();
  
  // Apply safety check
  applySafetyCheck();
  
  // Control actuators if safe
  if (!safetyStop) {
    controlMotors(receivedData.leftMotorSpeed, receivedData.rightMotorSpeed);
    servoBase.write(receivedData.servoBaseAngle);
    servoArm.write(receivedData.servoArmAngle);
  } else {
    stopMotors();
    Serial.println(F("SAFETY STOP: Obstacle detected!"));
  }
}

void setupMotors() {
  pinMode(MOTOR_LEFT_IN1, OUTPUT);
  pinMode(MOTOR_LEFT_IN2, OUTPUT);
  pinMode(MOTOR_LEFT_EN, OUTPUT);
  pinMode(MOTOR_RIGHT_IN3, OUTPUT);
  pinMode(MOTOR_RIGHT_IN4, OUTPUT);
  pinMode(MOTOR_RIGHT_EN, OUTPUT);
  
  stopMotors();
  Serial.println(F("Motors initialized"));
}

void setupServos() {
  servoBase.attach(SERVO_BASE_PIN);
  servoArm.attach(SERVO_ARM_PIN);
  
  // Set to neutral position
  servoBase.write(90);
  servoArm.write(90);
  
  Serial.println(F("Servos initialized"));
}

void setupWireless() {
  if (!radio.begin()) {
    Serial.println(F("NRF24L01 radio hardware not responding!"));
    while (1) {} // Hold in infinite loop
  }
  
  radio.openReadingPipe(1, PIPE_ADDRESS);
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(RF_CHANNEL);
  radio.startListening();
  
  Serial.println(F("NRF24L01 initialized"));
}

void setupSensors() {
  // Initialize I2C
  Wire.begin();
  
  // Initialize BME680 (Temperature/Humidity/Pressure/Gas)
  if (!bme.begin()) {
    Serial.println(F("Could not find BME680 sensor!"));
  } else {
    // Set up oversampling and filter initialization
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150); // 320*C for 150 ms
    Serial.println(F("BME680 initialized"));
  }
  
  // Initialize VL53L4CD (Distance Sensor)
  if (!vl53l4cd.begin()) {
    Serial.println(F("Could not find VL53L4CD sensor!"));
  } else {
    if (vl53l4cd.startRanging()) {
      Serial.println(F("VL53L4CD initialized"));
    }
  }
}

void updateDistance() {
  unsigned long currentTime = millis();
  if (currentTime - lastDistanceUpdate >= DISTANCE_UPDATE_INTERVAL) {
    lastDistanceUpdate = currentTime;
    
    if (vl53l4cd.dataReady()) {
      currentDistance = vl53l4cd.distance();
      vl53l4cd.clearInterrupt();
      
      Serial.print(F("Distance: "));
      Serial.print(currentDistance);
      Serial.println(F(" mm"));
    }
  }
}

void updateTemperature() {
  unsigned long currentTime = millis();
  if (currentTime - lastTempUpdate >= TEMP_UPDATE_INTERVAL) {
    lastTempUpdate = currentTime;
    
    if (bme.performReading()) {
      Serial.print(F("Temp: "));
      Serial.print(bme.temperature);
      Serial.print(F(" C, Humidity: "));
      Serial.print(bme.humidity);
      Serial.print(F(" %, Pressure: "));
      Serial.print(bme.pressure / 100.0);
      Serial.println(F(" hPa"));
    }
  }
}

void controlMotors(int leftSpeed, int rightSpeed) {
  // Constrain speeds
  leftSpeed = constrain(leftSpeed, -MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);
  rightSpeed = constrain(rightSpeed, -MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);
  
  // Left Motor
  if (leftSpeed > 0) {
    digitalWrite(MOTOR_LEFT_IN1, HIGH);
    digitalWrite(MOTOR_LEFT_IN2, LOW);
    analogWrite(MOTOR_LEFT_EN, abs(leftSpeed));
  } else if (leftSpeed < 0) {
    digitalWrite(MOTOR_LEFT_IN1, LOW);
    digitalWrite(MOTOR_LEFT_IN2, HIGH);
    analogWrite(MOTOR_LEFT_EN, abs(leftSpeed));
  } else {
    digitalWrite(MOTOR_LEFT_IN1, LOW);
    digitalWrite(MOTOR_LEFT_IN2, LOW);
    analogWrite(MOTOR_LEFT_EN, 0);
  }
  
  // Right Motor
  if (rightSpeed > 0) {
    digitalWrite(MOTOR_RIGHT_IN3, HIGH);
    digitalWrite(MOTOR_RIGHT_IN4, LOW);
    analogWrite(MOTOR_RIGHT_EN, abs(rightSpeed));
  } else if (rightSpeed < 0) {
    digitalWrite(MOTOR_RIGHT_IN3, LOW);
    digitalWrite(MOTOR_RIGHT_IN4, HIGH);
    analogWrite(MOTOR_RIGHT_EN, abs(rightSpeed));
  } else {
    digitalWrite(MOTOR_RIGHT_IN3, LOW);
    digitalWrite(MOTOR_RIGHT_IN4, LOW);
    analogWrite(MOTOR_RIGHT_EN, 0);
  }
}

void stopMotors() {
  digitalWrite(MOTOR_LEFT_IN1, LOW);
  digitalWrite(MOTOR_LEFT_IN2, LOW);
  analogWrite(MOTOR_LEFT_EN, 0);
  digitalWrite(MOTOR_RIGHT_IN3, LOW);
  digitalWrite(MOTOR_RIGHT_IN4, LOW);
  analogWrite(MOTOR_RIGHT_EN, 0);
}

void receiveData() {
  if (radio.available()) {
    radio.read(&receivedData, sizeof(ControlData));
    
    // Debug output
    Serial.print(F("Received - L:"));
    Serial.print(receivedData.leftMotorSpeed);
    Serial.print(F(" R:"));
    Serial.print(receivedData.rightMotorSpeed);
    Serial.print(F(" Base:"));
    Serial.print(receivedData.servoBaseAngle);
    Serial.print(F(" Arm:"));
    Serial.println(receivedData.servoArmAngle);
  }
}

void applySafetyCheck() {
  // Safety feature: stop if distance < 150mm
  if (currentDistance < SAFETY_DISTANCE_MM && currentDistance > 0) {
    safetyStop = true;
  } else {
    safetyStop = false;
  }
}
