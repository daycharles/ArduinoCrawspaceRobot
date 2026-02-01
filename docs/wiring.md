# Wiring Diagram Documentation
## Arduino Crawlspace Inspection Robot

## Robot (Arduino Uno) Wiring

### Power Distribution
```
7.4V LiPo Battery → L298N 12V Input
7.4V LiPo Battery → 5V Step-Down Converter → Arduino Uno 5V Pin
Arduino Uno 5V → Servos, Sensors, NRF24L01
```

### L298N Motor Driver Connections

#### Power
- **12V**: 7.4V LiPo Battery positive
- **GND**: Battery negative and Arduino GND (common ground)
- **5V**: Leave disconnected (using separate 5V regulator)

#### Motor Outputs
- **OUT1**: Left Motor (+)
- **OUT2**: Left Motor (-)
- **OUT3**: Right Motor (+)
- **OUT4**: Right Motor (-)

#### Control Pins to Arduino Uno
| L298N Pin | Arduino Pin | Description |
|-----------|-------------|-------------|
| ENA | D9 (PWM) | Left motor speed control |
| IN1 | D2 | Left motor direction 1 |
| IN2 | D3 | Left motor direction 2 |
| ENB | D10 (PWM) | Right motor speed control |
| IN3 | D4 | Right motor direction 1 |
| IN4 | D5 | Right motor direction 2 |

### Servo Connections
| Servo | Arduino Pin | Power | Notes |
|-------|-------------|-------|-------|
| Base Servo | D6 | 5V, GND | Brown=GND, Red=5V, Orange=Signal |
| Arm Servo | D7 | 5V, GND | Brown=GND, Red=5V, Orange=Signal |

**Note**: For high-torque servos, use external 5V power supply with common ground.

### NRF24L01+ Wireless Module
| NRF24 Pin | Arduino Pin | Description |
|-----------|-------------|-------------|
| VCC | 3.3V | Power (use 3.3V, NOT 5V!) |
| GND | GND | Ground |
| CE | D8 | Chip Enable |
| CSN | D53 (or D10) | Chip Select |
| SCK | D13 | SPI Clock |
| MOSI | D11 | SPI Master Out |
| MISO | D12 | SPI Master In |

**Important**: NRF24L01 operates at 3.3V. Add 10µF capacitor across VCC and GND for stability.

### BME688 Sensor (Modulino Thermo)
| BME688 Pin | Arduino Pin | Description |
|------------|-------------|-------------|
| VCC | 3.3V or 5V | Power |
| GND | GND | Ground |
| SDA | A4 | I2C Data |
| SCL | A5 | I2C Clock |

### VL53L4CD Distance Sensor (Modulino Distance)
| VL53L4CD Pin | Arduino Pin | Description |
|--------------|-------------|-------------|
| VCC | 3.3V or 5V | Power |
| GND | GND | Ground |
| SDA | A4 | I2C Data (shared with BME688) |
| SCL | A5 | I2C Clock (shared with BME688) |

**Note**: Both I2C sensors share the same bus. Ensure they have different I2C addresses or can coexist.

### Complete Arduino Uno Pin Assignment
```
Digital Pins:
D2  → L298N IN1 (Left Motor)
D3  → L298N IN2 (Left Motor)
D4  → L298N IN3 (Right Motor)
D5  → L298N IN4 (Right Motor)
D6  → Base Servo Signal
D7  → Arm Servo Signal
D8  → NRF24 CE
D9  → L298N ENA (PWM - Left Motor Speed)
D10 → L298N ENB (PWM - Right Motor Speed)
D11 → NRF24 MOSI (SPI)
D12 → NRF24 MISO (SPI)
D13 → NRF24 SCK (SPI)
D53 → NRF24 CSN (or D10 if not using Mega)

Analog Pins:
A4  → I2C SDA (BME688 & VL53L4CD)
A5  → I2C SCL (BME688 & VL53L4CD)

Power:
5V  → Servos, Step-down converter
3.3V → NRF24L01, Sensors
GND → Common ground for all components
```

---

## Controller (Arduino Nano) Wiring

### NRF24L01+ Wireless Module
| NRF24 Pin | Arduino Nano Pin | Description |
|-----------|------------------|-------------|
| VCC | 3.3V | Power |
| GND | GND | Ground |
| CE | D9 | Chip Enable |
| CSN | D10 | Chip Select |
| SCK | D13 | SPI Clock |
| MOSI | D11 | SPI Master Out |
| MISO | D12 | SPI Master In |

### Joysticks and Potentiometers
| Component | Arduino Pin | Description |
|-----------|-------------|-------------|
| Left Joystick VRx | Not connected | Optional |
| Left Joystick VRy | A1 | Forward/Backward |
| Left Joystick SW | Not connected | Optional button |
| Right Joystick VRx | A2 | Left/Right turning |
| Right Joystick VRy | Not connected | Optional |
| Right Joystick SW | Not connected | Optional button |
| Arm Base Pot | A6 | Servo base angle |
| Arm Joint Pot | A7 | Servo arm angle |

### Joystick Power
- **VCC**: Connect all joystick/pot VCC pins to 5V
- **GND**: Connect all joystick/pot GND pins to GND

### Complete Arduino Nano Pin Assignment
```
Digital Pins:
D9  → NRF24 CE
D10 → NRF24 CSN
D11 → NRF24 MOSI (SPI)
D12 → NRF24 MISO (SPI)
D13 → NRF24 SCK (SPI)

Analog Pins:
A1  → Left Joystick Y (Forward/Backward)
A2  → Right Joystick X (Turn Left/Right)
A6  → Arm Base Potentiometer
A7  → Arm Joint Potentiometer

Power:
5V  → Joysticks, Potentiometers
3.3V → NRF24L01
GND → Common ground
```

---

## ESP32-CAM Wiring

The ESP32-CAM is a standalone module with built-in camera and WiFi.

### Power
- **5V**: Connect to 5V power source
- **GND**: Connect to ground

### Programming
For initial programming, connect:
- **GPIO0** to **GND** (boot mode)
- **TX** to USB-TTL adapter RX
- **RX** to USB-TTL adapter TX
- **5V** and **GND** to USB-TTL adapter

After programming, remove GPIO0 connection to GND for normal operation.

### Camera Module
Camera module is pre-connected on ESP32-CAM board. No additional wiring needed.

---

## Wiring Best Practices

1. **Common Ground**: Ensure all components share a common ground connection
2. **Color Coding**: Use consistent wire colors
   - Red: Power (+)
   - Black: Ground (-)
   - Yellow/White: Signal/Data
3. **Wire Management**: Use cable ties and heat shrink for organization
4. **Secure Connections**: Solder critical connections; use quality connectors
5. **Capacitors**: Add 10µF capacitor across NRF24L01 power pins for stability
6. **Power Isolation**: Keep motor power separate from logic power (use the 5V regulator)
7. **Check Voltage Levels**: 
   - NRF24L01: 3.3V only
   - Servos: 5V (check datasheet)
   - Motors: 6-12V
8. **Polarity**: Double-check battery and motor polarity before powering on
9. **Test Incrementally**: Power on components one at a time to verify connections

---

## Safety Notes

- **Never** connect motors directly to Arduino pins
- Use proper current-rated connectors for battery
- Add fuse to battery positive line
- Monitor battery voltage to prevent over-discharge
- Disconnect battery when not in use
- Keep electronics away from water/moisture in crawlspace

---

## Troubleshooting Wiring Issues

See [troubleshooting.md](troubleshooting.md) for detailed debugging steps.
