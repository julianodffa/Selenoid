// Trigger LOW
// Smart UPS Millis

#define voltage_pin 32    // Voltage Sensor
// #define voltage_pin 12    // Voltage Sensor
#define relay_pin_sl 16   // ESP32 pin GIOP16 connected to the IN pin of Relay Selenoid
#define relay_pin_ups 17  // ESP32 pin GIOP17 connected to the IN pin of Relay UPS

float adc_voltage = 0.0;      // adc voltage
float in_voltage = 0.0;       // input voltage
int adc_value = 0;            //adc_value
int thresholdVolt = 8;        // batas tegangan
const char* mode = "PC_OFF";  // status mini pc

void setup() {
  Serial.begin(9600);
  pinMode(relay_pin_sl, OUTPUT);
  pinMode(relay_pin_ups, OUTPUT);
  digitalWrite(relay_pin_sl, HIGH); 
  digitalWrite( relay_pin_ups, HIGH);
}

void loop() {
  // Short delay 3 sec before read voltage input
  delay(3000);

  // Baca input analog
  adc_value = analogRead(voltage_pin);
  adc_voltage = adc_value * (12 / 2900.0);

  // Tampilkan Voltase Analog
  Serial.print("Input Voltage Analog = ");
  Serial.println(adc_value);

  // Tampilkan Voltase
  Serial.print("Input Voltage = ");
  Serial.println(adc_voltage, 2);

  // Tampilkan Mode
  Serial.print("Mode = ");
  Serial.println(mode);

  if (mode == "PC_OFF") {
    if (adc_voltage > thresholdVolt) {
      // Wait For PC and UPS to Power Up Properly
      delay(3000);

      // Menyalakan UPS
      Serial.println("Menyalakan UPS");
      digitalWrite(relay_pin_ups, LOW);
      Serial.println("Power Up");
      Serial.println("press");
      digitalWrite(relay_pin_sl, LOW);
      delay(250);
      Serial.println("release");
      digitalWrite(relay_pin_sl, HIGH);
      Serial.println("Mini PC Booting Up");
      // Delay Booting Up Mini PC, Sebelum Membaca sensor Tegangan kembali (1.5 Min)
      mode = "PC_ON";
      delay(90000UL);
    }
  }

  // if the analog value is high enough, turn on the LED:
  if (mode == "PC_ON") {
    if (adc_voltage < thresholdVolt) {
      // short Delay (2s)
      delay(2000);
      Serial.println("shutdown");
      Serial.println("press");
      digitalWrite(relay_pin_sl, LOW);
      delay(250);
      Serial.println("release");
      digitalWrite(relay_pin_sl, HIGH);
      Serial.println("Mini PC Shutdown");
      // Delay Shutdown Mini PC, Sebelum Membaca sensor Tegangan kembali (30 sec)
      mode = "PC_OFF";
      delay(30000UL);

      // Mematikan UPS
      Serial.println("Mematikan UPS");
      digitalWrite(relay_pin_ups, HIGH);
    }
  }
}