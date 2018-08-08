# 1 "C:\\Users\\George\\Desktop\\TMC2208_Simple\\TMC2208_Simple.ino"
# 1 "C:\\Users\\George\\Desktop\\TMC2208_Simple\\TMC2208_Simple.ino"
// Author Teemu Mäntykallio, 2017-04-07

// Define pins



# 8 "C:\\Users\\George\\Desktop\\TMC2208_Simple\\TMC2208_Simple.ino" 2
TMC2208Stepper driver = TMC2208Stepper(&Serial1); // Create driver and use
                                                  // HardwareSerial0 for communication

void setup() {
  Serial.begin(115200);
  Serial.println("Start...");
  Serial1.begin(115200); // Start hardware serial 1
  driver.push(); // Reset registers

  // Prepare pins
  pinMode(38 /* LOW: Driver enabled. HIGH: Driver disabled*/, 0x1);
  pinMode(54 /* Step on rising edge*/, 0x1);
  digitalWrite(38 /* LOW: Driver enabled. HIGH: Driver disabled*/, 0x1); // Disable driver in hardware

  driver.pdn_disable(true); // Use PDN/UART pin for communication
  driver.I_scale_analog(false); // Use internal voltage reference
  driver.rms_current(500); // Set driver current 500mA
  driver.toff(2); // Enable driver in software

  digitalWrite(38 /* LOW: Driver enabled. HIGH: Driver disabled*/, 0x0); // Enable driver in hardware

  uint32_t data = 0;
  Serial.print("DRV_STATUS = 0x");
  driver.DRV_STATUS(&data);
  Serial.println(data, 16);
}

void loop() {
  digitalWrite(54 /* Step on rising edge*/, !digitalRead(54 /* Step on rising edge*/));
  delayMicroseconds(100);
}
