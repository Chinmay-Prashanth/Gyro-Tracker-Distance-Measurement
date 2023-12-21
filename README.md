# GyroTracker: Real-Time GPS-Free Distance Measurement System
**Real Time Embedded Systems - Fall 2023 Term Project**

## 🏆 Project Achievement
**Final Score: 100/100** 🎉

![Score Card](media/images/score%20card.jpeg)

## Team Members - Group 49
- **Alston Shi** - as13388
- **Chinmay Prashanth** - cp3873  
- **Leshan Wang** - lw3423

> **Note**: This project was developed as a collaborative team effort for the Real Time Embedded Systems course. While we worked together on the design and implementation, each team member maintains their individual repository for academic purposes.

## 🎯 Project Overview

This project implements an innovative wearable speedometer that calculates distance traveled without relying on GPS. Instead, it uses a built-in L3GD20 gyroscope to measure three-axis angular velocity, which is then converted to linear distance through advanced processing algorithms.

### Key Features
- 📱 **GPS-Free Operation** - Works indoors and in GPS-denied environments
- 🔧 **Advanced Calibration** - Eliminates sensor drift for accurate measurements
- 📊 **Real-time Display** - Shows distance on STM32 board LCD
- ⚡ **Power Efficient** - Lower power consumption than GPS-based solutions
- 🏃 **Wearable Design** - Mounts on leg/foot for natural movement tracking

## 🔧 Technical Specifications

### Hardware
- **Microcontroller**: STM32F429I Discovery Board
- **Gyroscope**: L3GD20 (3-axis angular velocity sensor)
- **Display**: Built-in LCD with custom drivers
- **Communication**: SPI protocol at 100kHz
- **Sampling Rate**: 20Hz (0.05s intervals)

### Sensor Configuration
- **Sensitivity**: 8.75 mdps/digit (245 dps full scale)
- **Primary Axis**: Z-axis for leg movement detection
- **Mounting**: Side of knee for optimal motion capture

## 📐 Methodology

### Distance Calculation Algorithm
Our core algorithm converts angular velocity to linear distance using the arc formula:

```
Distance = (2 × π × leg_length / 360) × reading × sampling_frequency × sensitivity
```

**Parameters:**
- `leg_length`: 1.015 meters (assumed average)
- `reading`: Real-time Z-axis gyroscope data
- `sampling_frequency`: 0.05 seconds
- `sensitivity`: 8.75 mdps/digit (from L3GD20 datasheet)

### Three Implementation Methods

#### Method 1: Batch Processing
- Collects data over 30-second intervals
- Processes entire dataset for distance calculation
- Best for accuracy over longer periods

#### Method 2: Step Counting
- Detects individual steps using threshold values
- Multiplies step count by average stride length
- Simple but effective for basic distance tracking

#### Method 3: Real-time Calculation (Primary Method)
- Calculates distance continuously during movement
- Provides instant feedback on LCD display
- Used for all demonstrations and testing

## 🎯 Calibration System

Our calibration process eliminates sensor drift and improves accuracy:

1. **Data Collection**: 4000 stationary readings from gyroscope
2. **Offset Calculation**: Computes average of stationary data
3. **Drift Compensation**: Applies offset to all subsequent measurements
4. **Validation**: Proven to significantly improve measurement accuracy

```cpp
// Calibration function
double calibration(){
  double total = 0;
  for (int i = 0; i < 4000; i++){
    total += dataSet[i];
  }
  return total / 4000;  // Average offset
}
```

## 📊 Testing Results

### Test 1: 8 Meters
**Initial Testing Video**
- **Video**: [`8 meters testing.mp4`](media/videos/8%20meters%20testing.mp4)
- **Purpose**: Proof of concept and basic functionality verification
- **Result**: Successful distance detection and real-time display

### Test 2: 20 Meters
**Comprehensive Accuracy Testing**

#### Test Setup Documentation:
1. **Actual Measurement 1**: ![Actual Measured 1](media/images/actual%20measured%201.png)
2. **Actual Measurement 2**: ![Actual Measured 2](media/images/actual%20measured%202.png)
3. **Conversion to Meters**: ![Actual Converted](media/images/actual%20converted.png)
4. **LCD Display Output**: ![Output in LCD](media/images/output%20in%20lcd.png)

#### Test Results:
- **Video**: [`20_meters_video.mp4`](media/videos/20_meters_video.mp4)
- **Actual Distance**: 20 meters (converted from inch measurements)
- **Measured Distance**: Displayed on LCD screen
- **Accuracy**: High correlation between actual and measured distance

## 🚀 Getting Started

### Prerequisites
- STM32F429I Discovery Board
- L3GD20 Gyroscope (built-in)
- PlatformIO IDE
- STM32 development environment

### PlatformIO Setup
1. Clone this repository
2. Open in PlatformIO
3. Build and upload to STM32F429I board

📋 **For detailed setup instructions, see [SETUP_GUIDE.md](SETUP_GUIDE.md)**

### Project Structure
```
distance_recording_proj/
├── src/
│   ├── main.cpp                 # Main implementation
│   └── Calib_trail.cpp         # Calibration program
├── lib/
│   └── drivers/                # STM32 and LCD drivers
├── platformio.ini              # PlatformIO configuration
└── README.md                   # This file
```

### Usage Instructions
1. **Calibration**: Run calibration program first while sensor is stationary
2. **Mounting**: Attach sensor to right side of knee
3. **Operation**: Walk normally while system calculates distance
4. **Display**: View real-time distance on LCD screen

## 🔧 Code Structure

### Key Functions
- `setMode()`: Configures gyroscope SPI communication
- `readData()`: Reads angular velocity data from Z-axis
- `calculateDistance3()`: Real-time distance calculation
- `calibration()`: Sensor offset calibration
- LCD display functions for real-time visualization

### SPI Communication
```cpp
// Initialize SPI for gyroscope
spi.format(8,3);
spi.frequency(100000);
```

## 🎮 Implementation Details

### Motion Detection
- **Threshold**: ±3000 for motion detection
- **Filtering**: Eliminates noise and false readings
- **Processing**: Converts angular velocity to linear distance

### Display System
- **Real-time Updates**: 20Hz refresh rate
- **User Interface**: Clear distance display in meters
- **Visual Feedback**: Immediate response to movement

## 🏆 Project Achievements

✅ **Successful GPS-free distance measurement**  
✅ **Real-time processing and display**  
✅ **Advanced calibration system**  
✅ **Multiple calculation methods implemented**  
✅ **Comprehensive testing and validation**  
✅ **Indoor/outdoor versatility**  
✅ **Power-efficient operation**

## 🔮 Applications

- **Fitness Tracking**: Indoor gym workouts and running
- **Rehabilitation**: Physical therapy progress monitoring  
- **Industrial**: Worker movement tracking in GPS-denied areas
- **Sports**: Performance analysis for athletes
- **Research**: Gait analysis and biomechanics studies

## 📚 Technical Documentation

### Sensor Specifications
- **L3GD20 Gyroscope**: 3-axis angular rate sensor
- **Full Scale**: ±245/±500/±2000 dps
- **Sensitivity**: 8.75 mdps/digit (245 dps setting)
- **Interface**: SPI/I2C compatible

### Mathematical Foundation
The system leverages the relationship between angular velocity and linear motion through the arc length formula, accounting for human gait biomechanics and leg geometry.

---

**Course**: Real Time Embedded Systems  
**Semester**: Fall 2023  
**Achievement**: 100/100 Final Score 