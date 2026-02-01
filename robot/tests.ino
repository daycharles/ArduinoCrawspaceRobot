/**
 * Basic Unit Tests for Arduino Crawlspace Robot
 * 
 * These tests should be run individually to verify each subsystem
 * Uncomment the test you want to run
 */

// Uncomment ONE test at a time
// #define TEST_MOTORS
// #define TEST_SERVOS
// #define TEST_DISTANCE_SENSOR
// #define TEST_ENV_SENSOR
// #define TEST_NRF24
#define TEST_ALL_INIT  // Test initialization of all systems

#include <SPI.h>
#include <RF24.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>
#include <Adafruit_VL53L4CD.h>
#include "../config.h"

RF24 radio(NRF_CE_PIN, NRF_CSN_PIN);
Servo servoBase;
Servo servoArm;
Adafruit_BME680 bme;
Adafruit_VL53L4CD vl53l4cd = Adafruit_VL53L4CD();

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println(F("===== Arduino Crawlspace Robot Tests ====="));
  
#ifdef TEST_MOTORS
  testMotors();
#endif

#ifdef TEST_SERVOS
  testServos();
#endif

#ifdef TEST_DISTANCE_SENSOR
  testDistanceSensor();
#endif

#ifdef TEST_ENV_SENSOR
  testEnvironmentalSensor();
#endif

#ifdef TEST_NRF24
  testNRF24();
#endif

#ifdef TEST_ALL_INIT
  testAllInitialization();
#endif
}

void loop() {
  // Tests run once in setup
  delay(1000);
}

// ===== Motor Test =====
void testMotors() {
  Serial.println(F("\n--- Motor Test ---"));
  
  // Initialize motor pins
  pinMode(MOTOR_LEFT_IN1, OUTPUT);
  pinMode(MOTOR_LEFT_IN2, OUTPUT);
  pinMode(MOTOR_LEFT_EN, OUTPUT);
  pinMode(MOTOR_RIGHT_IN3, OUTPUT);
  pinMode(MOTOR_RIGHT_IN4, OUTPUT);
  pinMode(MOTOR_RIGHT_EN, OUTPUT);
  
  Serial.println(F("Motors initialized"));
  
  // Test left motor forward
  Serial.println(F("Left motor forward (2s)"));
  digitalWrite(MOTOR_LEFT_IN1, HIGH);
  digitalWrite(MOTOR_LEFT_IN2, LOW);
  analogWrite(MOTOR_LEFT_EN, 150);
  delay(2000);
  
  // Stop
  analogWrite(MOTOR_LEFT_EN, 0);
  delay(500);
  
  // Test left motor reverse
  Serial.println(F("Left motor reverse (2s)"));
  digitalWrite(MOTOR_LEFT_IN1, LOW);
  digitalWrite(MOTOR_LEFT_IN2, HIGH);
  analogWrite(MOTOR_LEFT_EN, 150);
  delay(2000);
  
  // Stop
  analogWrite(MOTOR_LEFT_EN, 0);
  delay(500);
  
  // Test right motor forward
  Serial.println(F("Right motor forward (2s)"));
  digitalWrite(MOTOR_RIGHT_IN3, HIGH);
  digitalWrite(MOTOR_RIGHT_IN4, LOW);
  analogWrite(MOTOR_RIGHT_EN, 150);
  delay(2000);
  
  // Stop
  analogWrite(MOTOR_RIGHT_EN, 0);
  delay(500);
  
  // Test right motor reverse
  Serial.println(F("Right motor reverse (2s)"));
  digitalWrite(MOTOR_RIGHT_IN3, LOW);
  digitalWrite(MOTOR_RIGHT_IN4, HIGH);
  analogWrite(MOTOR_RIGHT_EN, 150);
  delay(2000);
  
  // Stop all
  analogWrite(MOTOR_LEFT_EN, 0);
  analogWrite(MOTOR_RIGHT_EN, 0);
  Serial.println(F("Motor test complete"));
}

// ===== Servo Test =====
void testServos() {
  Serial.println(F("\n--- Servo Test ---"));
  
  servoBase.attach(SERVO_BASE_PIN);
  servoArm.attach(SERVO_ARM_PIN);
  
  Serial.println(F("Servos attached"));
  
  // Center position
  Serial.println(F("Center position (90°)"));
  servoBase.write(90);
  servoArm.write(90);
  delay(1000);
  
  // Base servo sweep
  Serial.println(F("Base servo sweep"));
  for (int pos = 0; pos <= 180; pos += 10) {
    servoBase.write(pos);
    delay(100);
  }
  delay(500);
  
  // Arm servo sweep
  Serial.println(F("Arm servo sweep"));
  for (int pos = 0; pos <= 180; pos += 10) {
    servoArm.write(pos);
    delay(100);
  }
  delay(500);
  
  // Return to center
  servoBase.write(90);
  servoArm.write(90);
  Serial.println(F("Servo test complete"));
}

