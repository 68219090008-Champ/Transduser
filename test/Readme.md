## นาย ทีรธร กาญจนวิวิญ

# Transduser

โปรเจคนี้เป็นระบบทดสอบการใช้งาน KY-025 Magnetic Reed Switch Sensor ร่วมกับ Arduino UNO และจอ LCD I2C 16x2

## วัตถุประสงค์
- อ่านสถานะแม่เหล็กจากโมดูล KY-025 (Digital Output)
- แสดงผลผ่าน Serial Monitor
- แสดงผลสถานะบนจอ LCD I2C 16x2
- เปิด/ปิด LED บนบอร์ด Arduino ตามการตรวจจับแม่เหล็ก

## ฮาร์ดแวร์
- Arduino UNO
- KY-025 Magnetic Reed Switch Sensor Module
- LCD 16x2 I2C (Address: `0x27`)
- สายไฟเชื่อมต่อ

## การต่อวงจร
### KY-025 กับ Arduino UNO
- `D0` (หรือ `DO`) → `D7`
- `VCC` → `5V`
- `GND` → `GND`

### LCD I2C กับ Arduino UNO
- `SDA` → `A4`
- `SCL` → `A5`
- Address LCD → `0x27`

### ตัวอย่างวงจรเชื่อมต่อ
```
Arduino UNO        KY-025            LCD I2C
-----------        -------           -------
5V  ------------>  VCC
GND ------------>  GND             GND
D7  ------------>  D0
                                 A4 (SDA) ---> SDA
                                 A5 (SCL) ---> SCL
```

### ไดอะแกรมสายต่อแบบง่าย
```
      +-----------------------------+
      |       Arduino UNO           |
      |                             |
      |   [A4] --- SDA ----------+   |
      |   [A5] --- SCL ----------+   |
      |   [D7] --- D0 (KY-025)       |
      |   [5V] --- VCC (KY-025)      |
      |   [GND] --- GND (KY-025)     |
      |                             |
      |   [GND] --- GND (LCD)        |
      |                             |
      +-----------------------------+
```

### หมายเหตุ
- บางโมดูล LCD อาจมี address ต่างกัน ถ้าไม่แสดงผลให้ตรวจสอบด้วย I2C scanner
- KY-025 ใช้ขา Digital เพื่ออ่านสถานะแม่เหล็กแบบ ON/OFF

## ซอฟต์แวร์
ไฟล์หลักของโครงการคือ `src/main.cpp`

### ไลบรารีที่ใช้
- `Wire` (สำหรับ I2C)
- `LiquidCrystal_I2C` (สำหรับจอ LCD)

### การตั้งค่า PlatformIO
ไฟล์ `platformio.ini` ใช้บอร์ด Arduino UNO และ Framework Arduino

```ini
[env:uno]
platform = atmelavr
board = uno
framework = arduino

lib_deps =
   adafruit/Adafruit Unified Sensor @ ^1.1.9
    marcoschwartz/LiquidCrystal_I2C @ ^1.1.4
```

## การใช้งาน
1. ต่อสายตามแผนผังด้านบน
2. เปิดโปรเจคใน PlatformIO
3. Build โดยใช้คำสั่ง `platformio run`
4. Upload โค้ดขึ้นบอร์ดโดยใช้คำสั่ง `platformio run --target upload`
5. เปิด Serial Monitor ที่ความเร็ว `9600`

## ผลลัพธ์
เมื่อมีแม่เหล็กเข้าใกล้ KY-025
- LED บนบอร์ด Arduino จะติด
- ข้อความบนจอ LCD จะแสดง `Magnet: YES`
- Serial Monitor จะแสดงสถานะ `Digital=1 | Magnet=YES`

เมื่อไม่มีแม่เหล็ก
- LED จะดับ
- LCD จะแสดง `Magnet: NO`
- Serial Monitor จะแสดงสถานะ `Digital=0 | Magnet=NO`

## เอกสารอ้างอิงเพิ่มเติม
- `test/design.md` สำหรับการเชื่อมต่อฮาร์ดแวร์
- `src/main.cpp` สำหรับโค้ดการทำงาน
- `platformio.ini` สำหรับการตั้งค่าโปรเจคบน PlatformIO
