# 🤖 embedded_ml_eiq – Embedded Machine Learning with NXP eiQ on i.MX RT1052

This repository contains the implementation of an **embedded machine learning system** using the **eiQ Time Series platform** on the **NXP i.MX RT1052** development board. The project demonstrates how to capture real-world data from an external **MPU6050 accelerometer**, train classification or anomaly detection models, and deploy them directly on a microcontroller.

---

## 🧠 Project Objective

The main goal is to implement a complete ML pipeline on an embedded device:

1. **Data acquisition** using the i.MX RT1052 and MPU6050.
2. **Preprocessing and training** using NXP's eiQ Time Series tool.
3. **Model deployment** back to the device for real-time inference.

This example is tailored for applications involving vibration analysis, fault detection, or other inertial signal classification tasks.

---
## 🛠️ Project Structure

| Path / File                      | Description                                       |
|----------------------------------|---------------------------------------------------|
| `source/`                        | Main application source code                      |
| `source/lib/`                    | Contains the deployed ML model (`libtss.a`)       |
| `board/`                         | Hardware initialization files (pins, clocks, etc.)|
| `eiq_models/`                    | CSV datasets and model training exports           |
| `scripts/`                       | Optional Python scripts for data analysis         |
| `README.md`                      | This file                                         |
| `nxp_embedded_machine_learning.mex` | MCUXpresso config file for board setup         |

---

## 🧪 Development Workflow

### 1. Data Logging

- Firmware captures 5 seconds of 3-axis acceleration data at 1 kHz.
- Each session generates a file like `ACCELE_x.csv` on the SD card.

### 2. Model Training (eiQ Time Series)

- Select **Classification** or **Anomaly Detection**.
- Use `.csv` files to train and benchmark models.
- The tool recommends the best model based on accuracy and memory footprint.

### 3. Deployment

- Export the trained model as a static library `libtss.a`.
- Copy it to `source/lib/` and rebuild the firmware in MCUXpresso.
- Run real-time inference using Tera Term (Option 1).

---

## 🔧 Tools & Requirements

- **MCUXpresso IDE**  
- **NXP i.MX RT1052 EVK Board**  
- **MPU6050 Accelerometer** (via I²C)  
- **eiQ Time Series Tool**  
- **Tera Term or any serial terminal**  
- **Oscilloscope** (optional, for debugging/validation)

> **Sensor Pin Mapping** (external MPU6050):

| Signal | Header | Pin |
|--------|--------|-----|
| VCC    | J24    | 8   |
| GND    | J24    | 7   |
| INT    | J22    | 8   |
| SDA    | J23    | 9   |
| SCL    | J23    | 8   |

---

**📍 Pin Location on the Board:**  
<p align="center">
  <img src="https://github.com/jvmreis/nxp_embedded_machine_learning/blob/develop/documents/hardware_pin_out.png" width="50%">
</p>

## 🚀 How to Run

1. Clone the repo:
   ```bash
   git clone https://github.com/jvmreis/nxp_embedded_machine_learning.git
   ```
2. Open in MCUXpresso:  
   `File > Import Project from File System`
3. Flash firmware to board.
4. Open Tera Term @ `115200 baud`:
   - **Option 1** → Run model inference
   - **Option 2** → Clear SD card
   - **Option 3** → Capture new signal
5. Use eiQ to train and export the model.
6. Place `libtss.a` into `source/lib/`, rebuild, and flash.

---

## 📊 Example Output

During real-time inference, the model compares live acceleration input with learned patterns and prints a **match score (%)** via the serial terminal.

---

## 📖 Documentation

A full technical lab report is available in PDF and Markdown formats, including:
- **[eiQ time series guide ](https://github.com/jvmreis/nxp_interrupt_lesson/blob/main/documents/Embedded%20Machine%20Learning%20Implementation%20Using%20eiQ.pdf)**
  - **[Schematic diagrams ](https://github.com/jvmreis/nxp_interrupt_lesson/blob/main/documents/imxrt1050evkb_schematic.pdf)**
- **[MPU-6050 Register Map](https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf)**
---

## 📄 License

This project is licensed for **educational purposes only**.
