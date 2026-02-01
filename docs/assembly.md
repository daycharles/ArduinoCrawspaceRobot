# Assembly Instructions
## Arduino Crawlspace Inspection Robot

## Overview
This guide walks you through assembling the crawlspace inspection robot from components. Allow 4-6 hours for complete assembly.

## Prerequisites
- All components from BOM acquired
- 3D printed parts completed
- Basic soldering skills
- Multimeter for testing

---

## Phase 1: Chassis Preparation (30 minutes)

### 1.1 Print 3D Components
If using custom 3D printed chassis:
1. Print all STL files from `/3d_models/` directory
   - Chassis base and top
   - Motor mounts (4 pieces)
   - Servo arm components (base, shoulder, elbow)
   - Electronics enclosure
   - Camera mount
   - Sensor mount

2. Clean up prints
   - Remove support material
   - Sand rough edges
   - Test fit components

### 1.2 Assemble Tank Tread System
1. Install DC motors into motor mounts
   - Use M3 screws to secure motors
   - Ensure motor shafts align with tread sprockets

2. Attach motor mounts to chassis
   - Position at four corners of chassis
   - Secure with M3 screws and nuts
   - Verify motor placement is level

3. Install tank treads
   - Route treads around front and rear sprockets
   - Adjust tension (not too tight, not too loose)
   - Test manual rotation

---

## Phase 2: Motor Driver Installation (20 minutes)

### 2.1 Mount L298N Module
1. Position L298N on chassis
   - Choose location away from sensors
   - Ensure heat sink has air flow
   - Use double-sided tape or M3 standoffs

### 2.2 Connect Motors
1. Solder JST connectors to motor leads if needed
2. Connect motors to L298N outputs:
   - Left motor → OUT1 (+), OUT2 (-)
   - Right motor → OUT3 (+), OUT4 (-)
3. Mark motor polarity for reference

---

## Phase 3: Arduino Uno Setup (30 minutes)

### 3.1 Mount Arduino
1. Attach Arduino Uno to chassis
   - Use M3 standoffs (recommended height: 10mm)
   - Position near center for wire management
   - Ensure USB port is accessible

### 3.2 Prepare Power System
1. Mount 5V step-down converter
   - Position near battery location
   - Allow ventilation

2. Solder power connections:
   - Battery (+) → L298N 12V input
   - Battery (+) → 5V converter input
   - Battery (-) → Common ground
   - 5V converter output → Arduino Vin pin
   - Add power switch to battery positive line

3. **Test power system**:
   - Connect battery
   - Verify 5V output with multimeter
   - Check Arduino LED lights up

---

## Phase 4: Wire Control Connections (45 minutes)

### 4.1 L298N to Arduino
Follow the wiring diagram in `wiring.md`:
1. Connect control pins:
   - ENA → D9
   - IN1 → D2, IN2 → D3
   - ENB → D10
   - IN3 → D4, IN4 → D5

2. Connect ground:
   - L298N GND → Arduino GND

### 4.2 Install NRF24L01 Module
1. **Important**: Add 10µF capacitor across VCC/GND on NRF24
2. Connect using Dupont wires (reference wiring.md):
   - VCC → 3.3V (NOT 5V!)
   - CE → D8
   - CSN → D53 (or D10)
   - Standard SPI pins (D11, D12, D13)

### 4.3 Test Motor Control
1. Upload a simple motor test sketch
2. Verify both motors can run forward/backward
3. Check direction matches expectations
4. If direction is wrong, swap motor wires at L298N

---

## Phase 5: Servo Arm Assembly (40 minutes)

### 5.1 Build 2-DOF Arm
1. Assemble 3D printed arm components:
   - Insert base servo into base mount
   - Secure with M2 screws
   - Attach servo horn to base servo
   - Mount lower arm segment

2. Install arm servo:
   - Position arm servo in shoulder joint
   - Secure with M2 screws
   - Attach servo horn to upper arm

3. Mount complete arm to chassis:
   - Attach base mount to chassis
   - Verify full range of motion
   - No binding or obstructions

### 5.2 Wire Servos
1. Connect servos to Arduino:
   - Base servo → D6 (signal), 5V, GND
   - Arm servo → D7 (signal), 5V, GND
2. Use servo extension cables if needed
3. Secure wires to arm with zip ties

### 5.3 Test Servos
1. Upload servo test sketch
2. Verify smooth movement 0-180°
3. Center both servos at 90°
4. Check arm doesn't hit chassis or other components

---

## Phase 6: Sensor Installation (30 minutes)

### 6.1 Mount Sensors
1. **VL53L4CD Distance Sensor**:
   - Install in front-facing sensor mount
   - Position at center front of robot
   - Unobstructed view forward
   - Secure with M2 screws or hot glue

