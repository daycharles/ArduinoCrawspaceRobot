# Arduino Crawlspace Inspection Robot

A remote-controlled robot designed for inspecting hard-to-reach crawlspaces, featuring tank treads, a 2-DOF robotic arm, live video streaming, and environmental sensors.

![Robot Status](https://img.shields.io/badge/status-active-success)
![Arduino](https://img.shields.io/badge/Arduino-Uno%20%26%20Nano-00979D?logo=arduino)
![ESP32](https://img.shields.io/badge/ESP32-CAM-000000?logo=espressif)

## Features

### Mobility
- **Tank Tread Drive System** - L298N dual motor driver for precise maneuvering
- **Wireless Control** - NRF24L01+ 2.4GHz communication up to 100m range
- **DIY Controller** - Custom controller with joysticks for intuitive operation

### Sensing & Inspection
- **Live Video Stream** - ESP32-CAM module with WiFi streaming
- **Distance Monitoring** - VL53L4CD Time-of-Flight sensor (up to 1.3m range)
- **Environmental Data** - BME688 sensor (temperature, humidity, pressure, gas)
- **Safety System** - Automatic motor stop when obstacle detected (<150mm)

### Manipulation
- **2-DOF Robotic Arm** - SG90 servos with 3D-printed arm structure
- **Remote Arm Control** - Potentiometers on controller for precise positioning

## Hardware Components

### Robot (Arduino Uno)
- Arduino Uno microcontroller
- L298N motor driver module
- 2x DC motors with tank treads
- 2x SG90 servo motors
- NRF24L01+ wireless module
- ESP32-CAM camera module
- BME688 environmental sensor (Modulino Thermo)
- VL53L4CD distance sensor (Modulino Distance)
- 7.4V LiPo battery with 5V step-down converter

### Controller (Arduino Nano)
- Arduino Nano microcontroller
- 2x Analog joysticks
- 2x Potentiometers (arm control)
- NRF24L01+ wireless module
- 9V battery or USB power

## Project Structure

```
ArduinoCrawspaceRobot/
├── robot/
│   ├── main.ino          # Main robot control code
│   └── config.h          # Pin definitions and constants
├── controller/
│   └── transmitter.ino   # Controller/transmitter code
├── esp32_cam/
│   └── camera.ino        # ESP32-CAM streaming code
├── 3d_models/
│   ├── arm/              # 2-DOF arm STL files
│   ├── mounts/           # Component mounting brackets
│   └── enclosure/        # Electronics protection enclosure
└── docs/
    ├── BOM.md            # Bill of Materials
    ├── wiring.md         # Wiring diagrams and connections
    ├── assembly.md       # Step-by-step assembly guide
    └── troubleshooting.md # Common issues and solutions
```

## Getting Started

### Prerequisites
1. **Arduino IDE** - Version 1.8.19+ or Arduino IDE 2.0+
2. **Required Libraries:**
   - RF24 (by TMRh20)
   - Adafruit_BME680
   - Adafruit_VL53L4CD
   - Servo (built-in)
3. **ESP32 Board Support** - For programming ESP32-CAM
4. **3D Printer** - Or access to 3D printing service

### Quick Start

1. **Install Libraries**
   ```
   Arduino IDE → Tools → Manage Libraries
   Search and install: RF24, Adafruit_BME680, Adafruit_VL53L4CD
   ```

2. **Hardware Assembly**
   - Follow the detailed [assembly guide](docs/assembly.md)
   - Refer to [wiring diagram](docs/wiring.md) for connections
   - Use [BOM](docs/BOM.md) to source components

3. **Upload Code**
   - Robot: Upload `robot/main.ino` to Arduino Uno
   - Controller: Upload `controller/transmitter.ino` to Arduino Nano
   - Camera: Upload `esp32_cam/camera.ino` to ESP32-CAM (update WiFi credentials)

4. **Test & Operate**
   - Power on both robot and controller
   - Check Serial Monitor for initialization
   - Access camera stream at `http://<ESP32-IP>`
   - Test motors, servos, and sensors

## Configuration

### Pin Assignments
All pin definitions are in `robot/config.h`. Default pinout:

**Robot (Arduino Uno):**
- Motors: D2-D5 (control), D9-D10 (PWM)
- Servos: D6 (base), D7 (arm)
- NRF24: D8 (CE), D53/D10 (CSN), D11-D13 (SPI)
- Sensors: A4 (SDA), A5 (SCL) for I2C

**Controller (Arduino Nano):**
- Joysticks: A1 (forward/back), A2 (turn)
- Arm Control: A6 (base), A7 (joint)
- NRF24: D9 (CE), D10 (CSN), D11-D13 (SPI)

### Safety Parameters
Modify in `config.h`:
```cpp
#define SAFETY_DISTANCE_MM  150   // Stop if obstacle <150mm
#define MAX_MOTOR_SPEED     255   // Maximum PWM (0-255)
```

## Operation

### Basic Controls
- **Left Joystick Y-axis** - Forward/Backward movement
- **Right Joystick X-axis** - Left/Right turning (tank steering)
- **Arm Base Potentiometer** - Rotate arm base (0-180°)
- **Arm Joint Potentiometer** - Move arm up/down (0-180°)

### Safety Features
- Automatic motor stop when obstacle detected <150mm
- Battery voltage monitoring (if implemented)
- Wireless connection loss handling

### Camera Access
1. Ensure ESP32-CAM is powered and connected to WiFi
2. Check Serial Monitor for assigned IP address
3. Open web browser: `http://<ESP32-IP>`
4. Video stream will display automatically

## Documentation

- **[Bill of Materials](docs/BOM.md)** - Complete parts list with estimated costs
- **[Wiring Diagram](docs/wiring.md)** - Detailed connection guide
- **[Assembly Instructions](docs/assembly.md)** - Step-by-step build guide
- **[Troubleshooting](docs/troubleshooting.md)** - Common issues and fixes

## 3D Printed Parts

All STL files are located in the `3d_models/` directory:
- **arm/** - 2-DOF robotic arm components
- **mounts/** - Motor, sensor, and electronics mounts
- **enclosure/** - Protective enclosure for electronics

Print with 20-30% infill, 0.2mm layer height, PLA or PETG recommended.

## Customization

### Extend Functionality
- Add LED lighting for dark crawlspaces
- Implement return-to-home feature
- Add battery voltage monitoring
- Integrate GPS for outdoor use
- Add emergency stop button on controller

### Code Modifications
- Adjust motor speeds in `robot/main.ino`
- Change wireless channel/address in `config.h`
- Modify servo ranges for different arm designs
- Implement PID control for smoother movement

## Troubleshooting

If you encounter issues:
1. Check power connections and battery charge
2. Verify all wiring matches the diagram
3. Test components individually
4. Review Serial Monitor for error messages
5. Consult [troubleshooting guide](docs/troubleshooting.md)

Common issues:
- **No wireless connection**: Add 10µF capacitor to NRF24L01
- **Motors don't run**: Check L298N power and control pins
- **Servos jitter**: Use external 5V power supply
- **Camera won't connect**: Verify 2.4GHz WiFi and credentials

## Safety Notes

⚠️ **Important Safety Information:**
- Always test in open area before crawlspace use
- Monitor battery voltage to prevent over-discharge
- Keep electronics away from water/moisture
- Ensure proper ventilation in crawlspace
- Never operate unattended
- Follow local regulations for robotic devices

## Contributing

Contributions are welcome! Areas for improvement:
- Enhanced motor control algorithms
- Better power management
- Additional sensor integrations
- Improved 3D models
- Documentation enhancements

## License

This project is provided as-is for educational and hobbyist use.

## Acknowledgments

- Uses RF24 library by TMRh20
- Adafruit sensor libraries
- Arduino and ESP32 communities
- Inspired by crawlspace inspection needs

## Contact & Support

For questions, issues, or contributions:
- Open an issue on GitHub
- Check existing documentation
- Review troubleshooting guide
- Arduino community forums

---

**Built with ❤️ for makers and DIY enthusiasts**