# ออกแบบวิธีการทดสอบ Sensor KY-025 ให้แสดงผลที่ Serial Monitor

## วัตถุประสงค์

ออกแบบการทดสอบ Sensor KY-025 Magnetic Reed Switch Module ร่วมกับ Arduino UNO เพื่ออ่านค่าสถานะการตรวจจับแม่เหล็ก แล้วแสดงผลผ่าน Serial Monitor โดยใช้ทั้งสัญญาณแบบ Digital และ Analog

การทดสอบนี้ช่วยให้เข้าใจว่า Sensor ตอบสนองอย่างไรเมื่อมีแม่เหล็กเข้าใกล้หรือออกห่าง และสามารถตรวจสอบได้ว่าโมดูลต่อวงจรถูกต้องหรือไม่

## อุปกรณ์ที่ใช้

| อุปกรณ์ | จำนวน | หมายเหตุ |
| --- | --- | --- |
| Arduino UNO R3 | 1 บอร์ด | ใช้เป็นไมโครคอนโทรลเลอร์หลัก |
| KY-025 Magnetic Reed Switch Sensor | 1 ตัว | Sensor ตรวจจับแม่เหล็ก |
| แม่เหล็ก | 1 ชิ้น | ใช้ทดสอบการตรวจจับ |
| สาย Jumper | 4 เส้น | ใช้ต่อวงจร |
| คอมพิวเตอร์ | 1 เครื่อง | ใช้เปิด Serial Monitor |
| สาย USB | 1 เส้น | ใช้อัปโหลดโปรแกรมและจ่ายไฟให้ Arduino |

## ภาพประกอบ Sensor

