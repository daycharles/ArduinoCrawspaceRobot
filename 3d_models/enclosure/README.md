# Electronics Enclosure

This directory contains STL files for the main electronics enclosure that protects components from dust and debris in crawlspaces.

## Files

### Main Enclosure
- **enclosure_base.stl** - Bottom plate with mounting points
- **enclosure_top.stl** - Top cover with ventilation holes
- **enclosure_walls.stl** - Side walls (4 pieces)

### Access Panels
- **usb_access_panel.stl** - Provides access to Arduino USB port
- **wire_pass_panel.stl** - Panel with cable pass-through slots

### Accessories
- **cable_gland_20mm.stl** - Cable entry point (print 2-4)
- **snap_clips.stl** - Quick-release clips for top cover (4 pieces)
- **ventilation_grille.stl** - Additional ventilation option

## Print Settings

**Recommended Settings:**
- Layer Height: 0.2-0.3mm
- Infill: 15-20% (walls), 30% (clips)
- Supports: Yes (for top cover vent holes)
- Material: PLA, PETG, or ASA (ASA for higher temperature resistance)
- Nozzle: 0.4mm

**Print Time:** Approximately 15-20 hours total

## Dimensions

- Internal space: 200mm x 150mm x 80mm (L x W x H)
- Wall thickness: 3mm
- Ventilation holes: 5mm diameter, multiple locations

## Assembly Instructions

1. **Base Installation:**
   - Attach base to chassis with M3 screws
   - Position Arduino, L298N, and other electronics inside
   - Route wires through cable pass-throughs

2. **Cable Management:**
   - Install cable glands in designated holes
   - Route motor wires, sensor cables through glands
   - Keep wire slack inside enclosure

3. **Top Cover:**
   - Align top cover with base
   - Secure with snap clips or M3 screws
   - Ensure USB access panel aligns with Arduino

4. **Ventilation:**
   - Don't block ventilation holes
   - Ensure L298N heatsink has airflow
   - Add grille if dust is excessive

## Features

- **Dust Protection:** Enclosed design keeps crawlspace dust out
- **Ventilation:** Multiple vent holes prevent overheating
- **Access Ports:** Easy Arduino programming without disassembly
- **Cable Management:** Organized wire routing
- **Modular:** Individual panels for easy repairs/modifications

## Hardware Required

- M3 x 12mm screws (quantity: 12)
- M3 nuts (quantity: 12)
- Optional: Rubber grommets for cable glands
- Optional: Small fan (40mm) for active cooling

## Modifications

**Suggested Customizations:**
- Drill additional holes for specific cable routing
- Add internal cable tie mounting points
- Install status LED window
- Add larger ventilation fan mount
- Integrate switch/button access

## Notes

- Print walls in orientation shown for strength
- Test snap clips fit before full assembly
- Consider TPU for cable glands (flexible fit)
- May need to sand USB access port for alignment
- Clear/translucent filament allows LED visibility

## Waterproofing (Optional)

While designed for dry crawlspaces, you can add:
- Rubber gasket material around edges
- Silicone sealant at cable entry points
- IP-rated cable glands
- Conformal coating on PCBs

**Note:** This is not a fully sealed waterproof enclosure.

## Maintenance Access

- Top cover removes completely
- USB panel slides out for programming
- Individual wall panels for component access
- Design allows full disassembly without tools

## Material Recommendations

- **PLA:** Easy to print, adequate for <40°C environments
- **PETG:** Better temperature and impact resistance
- **ASA:** Best for higher temperatures, UV resistant
- **ABS:** Good strength, requires heated bed

Choose material based on expected crawlspace conditions.
