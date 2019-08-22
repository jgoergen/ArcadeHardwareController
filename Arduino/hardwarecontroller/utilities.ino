float tweenVal(float original, float target, float speed) {

  return original + ((target - original) / speed);
}

byte wheelR(byte WheelPos) {
  
  WheelPos = 255 - WheelPos;
  
  if(WheelPos < 85) {
    
    return 255 - WheelPos * 3;
  }
  
  if(WheelPos < 170) {
    
    WheelPos -= 85;
    return 0;
  }
  
  WheelPos -= 170;
  return WheelPos * 3;
}

byte wheelG(byte WheelPos) {
  
  WheelPos = 255 - WheelPos;
  
  if(WheelPos < 85) {
    
    return 0;
  }
  
  if(WheelPos < 170) {
    
    WheelPos -= 85;
    return WheelPos * 3;
  }
  
  WheelPos -= 170;
  return 255 - WheelPos * 3;
}

byte wheelB(byte WheelPos) {
  
  WheelPos = 255 - WheelPos;
  
  if(WheelPos < 85) {
    
    return WheelPos * 3;
  }
  
  if(WheelPos < 170) {
    
    WheelPos -= 85;
    return 255 - WheelPos * 3;
  }
  
  WheelPos -= 170;
  return 0;
}
