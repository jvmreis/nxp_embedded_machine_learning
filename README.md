
# 🤖 Embedded Machine Learning with NXP eiQ on i.MX RT1052

This repository contains the implementation of an embedded machine learning system using the eiQ Time Series platform on the NXP i.MX RT1052 development board. The project demonstrates how to capture real-world data from both an external MPU6050 accelerometer and the onboard microphone, train classification or anomaly detection models, and deploy them directly on a microcontroller.

---

## 🧠 Project Objective

The main goal is to implement a complete ML pipeline on an embedded device:

1. **Data acquisition** using the i.MX RT1052 and MPU6050.
2. **Preprocessing and training** using NXP's eiQ Time Series tool.
3. **Model deployment** back to the device for real-time inference.

This example is tailored for applications involving vibration and sound analysis, fault detection, or signal classification tasks.

---

## 🛠️ Project Structure

Path / File                      | Description
----------------------------------|---------------------------------------------------
source/                           | Main application source code
source/lib/                       | Contains the deployed ML model (libtss.a)
board/                            | Hardware initialization files (pins, clocks, etc.)
eiq_models/                       | CSV datasets and model training exports
scripts/                          | Optional Python scripts for data analysis
README.md                         | This file
nxp_embedded_machine_learning.mex | MCUXpresso config file for board setup

---

## 🧪 Development Workflow

### 1. Data Logging
- Firmware captures 5 seconds of:
  - 3-axis acceleration data at 1 kHz
  - Audio data at 16 kHz, 16-bit (mono)
- Files are saved as .csv (and .wav for audio) on the SD card.

### 2. Model Training (eiQ Time Series)
- Select Classification or Anomaly Detection.
- Upload .csv files to train and benchmark models.
- The tool recommends the best model based on accuracy and memory footprint.

### 3. Deployment
- Export the trained model as a static library libtss.a.
- Copy it to source/lib/ and rebuild the firmware in MCUXpresso.
- Use Tera Term UART Menu to test the embedded model:
  - Option 1 → Run anomaly detection
  - Option 2 → Run classification
  - Option 3 → Clear SD card
  - Option 4 → Record accelerometer data
  - Option 5 → Record microphone data

## 🛠️ Signal Input Selection
In machine_learning.c, you can select the signal source (acc_sample_data() or mic_sample_data()) for each model. By default:
- Anomaly detection uses accelerometer
- Classification uses microphone

---

## 🔧 Tools & Requirements

- MCUXpresso IDE
- NXP i.MX RT1052 EVK Board
- MPU6050 Accelerometer (via I²C)
- eiQ Time Series Tool
- Tera Term or any serial terminal
- Oscilloscope (optional, for debugging/validation)

Sensor Pin Mapping (external MPU6050):

Signal | Header | Pin
-------|--------|----
VCC    | J24    | 8
GND    | J24    | 7
INT    | J22    | 8
SDA    | J23    | 9
SCL    | J23    | 8

---

**📍 Pin Location on the Board:**  
<p align="center">
  <img src="https://github.com/jvmreis/nxp_embedded_machine_learning/blob/develop/documents/hardware_pin_out.png" width="50%">
</p>

---

## 🚀 How to Run

1. Clone the repo:

```bash
git clone https://github.com/jvmreis/nxp_embedded_machine_learning.git
```   

2. Open in MCUXpresso:
   File > Import Project from File System

3. Place your trained libtss.a in source/lib/

4. Configure the project to link the precompiled libtss.a library:
 - The libtss.a file generated during the Deployment phase in eiQ Time Series
 must be correctly linked into your firmware project. Follow the steps below:
 - Right-click on the project in the Project Explorer, then select Properties.
 - Navigate to:
C/C++ Build > Settings > MCU Linker > Libraries
 - In "Libraries (-l)", add: libtss (without the .a extension and without the ~lib prefix):
```bash
tss
``` 
 - In "Library search path (-L)", add:
```bash
${workspace_loc:/${ProjName}/source/lib}
```


5. Build and flash the firmware.

6. Connect via Tera Term @ 115200 baud:

   1. Anomaly detection embedded Machine Learning Model
   2. Classification embedded Machine Learning Model
   3. Exclude files
   4. Record to SDcard Ext Accelerometer Data
   5. Record to SDcard Microphone Data
   6. Quit

---

## 📊 Example Output

1. Real-time results are shown via the UART terminal. For example:

- Anomaly detection:
- anomaly detection 0.954  // 95.4% match to learned pattern

2. Classification (microphone):
- class[0] 0.0 class[1] 0.0 class[2] 1.0 class[3] 0.0 class[4] 0.0

## 🎯 Default Classification Model Frequencies:
- class[0] → 4000 Hz
- class[1] → 2000 Hz
- class[2] → 1780 Hz
- class[3] → 860 Hz
- class[4] → 244 Hz

---

## 📖 Documentation

A full technical lab report is available in PDF and Markdown formats, including:
- **[eiQ time series guide ](https://github.com/jvmreis/nxp_embedded_machine_learning/blob/main/documents/Embedded%20Machine%20Learning%20Implementation%20Using%20eiQ.pdf)**
- **[Schematic diagrams ](https://github.com/jvmreis/nxp_interrupt_lesson/blob/main/documents/imxrt1050evkb_schematic.pdf)**
- **[MPU-6050 Register Map](https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf)**
---

## 📄 License

This project is licensed for **educational purposes only**.