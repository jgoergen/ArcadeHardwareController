#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <MFRC522.h>

// SETTINGS /////////////////////////////////////////////////////////////////////////////////
#define UPDATE_WAIT             33
#define STARTUP_DELAY           1000
#define RFID_UPDATE_SPEED       33
#define LED_UPDATE_SPEED        7
#define MOTION_UPDATE_SPEED     100
#define SERIAL_UPDATE_SPEED     1
#define MODE_UPDATE_SPEED       33
#define LED_TWEEN_SPEED         10.0f

bool pirStatus = false;
int mode = 0;
long lastRFIDUpdate = 0;
long lastLEDUpdate = 0;
long lastMotionUpdate = 0;
long lastSerialUpdate = 0;
long lastModeUpdate = 0;
long milliseconds = 0;

void setup() {

  delay(STARTUP_DELAY);
  serialInterface_Init();
  RFID_Init();
  ambientLights_Init();
  buttonLights_Init();
  motionDetector_Init();
  attractMode_Init();

  Serial.print("ready|");

  mode = 0;
}

void loop() {

  milliseconds = millis();

  if (milliseconds - lastModeUpdate > MODE_UPDATE_SPEED) {
    
    lastModeUpdate = milliseconds;
    
    switch(mode) {
  
      case 0:
        attractMode_Update();      
        break;
    }
  }
  
  mainLoop();
}

void mainLoop() {
  
  if (milliseconds - lastRFIDUpdate > RFID_UPDATE_SPEED) {
    
    lastRFIDUpdate = milliseconds;
    RFID_Update();
  }
  
  if (milliseconds - lastLEDUpdate > LED_UPDATE_SPEED) {
    
    lastLEDUpdate = milliseconds;
    ambientLights_Update();
    buttonLights_Update();
  }
  
  if (milliseconds - lastSerialUpdate > SERIAL_UPDATE_SPEED) {
    
    lastSerialUpdate = milliseconds;
    serialInterface_Update();
  }

  if (milliseconds - lastMotionUpdate > MOTION_UPDATE_SPEED) {

    lastMotionUpdate = milliseconds;
    bool pirVal = motionDetector_Read();
    if (pirStatus != pirVal) {
  
      pirStatus = pirVal;
      Serial.print("PIR|");
      Serial.println(pirVal);
    }
  }
}

void changeMode(int newMode) {

  mode = newMode;
}
