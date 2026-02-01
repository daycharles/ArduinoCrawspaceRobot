# Arduino Crawlspace Robot - Library Dependencies

## Required Libraries

Install these libraries through the Arduino IDE Library Manager:
**Tools → Manage Libraries** or **Sketch → Include Library → Manage Libraries**

### Core Libraries (Robot & Controller)

1. **RF24**
   - By: TMRh20
   - Version: 1.4.5 or later
   - Description: NRF24L01+ wireless communication
   - GitHub: https://github.com/nRF24/RF24
   - Installation: Search "RF24" in Library Manager

2. **Adafruit BME680 Library**
   - By: Adafruit
   - Version: 2.0.0 or later
   - Description: BME680 environmental sensor (temp, humidity, pressure, gas)
   - GitHub: https://github.com/adafruit/Adafruit_BME680
   - Installation: Search "Adafruit BME680" in Library Manager
   - Dependencies: Adafruit Unified Sensor, Adafruit BusIO

3. **Adafruit VL53L4CD**
   - By: Adafruit
   - Version: 1.0.0 or later
   - Description: VL53L4CD Time-of-Flight distance sensor
   - GitHub: https://github.com/adafruit/Adafruit_VL53L4CD
   - Installation: Search "Adafruit VL53L4CD" in Library Manager
   - Dependencies: Adafruit BusIO

4. **Servo**
   - Built-in with Arduino IDE
   - No installation needed
   - Description: Control SG90 servo motors

### Supporting Libraries (Auto-installed with above)

These are automatically installed as dependencies:

- **Adafruit Unified Sensor** (required by BME680)
- **Adafruit BusIO** (required by BME680 and VL53L4CD)
- **SPI** (built-in, for NRF24L01)
- **Wire** (built-in, for I2C sensors)

### ESP32-CAM Libraries

For ESP32-CAM programming, you need:

1. **ESP32 Board Support**
   - Add to Board Manager URLs:
     `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
   - File → Preferences → Additional Board Manager URLs
   - Tools → Board → Boards Manager → Search "ESP32" → Install

2. **ESP32 Camera Library**
   - Included with ESP32 board support
   - No separate installation needed

## Installation Instructions

### Method 1: Arduino IDE Library Manager (Recommended)

1. Open Arduino IDE
2. Go to **Tools → Manage Libraries** (or Ctrl+Shift+I)
3. Search for each library by name
4. Click "Install"
5. Install any dependencies when prompted

### Method 2: Manual Installation

1. Download library ZIP from GitHub
2. Arduino IDE → Sketch → Include Library → Add .ZIP Library
3. Select downloaded ZIP file
4. Restart Arduino IDE

### Method 3: Command Line (PlatformIO)

If using PlatformIO instead of Arduino IDE:

```ini
[env:uno]
platform = atmelavr
board = uno
framework = arduino
lib_deps =
    nRF24/RF24@^1.4.5
    adafruit/Adafruit BME680 Library@^2.0.0
    adafruit/Adafruit VL53L4CD@^1.0.0
    adafruit/Adafruit Unified Sensor
    adafruit/Adafruit BusIO

[env:esp32cam]
platform = espressif32
board = esp32cam
framework = arduino
```

## Verifying Installation

1. **Check Library Installation:**
   - Arduino IDE → Sketch → Include Library
   - Verify libraries appear in the list

2. **Test Compilation:**
   - Open `robot/main.ino`
   - Click "Verify" (checkmark icon)
   - Should compile without errors

3. **Check Examples:**
   - File → Examples
   - Look for RF24, Adafruit BME680, Adafruit VL53L4CD
   - Try running example sketches

## Version Compatibility

### Tested Configurations

**Arduino IDE:**
- Version 1.8.19 ✓
- Version 2.0.0+ ✓

**Library Versions:**
- RF24: 1.4.5, 1.4.6, 1.4.7 ✓
- Adafruit BME680: 2.0.0, 2.0.1+ ✓
- Adafruit VL53L4CD: 1.0.0+ ✓

**Board Versions:**
- Arduino AVR Boards: 1.8.3+ ✓
- ESP32 by Espressif: 2.0.0+ ✓

## Common Installation Issues

### Issue: Library not found during compilation

**Solution:**
- Ensure library is installed for correct Arduino installation
- Check spelling in `#include` statements
- Restart Arduino IDE after installation
- Check library compatibility with board

### Issue: Multiple library versions installed

**Solution:**
- Arduino IDE → Sketch → Include Library → Manage Libraries
- Look for libraries with version dropdowns
- Select latest stable version
- Uninstall old versions

### Issue: Dependency errors

**Solution:**
- Install all dependencies listed
- Update all Adafruit libraries together
- Use Library Manager to auto-install dependencies

### Issue: ESP32 board not found

**Solution:**
- Add ESP32 board URL to preferences
- Install ESP32 board support from Boards Manager
- Restart Arduino IDE
- Select "AI Thinker ESP32-CAM" from Tools → Board

## Updating Libraries

To update libraries to latest versions:

1. Open Library Manager (Tools → Manage Libraries)
2. Filter by "Updatable"
3. Update each library individually or select "Update All"
4. Test code after updates

**Note:** Major version updates may introduce breaking changes. Check library changelogs.

## Alternative Libraries

If you have issues with recommended libraries:

### RF24 Alternatives:
- RadioHead library (requires code changes)
- Mirf library (older, less maintained)

### BME680 Alternatives:
- BSEC library by Bosch (more features, larger)
- BME680-Arduino by Adafruit (older version)

### VL53L4CD Alternatives:
- VL53L0X library (different sensor model)
- VL53L1X library (different sensor model)

## Library Documentation Links

- **RF24**: https://nrf24.github.io/RF24/
- **Adafruit BME680**: https://learn.adafruit.com/adafruit-bme680-humidity-temperature-barometic-pressure-voc-gas
- **Adafruit VL53L4CD**: https://learn.adafruit.com/adafruit-vl53l4cd-time-of-flight-distance-sensor
- **Arduino Servo**: https://www.arduino.cc/reference/en/libraries/servo/

## Getting Help

If you encounter library issues:

1. Check library GitHub issues page
2. Verify Arduino IDE version compatibility
3. Test with example sketches first
4. Check Serial Monitor for error messages
5. Consult Arduino forums or project documentation

## License Information

All libraries have their own licenses (typically MIT or Apache 2.0). 
Check individual library repositories for license details.
