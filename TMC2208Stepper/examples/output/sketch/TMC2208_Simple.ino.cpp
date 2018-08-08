#include <Arduino.h>
#line 1 "C:\\Users\\George\\Desktop\\TMC2208_Simple\\TMC2208_Simple.ino"
#line 1 "C:\\Users\\George\\Desktop\\TMC2208_Simple\\TMC2208_Simple.ino"
// Author Teemu Mäntykallio, 2017-04-07

// Define pins
#define EN_PIN    38  // LOW: Driver enabled. HIGH: Driver disabled
#define STEP_PIN  54  // Step on rising edge

#include <TMC2208Stepper.h>                       // Include library
TMC2208Stepper driver = TMC2208Stepper(&Serial1);  // Create driver and use
                                                  // HardwareSerial0 for communication

#line 11 "C:\\Users\\George\\Desktop\\TMC2208_Simple\\TMC2208_Simple.ino"
void setup();
#line 35 "C:\\Users\\George\\Desktop\\TMC2208_Simple\\TMC2208_Simple.ino"
void loop();
#line 11 "C:\\Users\\George\\Desktop\\TMC2208_Simple\\TMC2208_Simple.ino"
void setup() {
  Serial.begin(115200);
  Serial.println("Start...");
  Serial1.begin(115200);        // Start hardware serial 1
  driver.push();                // Reset registers

  // Prepare pins
  pinMode(EN_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  digitalWrite(EN_PIN, HIGH);   // Disable driver in hardware

  driver.pdn_disable(true);     // Use PDN/UART pin for communication
  driver.I_scale_analog(false); // Use internal voltage reference
  driver.rms_current(500);      // Set driver current 500mA
  driver.toff(2);               // Enable driver in software

  digitalWrite(EN_PIN, LOW);    // Enable driver in hardware

  uint32_t data = 0;
  Serial.print("DRV_STATUS = 0x");
  driver.DRV_STATUS(&data);
  Serial.println(data, HEX);
}

void loop() {
  digitalWrite(STEP_PIN, !digitalRead(STEP_PIN));
  delayMicroseconds(100);
}

