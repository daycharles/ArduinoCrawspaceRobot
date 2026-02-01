# Component Mounts

This directory contains STL files for mounting various components to the chassis.

## Files

### Motor Mounts
- **motor_mount_left_front.stl** - Left front motor mount
- **motor_mount_left_rear.stl** - Left rear motor mount
- **motor_mount_right_front.stl** - Right front motor mount
- **motor_mount_right_rear.stl** - Right rear motor mount

### Sensor Mounts
- **distance_sensor_mount.stl** - VL53L4CD front-facing mount
- **environmental_sensor_mount.stl** - BME688 sensor holder

### Electronics Mounts
- **arduino_uno_mount.stl** - Arduino Uno mounting bracket with standoffs
- **l298n_mount.stl** - L298N motor driver mounting bracket
- **nrf24_mount.stl** - NRF24L01 module holder
- **power_converter_mount.stl** - 5V step-down converter mount
- **battery_strap_holder.stl** - Battery retention clips (2 pieces)

### Camera Mount
- **esp32cam_mount.stl** - ESP32-CAM adjustable angle mount
- **camera_tilt_bracket.stl** - Optional tilt mechanism

## Print Settings

**Recommended Settings:**
- Layer Height: 0.2mm
- Infill: 25-40%
- Supports: Minimal (mostly flat prints)
- Material: PLA or PETG
- Nozzle: 0.4mm

**Print Time:** Approximately 8-12 hours total for all mounts

## Assembly Notes

### Motor Mounts
- Print 4 copies (one for each corner)
- Use M3 screws to attach motors
- Secure to chassis with M3 screws and nuts
- Ensure motor shafts align with tread sprockets

### Sensor Mounts
- Distance sensor should face forward, perpendicular to ground
- Environmental sensor needs airflow but dust protection
- Use M2 screws or hot glue to secure sensors

### Electronics Mounts
- Arduino mount uses 10mm standoffs (built-in or separate M3 standoffs)
- Ensure USB port remains accessible
- L298N mount should allow heatsink ventilation
- NRF24 mount keeps module away from motors (reduce EMI)

## Hardware Required

- M3 screws: 8mm, 12mm, 16mm lengths (quantity: ~40 total)
- M3 nuts (quantity: ~40)
- M2 screws: 6mm, 8mm (quantity: ~10)
- Optional: M3 standoffs for Arduino (if not using integrated)

## Compatibility

- Designed for 130 size DC motors (3-6V)
- Arduino Uno R3 footprint
- Standard L298N module
- SG90 servo size (can adapt for larger servos)

## Modifications

Adjust hole positions if using different:
- Motor sizes
- Board variants
- Component dimensions

## Notes

- Some mounts may need support material
- Test fit before gluing/permanent mounting
- Can be reprinted individually if damaged
- Consider printing spares for critical mounts
