# Troubleshooting Guide
## Arduino Crawlspace Inspection Robot

## General Troubleshooting Steps
1. Check all power connections and battery charge
2. Verify common ground between all components
3. Check Serial Monitor for error messages
4. Test components individually before full system test
5. Verify pin definitions match actual wiring

---

## Power Issues

### Robot Won't Turn On
**Symptoms**: No LED lights, no response
**Causes & Solutions**:
- ✓ Check battery charge (should be >7.0V for 2S LiPo)
- ✓ Verify power switch is ON
- ✓ Check fuse if installed
- ✓ Test 5V regulator output with multimeter
- ✓ Verify Arduino Vin receives ~5V
- ✓ Check for short circuits (disconnect battery immediately if components get hot)

### Arduino Powers On But Components Don't Work
**Symptoms**: Arduino LED on, but motors/servos/sensors not responding
**Causes & Solutions**:
- ✓ Check 5V rail with multimeter
- ✓ Verify common ground connections
- ✓ Ensure 5V regulator can supply enough current (>2A recommended)
- ✓ Check for loose connections
- ✓ Test each component with dedicated power supply

### Intermittent Power Loss
**Symptoms**: Robot randomly shuts down or reboots
**Causes & Solutions**:
- ✓ Battery may be over-discharged (check voltage)
- ✓ Loose battery connection
- ✓ Insufficient current capacity from 5V regulator
- ✓ Add capacitors to power lines (100µF on 5V rail)
- ✓ Check for momentary shorts when robot moves

---

## Motor Issues

### Motors Don't Run
**Symptoms**: No motor movement when joystick moved
**Causes & Solutions**:
- ✓ Check L298N power LED is lit
- ✓ Verify motor power supply (7.4V battery connected to 12V input)
- ✓ Test motors directly with battery (confirm motors work)
- ✓ Check control pin connections (IN1, IN2, IN3, IN4)
- ✓ Verify EN pins connected to PWM-capable Arduino pins
- ✓ Upload simple motor test sketch to isolate issue
- ✓ Check Serial Monitor for received control commands

### Motors Run But Wrong Direction
**Symptoms**: Forward command makes robot go backward
**Causes & Solutions**:
- ✓ Swap motor wires at L298N outputs (OUT1↔OUT2 or OUT3↔OUT4)
- ✓ Or modify code to invert motor direction in software

### One Motor Works, One Doesn't
**Symptoms**: Only left or right motor responds
**Causes & Solutions**:
- ✓ Check wiring to non-working motor
- ✓ Test motor directly with battery
- ✓ Verify all control pins for that motor channel
- ✓ Check if EN pin is connected and receiving PWM
- ✓ L298N may have damaged channel (test with multimeter)

### Motors Run Slowly or Weak
**Symptoms**: Robot moves but lacks power
**Causes & Solutions**:
- ✓ Battery voltage too low (charge battery)
- ✓ PWM speed values too low in code
- ✓ Motor wiring has high resistance (check connections)
- ✓ Tank treads too tight (adjust tension)
- ✓ L298N overheating (add heatsink, improve airflow)

### Motors Stutter or Jerk
**Symptoms**: Inconsistent motor operation
**Causes & Solutions**:
- ✓ Poor wireless connection (see Wireless Issues)
- ✓ Power supply brownout (add capacitors)
- ✓ Bad motor contacts/brushes
- ✓ Increase loop delay in controller code (reduce update rate)

---

## Wireless Communication Issues

### No Wireless Connection
**Symptoms**: "Transmission failed" or no data received
**Causes & Solutions**:
- ✓ Check NRF24L01 power (must be 3.3V, NOT 5V)
- ✓ Add 10µF capacitor across NRF24 VCC and GND
- ✓ Verify SPI pins correct (CE, CSN, SCK, MOSI, MISO)
- ✓ Ensure both devices use same channel and pipe address
- ✓ Check for physical damage to NRF24 modules
- ✓ Try modules with external antenna for better range
- ✓ Upload I2C/SPI scanner to verify NRF24 responds
- ✓ Reduce distance between controller and robot for testing

### Intermittent Connection
**Symptoms**: Connection drops randomly
**Causes & Solutions**:
- ✓ Add larger capacitor to NRF24 (47-100µF)
- ✓ Use shielded wires for NRF24 connections
- ✓ Move NRF24 away from motors and motor driver (EMI)
- ✓ Reduce RF interference (change channel in config.h)
- ✓ Upgrade to NRF24L01+ PA+LNA version (external antenna)
- ✓ Add metal shielding around NRF24