2. **BME688 Environmental Sensor**:
   - Mount in electronics enclosure
   - Ensure air can reach sensor
   - Protect from dust/debris

### 6.2 Wire Sensors
1. Connect both sensors to I2C bus:
   - VCC → 5V (or 3.3V, check datasheet)
   - GND → GND
   - SDA → A4
   - SCL → A5

2. Both sensors share same I2C bus
3. Use 4.7kΩ pull-up resistors if needed (often built-in)

### 6.3 Test Sensors
1. Upload sensor test sketch
2. Verify I2C addresses detected (use I2C scanner)
3. Check distance readings make sense
4. Verify temperature/humidity readings

---

## Phase 7: ESP32-CAM Installation (30 minutes)

### 7.1 Program ESP32-CAM
1. Connect ESP32-CAM to USB-TTL adapter:
   - GPIO0 → GND (for programming mode)
   - TX/RX to adapter (crossed)
   - 5V and GND

2. Upload camera.ino from esp32_cam folder
3. Update WiFi credentials in code
4. Remove GPIO0 connection after programming

### 7.2 Mount Camera
1. Install ESP32-CAM in camera mount
2. Position at front of robot
3. Adjust angle for optimal view
4. Secure with M2 screws

### 7.3 Power Camera
1. Connect 5V and GND from main power
2. Can share Arduino's 5V supply
3. Test camera stream on WiFi network

---

## Phase 8: Controller Assembly (45 minutes)

### 8.1 Build Controller Base
1. Create controller housing:
   - Use project box or 3D printed enclosure
   - Drill holes for joysticks and potentiometers
   - Mount Arduino Nano inside

### 8.2 Install Controls
1. Mount joysticks:
   - Left joystick (forward/back)
   - Right joystick (turning)
   - Secure with nuts and washers

2. Mount potentiometers:
   - Arm base control
   - Arm joint control
   - Add knobs for easy adjustment

### 8.3 Wire Controller
1. Connect joysticks to Arduino Nano:
   - Left Y → A1
   - Right X → A2
   - Potentiometers → A6, A7
   - All 5V and GND connections

2. Install NRF24L01:
   - Same pinout as robot
   - CE → D9, CSN → D10
   - Add 10µF capacitor

3. Add battery connector or USB power

### 8.4 Test Controller
1. Upload transmitter.ino
2. Verify joystick readings on Serial Monitor
3. Check NRF24 transmission successful

---

## Phase 9: Final Integration (30 minutes)

### 9.1 Upload Final Code
1. Upload main.ino to robot Arduino Uno
2. Verify all includes compile successfully
3. Open Serial Monitor to check initialization

### 9.2 System Test
1. Power on both robot and controller
2. Verify wireless communication
3. Test each function:
   - Forward/backward movement
   - Left/right turning
   - Base servo control
   - Arm servo control
   - Distance sensor reading
   - Environmental sensor reading

### 9.3 Safety Test
1. Test distance sensor safety stop:
   - Place object <150mm from sensor
   - Verify motors stop automatically
   - Move object away
   - Verify robot resumes operation

### 9.4 Camera Test
1. Power on ESP32-CAM
2. Connect to camera stream via web browser
3. Verify video quality and framerate

---

## Phase 10: Final Assembly & Finishing (20 minutes)

### 10.1 Wire Management
1. Bundle wires with zip ties
2. Route wires away from moving parts
3. Secure loose wires to chassis
4. Label important connections

### 10.2 Install Enclosure
1. Place electronics enclosure over components
2. Ensure ventilation holes clear
3. Secure with clips or screws
4. Keep Arduino USB accessible for updates

### 10.3 Battery Mounting
1. Secure battery with Velcro straps
2. Position for balanced weight distribution
3. Ensure easy removal for charging
4. Add battery voltage monitor (optional)

### 10.4 Final Checks
- All screws tightened
- No loose wires
- Moving parts clear
- Battery charged
- Power switch works
- Emergency stop accessible

---

## Congratulations!
Your Arduino Crawlspace Inspection Robot is now complete!

## Next Steps
1. Perform initial test runs in safe area
2. Adjust PID/motor speeds if needed
3. Calibrate distance sensor threshold
4. Review troubleshooting guide if issues arise
5. Begin crawlspace inspections!

---

## Maintenance Schedule
- **After each use**: Check for loose screws, wire damage
- **Weekly**: Clean sensors, check battery health
- **Monthly**: Re-calibrate sensors, tighten all fasteners
- **Annually**: Replace worn treads, check motor brushes

---

## Safety Reminders
- Always test in open area first
- Keep spare battery charged
- Monitor battery voltage during use
- Never operate unattended
- Keep robot dry
- Follow local regulations for robotic devices