![KY-025 Magnetic Reed Sensor](https://sensorkit.joy-it.net/files/files/sensors/KY-025/KY-025.png)

## หลักการทดสอบ

KY-025 ใช้ Reed Switch ตรวจจับสนามแม่เหล็ก เมื่อมีแม่เหล็กเข้าใกล้ หน้าสัมผัสภายใน Reed Switch จะเปลี่ยนสถานะ ทำให้ค่าที่อ่านจากขา `D0` เปลี่ยนเป็น `HIGH` หรือ `LOW`

ขา `A0` สามารถอ่านค่าแรงดันผ่านขา Analog ของ Arduino ได้ โดยค่าที่แสดงใน Serial Monitor จะอยู่ในช่วง `0` ถึง `1023` แต่เนื่องจาก Reed Switch เป็นอุปกรณ์แบบเปิด/ปิด ค่า Analog จึงมักเปลี่ยนเป็นระดับหลัก ๆ ไม่ได้เป็นค่าความแรงแม่เหล็กแบบละเอียด

## การต่อวงจร

| ขา KY-025 | ต่อกับ Arduino UNO | หน้าที่ |
| --- | --- | --- |
| `+` หรือ `VCC` | `5V` | จ่ายไฟให้ Sensor |
| `G` หรือ `GND` | `GND` | กราวด์ร่วม |
| `D0` หรือ `DO` | `D3` | อ่านค่าสัญญาณ Digital |
| `A0` หรือ `AO` | `A0` | อ่านค่าสัญญาณ Analog |

![KY-025 Pinout](https://sensorkit.joy-it.net/files/files/sensors/KY-025/KY-025.svg)

## ขั้นตอนการทดสอบ

1. ต่อสาย KY-025 เข้ากับ Arduino UNO ตามตารางการต่อวงจร
2. เชื่อมต่อ Arduino UNO กับคอมพิวเตอร์ผ่านสาย USB
3. เปิดโปรเจกต์ใน PlatformIO หรือ Arduino IDE
4. อัปโหลดโค้ดทดสอบลงบอร์ด Arduino UNO
5. เปิด Serial Monitor และตั้ง Baud Rate เป็น `9600`
6. นำแม่เหล็กเข้าใกล้ Sensor แล้วสังเกตค่าที่แสดงใน Serial Monitor
7. นำแม่เหล็กออกห่างจาก Sensor แล้วสังเกตการเปลี่ยนแปลงของค่า
8. ถ้าค่า Digital ไม่เปลี่ยน ให้ปรับ Potentiometer บนโมดูล KY-025 ช้า ๆ แล้วทดสอบใหม่

## โค้ดทดสอบสำหรับ Serial Monitor

```cpp
#include <Arduino.h>

const int digitalPin = 3;
const int analogPin = A0;
const int ledPin = LED_BUILTIN;

void setup() {
  pinMode(digitalPin, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
  Serial.println("KY-025 Sensor Test");
  Serial.println("Move a magnet near the sensor.");
}

void loop() {
  int digitalValue = digitalRead(digitalPin);
  int analogValue = analogRead(analogPin);

  digitalWrite(ledPin, digitalValue);

  Serial.print("Digital = ");
  Serial.print(digitalValue);
  Serial.print(" | Analog = ");
  Serial.print(analogValue);
  Serial.print(" | Status = ");

  if (digitalValue == HIGH) {
    Serial.println("Magnet detected");
  } else {
    Serial.println("No magnet");
  }

  delay(300);
}
```

## ผลลัพธ์ที่คาดว่าจะเห็นใน Serial Monitor

เมื่อเปิด Serial Monitor จะเห็นข้อความแสดงค่า Digital, Analog และสถานะการตรวจจับแม่เหล็ก เช่น

```text
KY-025 Sensor Test
Move a magnet near the sensor.
Digital = 0 | Analog = 1023 | Status = No magnet
Digital = 0 | Analog = 1022 | Status = No magnet
Digital = 1 | Analog = 24 | Status = Magnet detected
Digital = 1 | Analog = 23 | Status = Magnet detected
Digital = 0 | Analog = 1023 | Status = No magnet
```

หมายเหตุ: ค่าจริงอาจต่างจากตัวอย่าง ขึ้นอยู่กับรุ่นของโมดูล การปรับ Potentiometer ระยะห่าง และความแรงของแม่เหล็ก

## ตารางบันทึกผลการทดลอง

| ครั้งที่ | สถานะการทดสอบ | Digital Value | Analog Value | ผลที่สังเกตได้ |
| --- | --- | --- | --- | --- |
| 1 | ไม่มีแม่เหล็กใกล้ Sensor |  |  |  |
| 2 | นำแม่เหล็กเข้าใกล้ Sensor |  |  |  |
| 3 | นำแม่เหล็กออกห่าง Sensor |  |  |  |
| 4 | ปรับ Potentiometer แล้วทดสอบใหม่ |  |  |  |

## เกณฑ์การผ่านการทดสอบ

| เงื่อนไข | ผลที่ต้องการ |
| --- | --- |
| ไม่มีแม่เหล็กใกล้ Sensor | ค่า Digital อยู่สถานะหนึ่ง และข้อความแสดง `No magnet` |
| มีแม่เหล็กเข้าใกล้ Sensor | ค่า Digital เปลี่ยนสถานะ และข้อความแสดง `Magnet detected` |
| นำแม่เหล็กออกห่าง | ค่า Digital กลับสู่สถานะเดิม |
| Serial Monitor แสดงผลต่อเนื่อง | มีค่า Digital และ Analog แสดงทุกประมาณ 300 ms |

## การแก้ปัญหาเบื้องต้น

| ปัญหา | สาเหตุที่เป็นไปได้ | วิธีแก้ไข |
| --- | --- | --- |
| Serial Monitor ไม่มีข้อความ | Baud Rate ไม่ตรง หรือไม่ได้อัปโหลดโปรแกรม | ตั้ง Baud Rate เป็น `9600` และอัปโหลดใหม่ |
| ค่า Digital ไม่เปลี่ยน | ต่อสายผิด หรือ Threshold ยังไม่เหมาะสม | ตรวจขา `VCC`, `GND`, `D0` และปรับ Potentiometer |
| Sensor ไม่ตอบสนองต่อแม่เหล็ก | แม่เหล็กอยู่ไกลเกินไป หรือแม่เหล็กแรงไม่พอ | นำแม่เหล็กเข้าใกล้ Reed Switch มากขึ้น |
| ค่า Analog เปลี่ยนแปลก ๆ | ขา Analog ลอยหรือสายหลวม | ตรวจสายที่ต่อกับ `A0` |
| LED บนบอร์ดทำงานกลับด้าน | โมดูลบางรุ่นให้ Logic กลับกัน | ใช้การเปลี่ยนสถานะเป็นหลัก ไม่ยึดว่า `HIGH` ต้องแปลว่าพบเสมอ |

## ข้อควรระวัง

- ตรวจสอบการต่อ `5V` และ `GND` ก่อนเสียบ USB
- อย่าให้ขาไฟเลี้ยงลัดวงจร
- จับโมดูลอย่างระมัดระวัง เพราะ Reed Switch เป็นหลอดแก้วขนาดเล็ก
- ถ้าต้องการใช้งานจริง ควรเพิ่มการ debounce เพื่อลดสัญญาณสั่นจาก Reed Switch

## สรุป

การทดสอบ KY-025 ด้วย Serial Monitor ทำให้เห็นการเปลี่ยนแปลงของ Sensor ได้ชัดเจน ทั้งค่า `Digital` สำหรับตรวจจับสถานะพบ/ไม่พบแม่เหล็ก และค่า `Analog` สำหรับดูระดับแรงดันจากโมดูล ขั้นตอนนี้เหมาะสำหรับตรวจสอบ Sensor ก่อนนำไปใช้ในระบบแจ้งเตือนประตู หน้าต่าง หรือระบบตรวจจับตำแหน่งแบบไม่สัมผัส