### Short Range
**Symptoms**: Connection only works when very close
**Causes & Solutions**:
- ✓ Use NRF24L01+ with external antenna
- ✓ Set power level to RF24_PA_HIGH (change in code)
- ✓ Ensure antenna connector is tight
- ✓ Add ground plane near antenna
- ✓ Check for interference from ESP32-CAM WiFi

---

## Servo Issues

### Servos Don't Move
**Symptoms**: Arm servos don't respond to potentiometer
**Causes & Solutions**:
- ✓ Check servo power (5V and GND)
- ✓ Verify signal pin connections (D6, D7)
- ✓ Test servos with simple Servo sweep sketch
- ✓ Ensure Servo library included in code
- ✓ Check Serial Monitor for received servo angles
- ✓ Servos may require external power if drawing >500mA

### Servos Jitter or Vibrate
**Symptoms**: Servos shake or make noise when stopped
**Causes & Solutions**:
- ✓ Power supply noise (add 100-470µF capacitor near servos)
- ✓ Use external 5V power supply for servos (not Arduino 5V)
- ✓ Check for loose servo horns or gears
- ✓ Adjust servo positions to avoid mechanical binding
- ✓ Add small delay in servo write commands

### Limited Servo Range
**Symptoms**: Servos don't reach full 0-180° range
**Causes & Solutions**:
- ✓ Some servos have limited range (check datasheet)
- ✓ Mechanical obstruction preventing full rotation
- ✓ Adjust min/max values in servo library
- ✓ Calibrate potentiometer endpoints in controller code

---

## Sensor Issues

### Distance Sensor Not Reading
**Symptoms**: VL53L4CD returns 0 or error values
**Causes & Solutions**:
- ✓ Check I2C connections (SDA to A4, SCL to A5)
- ✓ Verify sensor power (3.3V or 5V, check datasheet)
- ✓ Run I2C scanner sketch to detect sensor address
- ✓ Check for I2C address conflicts
- ✓ Sensor may need time to initialize (add delay in setup)
- ✓ Clean sensor lens
- ✓ Ensure sensor has clear line of sight
- ✓ Check library version compatibility

### Environmental Sensor Not Reading
**Symptoms**: BME688 returns error or invalid readings
**Causes & Solutions**:
- ✓ Verify I2C connections (shared bus with distance sensor)
- ✓ Run I2C scanner to confirm sensor detected
- ✓ Check I2C address (usually 0x76 or 0x77)
- ✓ Ensure sensor has adequate warm-up time
- ✓ Library version may need update
- ✓ Gas sensor requires heating time (150ms default)

### Inaccurate Distance Readings
**Symptoms**: Distance values don't match reality
**Causes & Solutions**:
- ✓ Calibrate sensor (see VL53L4CD datasheet)
- ✓ Sensor pointed at angle (should be perpendicular)
- ✓ Reflective surfaces cause errors
- ✓ Ambient light interference
- ✓ Check measurement mode settings

### Safety Stop Not Working
**Symptoms**: Robot doesn't stop when object near
**Causes & Solutions**:
- ✓ Verify distance readings in Serial Monitor
- ✓ Check SAFETY_DISTANCE_MM threshold in config.h
- ✓ Ensure applySafetyCheck() called in main loop
- ✓ Logic may be inverted (check if statement)
- ✓ Sensor update interval too slow

---

## ESP32-CAM Issues

### Camera Won't Program
**Symptoms**: Upload fails, timeout errors
**Causes & Solutions**:
- ✓ GPIO0 must be connected to GND during upload
- ✓ Check TX/RX connections (should be crossed)
- ✓ Use 5V 1A+ power supply (USB may be insufficient)
- ✓ Press reset button on ESP32-CAM before upload
- ✓ Try different USB-TTL adapter
- ✓ Select correct board (AI Thinker ESP32-CAM)
- ✓ Reduce upload speed (115200 to 57600)

