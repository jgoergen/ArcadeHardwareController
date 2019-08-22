uint16_t btnAnimationIndex = 0;
uint16_t ambientAnimationIndex = 0;

void attractMode_Init() {
  
}

void attractMode_Update() {

  if (btnAnimationIndex >= 256)
    btnAnimationIndex = 0;
    
  for(uint16_t i = 0; i < 10; i ++)
    buttonLights_Set(
      wheelR(i + btnAnimationIndex) & 255,
      wheelG(i + btnAnimationIndex) & 255,
      wheelB(i + btnAnimationIndex) & 255,
      i);
  
  btnAnimationIndex ++;

  if (ambientAnimationIndex >= 256)
    ambientAnimationIndex = 0;  

  for(int i = 0; i < ambientStrip.numPixels(); i ++)
    ambientLights_Set(
      wheelR(i + ambientAnimationIndex) & 255,
      wheelG(i + ambientAnimationIndex) & 255,
      wheelB(i + ambientAnimationIndex) & 255,
      i);
  
  ambientAnimationIndex ++;
}
