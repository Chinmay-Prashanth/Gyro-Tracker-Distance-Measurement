# GyroTracker - PlatformIO Setup Guide

## Quick Start

### 1. Prerequisites
- Install [PlatformIO IDE](https://platformio.org/platformio-ide) or [PlatformIO Core](https://platformio.org/install/cli)
- STM32F429I Discovery Board
- USB cable for programming

### 2. Project Setup
```bash
# Clone the repository
git clone <repository-url>
cd distance_recording_proj

# Open in PlatformIO
pio project init --ide vscode  # For VSCode
# OR
# Open the folder in PlatformIO IDE
```

### 3. Building the Project

#### Main Application (Distance Measurement)
```bash
# Build the main application
pio run -e disco_f429zi

# Upload to board
pio run -e disco_f429zi -t upload

# Monitor serial output
pio device monitor -e disco_f429zi
```

#### Calibration Program
```bash
# Build calibration program
pio run -e calibration

# Upload calibration program
pio run -e calibration -t upload

# Monitor calibration output
pio device monitor -e calibration
```

### 4. Usage Workflow

1. **First Time Setup**:
   - Connect STM32F429I Discovery board
   - Flash the calibration program
   - Keep the board stationary during calibration
   - Note the calibration offset value

2. **Distance Measurement**:
   - Flash the main application
   - Mount the board on the right side of your knee
   - Walk normally and observe real-time distance on LCD

### 5. Project Structure
```
distance_recording_proj/
├── src/
│   ├── main.cpp                 # Main distance measurement application
│   └── Calib_trail.cpp         # Calibration program
├── lib/
│   └── drivers/                # STM32F429I Discovery drivers
│       ├── LCD_DISCO_F429ZI.h  # LCD display driver
│       ├── l3gd20.h           # L3GD20 gyroscope driver
│       └── [other drivers]
├── media/
│   ├── images/                 # Test result images
│   └── videos/                 # Demo videos
├── platformio.ini              # PlatformIO configuration
├── README.md                   # Project documentation
└── SETUP_GUIDE.md             # This file
```

### 6. Hardware Connections

The STM32F429I Discovery board has built-in:
- L3GD20 gyroscope (connected via SPI)
- LCD display (ILI9341 controller)
- All necessary connections are already made on the board

**No additional wiring required!**

### 7. Troubleshooting

#### Build Issues
- Ensure all drivers are in `lib/drivers/` directory
- Check that `platformio.ini` includes the correct build flags
- Verify STM32 platform is installed: `pio platform install ststm32`

#### Upload Issues
- Check USB cable connection
- Verify ST-Link drivers are installed
- Try different USB port
- Press reset button on board before upload

#### Runtime Issues
- Ensure board is properly calibrated first
- Check serial monitor for debug output
- Verify gyroscope is working: `pio device monitor`

### 8. Advanced Configuration

#### Modifying Sampling Rate
In `src/main.cpp`, line ~205:
```cpp
t.attach(&setFlag, 0.05);  // Change 0.05 to desired interval
```

#### Adjusting Motion Threshold
In `calculateDistance3()` function:
```cpp
if(abs(tempData) > 3000) {  // Change 3000 to desired threshold
```

#### Calibration Settings
In `src/Calib_trail.cpp`:
```cpp
if (iter == 4000){  // Change 4000 for different calibration duration
```

### 9. Alternative IDEs

#### VSCode with PlatformIO Extension
1. Install PlatformIO extension
2. Open folder in VSCode
3. Use PlatformIO toolbar for build/upload

#### CLion with PlatformIO Plugin
1. Install PlatformIO plugin
2. Import as PlatformIO project
3. Configure build targets

### 10. Serial Monitor Commands

The project outputs real-time distance measurements:
```
Distance: 1 meters
Distance: 2 meters
Distance: 3 meters
...
```

Monitor baud rate: 9600 bps

---

## Need Help?

- Check [PlatformIO Documentation](https://docs.platformio.org/)
- Review STM32F429I [Discovery Board Manual](https://www.st.com/en/evaluation-tools/32f429idiscovery.html)
- See project [README.md](README.md) for technical details 