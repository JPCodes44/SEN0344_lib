## 📦 `SEN0344` Arduino Library

A lightweight and efficient Arduino library for reading SpO₂ (blood oxygen saturation) data from the **DFRobot SEN0344** sensor over I²C.
Supports continuous data streaming with **Red** and **Infrared** photodiodes.

---

## ⚙️ Features

* 📡 Communicates via **I²C**
* ❤️ Retrieves **Red/IR data pairs** from sensor FIFO
* 🔁 Enables **FIFO rollover** for continuous data capture
* 🧠 Outputs **raw ratio** (`Red / IR`) for SpO₂ calculation

---

## 🛠️ Installation

### 🔧 Option 1: Manually

1. 📁 Copy both files into your Arduino project:

   * [`SEN0344.cpp`](./SEN0344.cpp)
   * [`SEN0344.h`](./SEN0344.h)

2. At the top of your `.ino` sketch, include the library:

```cpp
#include "SEN0344.h"
```

### 🔧 Option 2: Create a Library Folder

1. In your Arduino `libraries/` directory, create a new folder called `SEN0344`.
2. Drop `SEN0344.cpp` and `SEN0344.h` into that folder.
3. Restart the Arduino IDE.

---

## 🧪 Example Usage

```cpp
#include <Wire.h>
#include "SEN0344.h"

SEN0344 sensor(0x47); // 0x47 or 0x48 based on your hardware config

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  if (sensor.begin()) {
    Serial.println("SEN0344 initialized ✅");
  } else {
    Serial.println("SEN0344 failed to initialize ❌");
  }
}

void loop() {
  float ratio = sensor.readSpo2();
  Serial.print("SpO2 Ratio: ");
  Serial.println(ratio, 4); // Optional: multiply by coefficient if calibrating to %
  delay(500);
}
```

---

## 🔍 How It Works

### 🔧 `begin()`

* Sets FIFO rollover
* Enables SpO₂ mode with Red & IR LEDs
* Configures 3200 samples/sec for high responsiveness

### 📤 `readSpo2()`

* Reads 6 bytes from FIFO (3 bytes per channel)
* Extracts raw 24-bit values for:

  * Red LED
  * Infrared LED
* Returns the **Red / IR ratio** (float)

### 🧱 Low-Level I²C Tools

* `i2c_write(addr, byte, deviceID)`
* `i2c_read(addr, deviceID)`

---

## 🧼 Tips

* Make sure `Wire.begin()` is called in `setup()`
* Sensor I²C address is **usually 0x47** but can be **0x48** — check your device
* To convert the Red/IR ratio into a real SpO₂ %, you'll need to apply a calibration curve (device/skin dependent)

---

## 🧪 Tested On

* ✅ Arduino Uno
* ✅ Arduino Nano
* ✅ ESP32 (with 3.3V logic)
* ✅ DFRobot SEN0344 (MAX30102)

---

## 📄 License

MIT License — free to use, modify, and distribute.
Go build something awesome. 🚀

---