### Camera Won't Connect to WiFi
**Symptoms**: No IP address shown in Serial Monitor
**Causes & Solutions**:
- ✓ Verify WiFi credentials correct in code
- ✓ Check WiFi network is 2.4GHz (ESP32 doesn't support 5GHz)
- ✓ Move closer to WiFi router
- ✓ Check Serial Monitor for connection errors
- ✓ Try different WiFi network
- ✓ Add longer timeout in WiFi connection code

### No Video Stream
**Symptoms**: IP address works but no image
**Causes & Solutions**:
- ✓ Check camera initialization in Serial Monitor
- ✓ Try different image quality/size settings
- ✓ Clear browser cache
- ✓ Try different browser
- ✓ Check camera ribbon cable connection
- ✓ Camera module may be damaged
- ✓ Reduce frame size if connection unstable

### Poor Video Quality
**Symptoms**: Blurry, dark, or low framerate
**Causes & Solutions**:
- ✓ Adjust camera settings (brightness, contrast)
- ✓ Clean camera lens
- ✓ Improve lighting in crawlspace
- ✓ Change JPEG quality setting (lower number = better quality)
- ✓ Reduce resolution for better framerate
- ✓ Check WiFi signal strength

---

## Code Issues

### Compilation Errors
**Symptoms**: Code won't upload, errors in Arduino IDE
**Causes & Solutions**:
- ✓ Install required libraries (RF24, Adafruit_BME680, Adafruit_VL53L4CD, Servo)
- ✓ Check for typos in variable names
- ✓ Verify #include statements
- ✓ Ensure config.h in same folder as main.ino
- ✓ Update Arduino IDE to latest version
- ✓ Select correct board (Arduino Uno, Nano, ESP32)

### Upload Errors
**Symptoms**: Compilation succeeds but upload fails
**Causes & Solutions**:
- ✓ Select correct COM port
- ✓ Close Serial Monitor before upload
- ✓ Check USB cable (must be data cable, not charge-only)
- ✓ Try different USB port
- ✓ Disconnect components that use RX/TX pins
- ✓ Install CH340 drivers (for clones)

### Robot Behavior Doesn't Match Code
**Symptoms**: Logic seems wrong
**Causes & Solutions**:
- ✓ Verify correct code uploaded (check timestamp)
- ✓ Use Serial.println() for debugging
- ✓ Check variable values in Serial Monitor
- ✓ Ensure constants in config.h are correct

---

## Mechanical Issues

### Tank Treads Slip
**Symptoms**: Motors run but robot doesn't move
**Causes & Solutions**:
- ✓ Adjust tread tension (tighter)
- ✓ Clean treads and sprockets
- ✓ Add tread cleats for grip
- ✓ Reduce weight or increase motor torque

### Arm Doesn't Hold Position
**Symptoms**: Arm droops under weight
**Causes & Solutions**:
- ✓ Use higher-torque servos (metal gear)
- ✓ Reduce arm weight (lighter materials)
- ✓ Add counterweight to balance
- ✓ Design shorter arm for less leverage

### Components Come Loose
**Symptoms**: Screws vibrate loose
**Causes & Solutions**:
- ✓ Use thread-lock compound
- ✓ Add lock washers
- ✓ Tighten screws periodically
- ✓ Use nylon insert lock nuts

---

## Using Serial Monitor for Debugging

1. Connect Arduino to computer via USB
2. Open Serial Monitor (Ctrl+Shift+M or Tools → Serial Monitor)
3. Set baud rate to 115200
4. Watch for initialization messages
5. Check for error messages
6. View sensor readings and control values

**Key Debug Messages to Add**:
```cpp
Serial.print("Distance: ");
Serial.println(currentDistance);

Serial.print("Motor L/R: ");
Serial.print(leftSpeed);
Serial.print(" / ");
Serial.println(rightSpeed);
```

---

## Advanced Debugging

### Multimeter Tests
- Measure battery voltage (should be 7.4V nominal)
- Check 5V rail (should be 4.9-5.1V)
- Verify 3.3V for NRF24 (should be 3.2-3.4V)
- Test motor resistance (should be 5-20Ω typically)

### Oscilloscope Tests
- Check PWM signals on motor EN pins
- Verify servo pulse width (1-2ms)
- Check SPI signals for NRF24

### Logic Analyzer
- Debug I2C communication with sensors
- Verify SPI timing for NRF24

---

## Still Having Issues?

1. Check each component individually with test code
2. Review all connections against wiring diagram
3. Test with minimal configuration (remove components one by one)
4. Ask for help on Arduino forums with:
   - Detailed description of issue
   - Photos of wiring
   - Serial Monitor output
   - Code snippets
5. Consider replacing suspected faulty components

---

## Preventive Maintenance

- Clean sensors regularly
- Check all connections before each use
- Monitor battery health
- Keep firmware up to date
- Document any modifications
- Take photos of working configuration
