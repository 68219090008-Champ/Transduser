# LAB2 Blink 2 LED

## ข้อมูลนักเรียน
- รหัสนักเรียน: 68219090008
- ชื่อ-นามสกุล: นาย ทีรธร กาญจนวิวิญ
- แผนก: เทคนิคคอมพิวเตอร์

## วัตถุประสงค์
การเขียนโปรแกรมเพื่อให้ LED 2 ตัว ทำงานกระพริบสลับกัน โดยใช้ขา D12 และ D13 ของ Arduino Uno

## การต่อวงจร
| LED | ขาที่ต่อกับ Arduino | ขาที่ต่อกับวงจร |
|-----|--------------------|----------------|
| LED 1 | D12 | ผ่านตัวต้านทาน 220 Ω ไปยังขา Anode แล้วจึงต่อ Cathode กับ GND |
| LED 2 | D13 | ผ่านตัวต้านทาน 220 Ω ไปยังขา Anode แล้วจึงต่อ Cathode กับ GND |

## วิธีการต่อ
1. ต่อขา long leg (anode) ของ LED ไปยังขา D12 และ D13
2. ต่อขา short leg (cathode) ของ LED ไปยัง GND
3. ใช้ตัวต้านทาน 220 Ω ต่อน้ำหนักระหว่างขา D12/D13 กับ LED เพื่อป้องกัน LED เสียหาย

## ตัวอย่างโค้ด
```cpp
const int led1 = 12;
const int led2 = 13;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  delay(500);

  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  delay(500);
}
```

## ผลลัพธ์ที่คาดหวัง
- LED ที่ต่อกับ D12 จะติดค้างแล้วดับสลับกับ LED ที่ต่อกับ D13
- ความเร็วกระพริบประมาณ 0.5 วินาทีต่อครั้ง