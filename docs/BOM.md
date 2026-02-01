# Bill of Materials (BOM)
## Arduino Crawlspace Inspection Robot

### Main Components

#### Electronics - Robot (Arduino Uno)
| Qty | Component | Description | Notes |
|-----|-----------|-------------|-------|
| 1 | Arduino Uno | Main microcontroller | Or compatible board |
| 1 | L298N Motor Driver | Dual H-bridge for tank treads | Supports up to 2A per channel |
| 2 | DC Motors with Tank Treads | Drive system | 6-12V DC motors |
| 2 | SG90 Servo Motors | 2-DOF robotic arm | 180° rotation |
| 1 | NRF24L01+ Module | 2.4GHz wireless transceiver | With external antenna recommended |
| 1 | ESP32-CAM | Camera module with WiFi | AI-Thinker module |
| 1 | BME688 Sensor (Modulino Thermo) | Temperature, humidity, pressure, gas | I2C interface |
| 1 | VL53L4CD Sensor (Modulino Distance) | Time-of-Flight distance sensor | Up to 1300mm range, I2C |
| 1 | 7.4V LiPo Battery | Power supply for motors | 2S, 2200mAh or higher |
| 1 | 5V Step-Down Converter | Power for Arduino and sensors | 3A capacity recommended |
| 1 | Power Switch | Main power control | SPST switch |

#### Electronics - Controller (Arduino Nano)
| Qty | Component | Description | Notes |
|-----|-----------|-------------|-------|
| 1 | Arduino Nano | Controller microcontroller | Or compatible board |
| 2 | Analog Joysticks | Movement control | Two-axis joysticks |
| 2 | Potentiometers | Arm servo control | 10kΩ linear |
| 1 | NRF24L01+ Module | 2.4GHz wireless transceiver | With external antenna recommended |
| 1 | 9V Battery | Controller power | Or USB power |
| 1 | Battery Connector | 9V battery snap connector | |

#### Mechanical Components
| Qty | Component | Description | Notes |
|-----|-----------|-------------|-------|
| 1 | Robot Chassis | Main body structure | Custom 3D printed or commercial |
| 2 | Tank Tread Sets | Left and right treads | Compatible with motors |
| 1 | 2-DOF Arm Assembly | Robotic arm structure | 3D printed parts (see /3d_models/arm) |
| 4 | Motor Mounts | Secure motors to chassis | 3D printed (see /3d_models/mounts) |
| 1 | Electronics Enclosure | Protect components | 3D printed (see /3d_models/enclosure) |
| 1 | Camera Mount | ESP32-CAM positioning | Adjustable angle preferred |
| 1 | Sensor Mount | For distance sensor | Front-facing |

#### Hardware & Fasteners
| Qty | Component | Description | Notes |
|-----|-----------|-------------|-------|
| 20 | M3 Screws | Various lengths | 8mm, 12mm, 16mm |
| 20 | M3 Nuts | Hex nuts | |
| 10 | M2 Screws | Servo mounting | 6mm, 8mm |
| 1 | Double-sided Tape | Component mounting | High-strength |
| 1 | Wire Bundle | 22-24 AWG | Various colors |
| 1 | Heat Shrink Tubing | Wire protection | Assorted sizes |

#### Connectors & Cables
| Qty | Component | Description | Notes |
|-----|-----------|-------------|-------|
| 10 | Dupont Connectors | Female-to-Female jumpers | 20cm length |
| 5 | JST Connectors | Motor/power connections | Male and female sets |
| 1 | USB Cable | Programming Arduino | Mini/Micro USB |

### Total Estimated Cost
- Electronics (Robot): ~$120-150 USD
- Electronics (Controller): ~$30-40 USD
- Mechanical Components: ~$40-60 USD (if 3D printing)
- Hardware & Supplies: ~$20-30 USD
- **Total: ~$210-280 USD**

### Required Tools
- Soldering iron and solder
- Wire strippers
- Screwdrivers (Phillips and flathead)
- Hot glue gun
- Multimeter
- 3D Printer (or access to 3D printing service)

### Software/Libraries Required
- Arduino IDE (version 1.8.19 or later / Arduino IDE 2.0+)
- RF24 library (by TMRh20)
- Adafruit BME680 library
- Adafruit VL53L4CD library
- Servo library (built-in)
- ESP32 board support package (for ESP32-CAM)

### Optional Components
| Qty | Component | Description | Notes |
|-----|-----------|-------------|-------|
| 1 | LED Strip | Undercarriage lighting | For dark crawlspaces |
| 1 | Buzzer | Audio feedback | Low voltage piezo |
| 1 | Emergency Stop Button | Safety feature | Large red button for controller |
| 1 | LCD Display | Controller status display | 16x2 I2C LCD |
| 1 | Voltage Sensor | Battery monitoring | 0-25V range |

### Notes
- All components should be checked for voltage compatibility
- Consider purchasing spare sensors and connectors
- Verify motor current draw matches L298N specifications
- NRF24L01+ modules with external antenna provide better range
- Use quality LiPo battery with protection circuit