// ===== Distance Sensor Test =====
void testDistanceSensor() {
  Serial.println(F("\n--- Distance Sensor Test ---"));
  
  Wire.begin();
  
  if (!vl53l4cd.begin()) {
    Serial.println(F("ERROR: VL53L4CD not found!"));
    return;
  }
  
  Serial.println(F("VL53L4CD found"));
  
  if (!vl53l4cd.startRanging()) {
    Serial.println(F("ERROR: Could not start ranging"));
    return;
  }
  
  Serial.println(F("Reading distance (10 samples)..."));
  
  for (int i = 0; i < 10; i++) {
    while (!vl53l4cd.dataReady()) {
      delay(10);
    }
    
    int distance = vl53l4cd.distance();
    vl53l4cd.clearInterrupt();
    
    Serial.print(F("Distance "));
    Serial.print(i + 1);
    Serial.print(F(": "));
    Serial.print(distance);
    Serial.println(F(" mm"));
    
    delay(200);
  }
  
  Serial.println(F("Distance sensor test complete"));
}

// ===== Environmental Sensor Test =====
void testEnvironmentalSensor() {
  Serial.println(F("\n--- Environmental Sensor Test ---"));
  
  Wire.begin();
  
  if (!bme.begin()) {
    Serial.println(F("ERROR: BME680 not found!"));
    return;
  }
  
  Serial.println(F("BME680 found"));
  
  // Configure sensor
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150);
  
  Serial.println(F("Reading sensors (5 samples)..."));
  
  for (int i = 0; i < 5; i++) {
    if (!bme.performReading()) {
      Serial.println(F("Failed to read sensor"));
      continue;
    }
    
    Serial.print(F("Sample "));
    Serial.print(i + 1);
    Serial.print(F(": Temp="));
    Serial.print(bme.temperature);
    Serial.print(F("°C, Humidity="));
    Serial.print(bme.humidity);
    Serial.print(F("%, Pressure="));
    Serial.print(bme.pressure / 100.0);
    Serial.println(F(" hPa"));
    
    delay(2000);
  }
  
  Serial.println(F("Environmental sensor test complete"));
}

// ===== NRF24 Test =====
void testNRF24() {
  Serial.println(F("\n--- NRF24L01 Test ---"));
  
  if (!radio.begin()) {
    Serial.println(F("ERROR: NRF24L01 hardware not responding!"));
    Serial.println(F("Check wiring and power (must be 3.3V)"));
    return;
  }
  
  Serial.println(F("NRF24L01 found"));
  
  radio.openReadingPipe(1, PIPE_ADDRESS);
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(RF_CHANNEL);
  radio.startListening();
  
  Serial.println(F("Configuration:"));
  Serial.print(F("  Channel: "));
  Serial.println(RF_CHANNEL);
  Serial.print(F("  Address: 0x"));
  Serial.println((unsigned long)(PIPE_ADDRESS & 0xFFFFFFFF), HEX);
  
  Serial.println(F("NRF24L01 test complete"));
}

// ===== All Systems Initialization Test =====
void testAllInitialization() {
  Serial.println(F("\n--- All Systems Initialization Test ---"));
  
  bool allGood = true;
  
  // Test Motors
  Serial.print(F("Motors... "));
  pinMode(MOTOR_LEFT_IN1, OUTPUT);
  pinMode(MOTOR_LEFT_IN2, OUTPUT);
  pinMode(MOTOR_LEFT_EN, OUTPUT);
  pinMode(MOTOR_RIGHT_IN3, OUTPUT);
  pinMode(MOTOR_RIGHT_IN4, OUTPUT);
  pinMode(MOTOR_RIGHT_EN, OUTPUT);
  Serial.println(F("OK"));
  
  // Test Servos
  Serial.print(F("Servos... "));
  servoBase.attach(SERVO_BASE_PIN);
  servoArm.attach(SERVO_ARM_PIN);
  servoBase.write(90);
  servoArm.write(90);
  Serial.println(F("OK"));
  
  // Test NRF24
  Serial.print(F("NRF24L01... "));
  if (!radio.begin()) {
    Serial.println(F("FAIL"));
    allGood = false;
  } else {
    radio.openReadingPipe(1, PIPE_ADDRESS);
    radio.setPALevel(RF24_PA_LOW);
    radio.setChannel(RF_CHANNEL);
    radio.startListening();
    Serial.println(F("OK"));
  }
  
  // Test I2C
  Wire.begin();
  
  // Test Distance Sensor
  Serial.print(F("VL53L4CD... "));
  if (!vl53l4cd.begin()) {
    Serial.println(F("FAIL"));
    allGood = false;
  } else {
    if (vl53l4cd.startRanging()) {
      Serial.println(F("OK"));
    } else {
      Serial.println(F("FAIL (ranging)"));
      allGood = false;
    }
  }
  
  // Test Environmental Sensor
  Serial.print(F("BME680... "));
  if (!bme.begin()) {
    Serial.println(F("FAIL"));
    allGood = false;
  } else {
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150);
    Serial.println(F("OK"));
  }
  
  // Summary
  Serial.println(F("\n=== Test Summary ==="));
  if (allGood) {
    Serial.println(F("✓ All systems initialized successfully!"));
  } else {
    Serial.println(F("✗ Some systems failed - check wiring and connections"));
  }
}
