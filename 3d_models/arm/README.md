# 3D Printed Robotic Arm Components

This directory contains STL files for the 2-DOF (2 Degree of Freedom) robotic arm.

## Files

### Base Components
- **arm_base.stl** - Base mount for the base servo (attaches to chassis)
- **servo_base_holder.stl** - Holds SG90 servo for base rotation

### Arm Segments  
- **lower_arm.stl** - Lower arm segment (connects to base servo horn)
- **upper_arm.stl** - Upper arm segment (connects to arm servo)
- **servo_arm_holder.stl** - Holds SG90 servo for arm joint

### End Effector (Optional)
- **gripper_base.stl** - Simple gripper attachment point
- **gripper_finger_left.stl** - Left gripper finger
- **gripper_finger_right.stl** - Right gripper finger

## Print Settings

**Recommended Settings:**
- Layer Height: 0.2mm
- Infill: 20-30%
- Supports: Yes (for servo holders)
- Material: PLA or PETG
- Nozzle: 0.4mm

**Print Time:** Approximately 6-8 hours total

## Assembly Notes

1. Print all components with servo mounting holes facing up for best quality
2. Use support material for overhanging servo holder areas
3. Test fit servos before full assembly
4. May require light sanding for servo fit
5. Attach servo horns with provided servo screws
6. Use M2 screws to secure servos to holders

## Hardware Required

- 2x SG90 Servo Motors (or compatible 9g servos)
- 4x M2 x 8mm screws (servo mounting)
- 2x M3 x 12mm screws (arm segments)
- 2x M3 nuts
- Servo horns (included with servos)

## Dimensions

- Base diameter: ~60mm
- Lower arm length: ~80mm
- Upper arm length: ~60mm
- Total reach: ~140mm (extended)

## Notes

- Design allows 180° rotation at base
- Arm joint has ~180° range of motion
- Load capacity: ~50g at full extension (with SG90 servos)
- Consider metal gear servos for heavier loads
- Can be scaled in slicer (maintain aspect ratio)

## Modifications

Feel free to modify these designs for your needs:
- Lengthen/shorten arm segments
- Add camera mount to end effector
- Integrate sensor holders
- Add cable management clips

## License

These 3D models are provided as-is for the Arduino Crawlspace Robot project.
