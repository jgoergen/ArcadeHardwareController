// PINS /////////////////////////////////////////////////////////////////////////////////////
#define PIR_PIN                 3

void motionDetector_Init() {
  
}

bool motionDetector_Read() {

  return digitalRead(PIR_PIN);
}
