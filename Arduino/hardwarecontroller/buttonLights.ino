// SETTINGS /////////////////////////////////////////////////////////////////////////////////
#define BTN_NEOPIXELS           20
#define BTN_COUNT               10
#define BTN_BRIGHTNESS          64

// PINS /////////////////////////////////////////////////////////////////////////////////////
#define NEOPIXELS_BTNS_PIN      2

Adafruit_NeoPixel buttonStrip = Adafruit_NeoPixel(BTN_NEOPIXELS, NEOPIXELS_BTNS_PIN, NEO_GRB + NEO_KHZ800);

byte btnIndexs[BTN_COUNT] = { 0, 5, 10, 15, 0, 0, 0, 0, 0, 0 };
byte btnCounts[BTN_COUNT] = { 5, 5, 5, 5, 0, 0, 0, 0, 0, 0 };

byte btnTargetColorsRed[BTN_NEOPIXELS];
byte btnTargetColorsGreen[BTN_NEOPIXELS];
byte btnTargetColorsBlue[BTN_NEOPIXELS];
byte btnColorsRed[BTN_NEOPIXELS];
byte btnColorsGreen[BTN_NEOPIXELS];
byte btnColorsBlue[BTN_NEOPIXELS];
const char* BUTN_COMMAND_DIVIDER_CHAR = "-";

void buttonLights_Init() {

  buttonStrip.begin();
  buttonStrip.setBrightness(BTN_BRIGHTNESS);
  buttonStrip.show();

  for(int i = 0; i < BTN_NEOPIXELS; i ++) {

    btnTargetColorsRed[i] = 0;
    btnTargetColorsGreen[i] = 0;
    btnTargetColorsBlue[i] = 0;
    btnColorsRed[i] = 0;
    btnColorsGreen[i] = 0;
    btnColorsBlue[i] = 0;
  }
}

void buttonLights_Update() {

  for (int o = 0; o < BTN_NEOPIXELS; o ++) {
  
    if (btnColorsRed[o] != btnTargetColorsRed[o])
      btnColorsRed[o] = 
        tweenVal(
          btnColorsRed[o], 
          btnTargetColorsRed[o], 
          LED_TWEEN_SPEED);

    if (btnColorsGreen[o] != btnTargetColorsGreen[o])
      btnColorsGreen[o] = 
        tweenVal(
          btnColorsGreen[o], 
          btnTargetColorsGreen[o], 
          LED_TWEEN_SPEED);
  
    if (btnColorsBlue[o] != btnTargetColorsBlue[o])
      btnColorsBlue[o] = 
        tweenVal(
          btnColorsBlue[o], 
          btnTargetColorsBlue[o], 
          LED_TWEEN_SPEED);

    buttonStrip.setPixelColor(
      o, 
      buttonStrip.Color(
        btnColorsRed[o], 
        btnColorsGreen[o], 
        btnColorsBlue[o]));
  }

  buttonStrip.show();
}

void buttonLights_Set(byte r, byte g, byte b, int buttonIndex) {

  int startIndex = btnIndexs[buttonIndex];
  int endIndex = (btnIndexs[buttonIndex] + btnCounts[buttonIndex]);

  if (startIndex == 0 && endIndex == 0)
    return;

  for (int i = startIndex; i < endIndex; i++) {
      
    btnTargetColorsRed[i] = r;
    btnTargetColorsGreen[i] = g;
    btnTargetColorsBlue[i] = b;
  }
}

void buttonLights_Parse_Command(char* cmd) {

  char* indexChar = strtok(cmd, BUTN_COMMAND_DIVIDER_CHAR);
  char* rChar = strtok(NULL, BUTN_COMMAND_DIVIDER_CHAR);
  char* gChar = strtok(NULL, BUTN_COMMAND_DIVIDER_CHAR);
  char* bChar = strtok(NULL, BUTN_COMMAND_DIVIDER_CHAR);

  buttonLights_Set(
    byte(atoi(rChar)), 
    byte(atoi(gChar)), 
    byte(atoi(bChar)), 
    atoi(indexChar));
}
