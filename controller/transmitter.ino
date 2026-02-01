/**
 * Arduino Crawlspace Robot - Controller (Transmitter)
 * 
 * Hardware:
 * - Arduino Nano
 * - 2x Analog Joysticks
 * - NRF24L01 Wireless Module
 * 
 * Joystick Connections:
 * - Left Joystick X: A0 (not used for tank control)
 * - Left Joystick Y: A1 (forward/backward)
 * - Right Joystick X: A2 (left/right turning)
 * - Right Joystick Y: A3 (not used for tank control)
 * - Arm Base Pot: A6 (servo base control)
 * - Arm Joint Pot: A7 (servo arm control)
 * 
 * Libraries Required:
 * - RF24
 */

#include <SPI.h>
#include <RF24.h>

// ===== Pin Definitions =====
#define NRF_CE_PIN        9
#define NRF_CSN_PIN       10

// Joystick pins
#define LEFT_JOY_Y        A1  // Forward/Backward
#define RIGHT_JOY_X       A2  // Left/Right turning
#define ARM_BASE_POT      A6  // Servo base angle
#define ARM_JOINT_POT     A7  // Servo arm angle

// ===== Constants =====
#define JOYSTICK_CENTER   512
#define JOYSTICK_DEADZONE 50
#define RF_CHANNEL        76
const uint64_t PIPE_ADDRESS = 0xE8E8F0F0E1LL;

// ===== Control Data Structure =====
struct ControlData {
  int leftMotorSpeed;   // -255 to 255
  int rightMotorSpeed;  // -255 to 255
  int servoBaseAngle;   // 0 to 180
  int servoArmAngle;    // 0 to 180
};

ControlData controlData;

// ===== Object Instances =====
RF24 radio(NRF_CE_PIN, NRF_CSN_PIN);

// ===== Function Prototypes =====
void setupWireless();
void readJoysticks();
void calculateMotorSpeeds(int forward, int turn);
int applyDeadzone(int value, int center, int deadzone);

void setup() {
  Serial.begin(115200);
  Serial.println(F("Controller Starting..."));
  
  // Initialize analog pins (optional, they're inputs by default)
  pinMode(LEFT_JOY_Y, INPUT);
  pinMode(RIGHT_JOY_X, INPUT);
  pinMode(ARM_BASE_POT, INPUT);
  pinMode(ARM_JOINT_POT, INPUT);
  
  setupWireless();
  
  // Initialize control data to neutral
  controlData.leftMotorSpeed = 0;
  controlData.rightMotorSpeed = 0;
  controlData.servoBaseAngle = 90;
  controlData.servoArmAngle = 90;
  
  Serial.println(F("Controller Ready!"));
}

void loop() {
  readJoysticks();
  
  // Send data
  bool success = radio.write(&controlData, sizeof(ControlData));
  
  if (success) {
    Serial.print(F("Sent - L:"));
    Serial.print(controlData.leftMotorSpeed);
    Serial.print(F(" R:"));
    Serial.print(controlData.rightMotorSpeed);
    Serial.print(F(" Base:"));
    Serial.print(controlData.servoBaseAngle);
    Serial.print(F(" Arm:"));
    Serial.println(controlData.servoArmAngle);
  } else {
    Serial.println(F("Transmission failed!"));
  }
  
  delay(50);  // Send updates at ~20Hz
}

void setupWireless() {
  if (!radio.begin()) {
    Serial.println(F("NRF24L01 radio hardware not responding!"));
    while (1) {} // Hold in infinite loop
  }
  
  radio.openWritingPipe(PIPE_ADDRESS);
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(RF_CHANNEL);
  radio.stopListening();
  
  Serial.println(F("NRF24L01 initialized"));
}

void readJoysticks() {
  // Read joystick values
  int forward = analogRead(LEFT_JOY_Y);
  int turn = analogRead(RIGHT_JOY_X);
  int basePos = analogRead(ARM_BASE_POT);
  int armPos = analogRead(ARM_JOINT_POT);
  
  // Apply deadzone to movement controls
  forward = applyDeadzone(forward, JOYSTICK_CENTER, JOYSTICK_DEADZONE);
  turn = applyDeadzone(turn, JOYSTICK_CENTER, JOYSTICK_DEADZONE);
  
  // Convert forward/turn to motor speeds (tank steering)
  calculateMotorSpeeds(forward, turn);
  
  // Convert potentiometer values to servo angles (0-1023 -> 0-180)
  controlData.servoBaseAngle = map(basePos, 0, 1023, 0, 180);
  controlData.servoArmAngle = map(armPos, 0, 1023, 0, 180);
}

void calculateMotorSpeeds(int forward, int turn) {
  // Convert joystick values (0-1023) to speed values (-255 to 255)
  // Forward: 0 = full reverse, 512 = stop, 1023 = full forward
  // Turn: 0 = full left, 512 = straight, 1023 = full right
  
  int forwardSpeed = map(forward, 0, 1023, -255, 255);
  int turnSpeed = map(turn, 0, 1023, -255, 255);
  
  // Tank steering: differential drive
  // Left motor = forward - turn
  // Right motor = forward + turn
  int leftSpeed = forwardSpeed - turnSpeed;
  int rightSpeed = forwardSpeed + turnSpeed;
  
  // Constrain to valid range
  leftSpeed = constrain(leftSpeed, -255, 255);
  rightSpeed = constrain(rightSpeed, -255, 255);
  
  controlData.leftMotorSpeed = leftSpeed;
  controlData.rightMotorSpeed = rightSpeed;
}

int applyDeadzone(int value, int center, int deadzone) {
  // Apply deadzone around center position
  if (value > center - deadzone && value < center + deadzone) {
    return center;
  }
  return value;
}
