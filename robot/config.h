/**
 * Configuration File for Arduino Crawlspace Inspection Robot
 * Pin definitions and constants
 */

#ifndef CONFIG_H
#define CONFIG_H

// ===== L298N Motor Driver Pins (Tank Treads) =====
#define MOTOR_LEFT_IN1    2
#define MOTOR_LEFT_IN2    3
#define MOTOR_LEFT_EN     9   // PWM enabled pin
#define MOTOR_RIGHT_IN3   4
#define MOTOR_RIGHT_IN4   5
#define MOTOR_RIGHT_EN    10  // PWM enabled pin

// ===== Servo Pins (2-DOF Arm) =====
#define SERVO_BASE_PIN    6
#define SERVO_ARM_PIN     7

// ===== NRF24L01 Wireless Module Pins =====
#define NRF_CE_PIN        8
#define NRF_CSN_PIN       53  // Use 53 for Uno (or 10 for Mega)

// ===== I2C Pins for Sensors (Default for Arduino Uno) =====
// SDA: A4
// SCL: A5
// BME688 (Modulino Thermo) and VL53L4CD (Modulino Distance) use I2C

// ===== Constants =====
#define SAFETY_DISTANCE_MM  150   // Stop robot if distance < 150mm
#define MAX_MOTOR_SPEED     255   // Maximum PWM value
#define MIN_MOTOR_SPEED     0     // Minimum PWM value

// ===== Communication Settings =====
#define RF_CHANNEL          76    // NRF24L01 channel (0-125)
const uint64_t PIPE_ADDRESS = 0xE8E8F0F0E1LL;  // Communication pipe address

// ===== Servo Limits =====
#define SERVO_BASE_MIN      0
#define SERVO_BASE_MAX      180
#define SERVO_ARM_MIN       0
#define SERVO_ARM_MAX       180

// ===== Sensor Update Intervals (ms) =====
#define DISTANCE_UPDATE_INTERVAL  100   // Update distance every 100ms
#define TEMP_UPDATE_INTERVAL      1000  // Update temperature every 1s

#endif // CONFIG_H
