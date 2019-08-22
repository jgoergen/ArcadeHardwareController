// SETTINGS /////////////////////////////////////////////////////////////////////////////////
#define AMBIENT_NEOPIXELS       12
#define TWEEN_SPEED             10.0f
#define AMBIENT_BRIGHTNESS      64

// PINS /////////////////////////////////////////////////////////////////////////////////////
#define NEOPIXELS_AMBIENT_PIN   7

Adafruit_NeoPixel ambientStrip = Adafruit_NeoPixel(AMBIENT_NEOPIXELS, NEOPIXELS_AMBIENT_PIN, NEO_GRB + NEO_KHZ800);

byte ambientTargetColorsRed[AMBIENT_NEOPIXELS];
byte ambientTargetColorsGreen[AMBIENT_NEOPIXELS];
byte ambientTargetColorsBlue[AMBIENT_NEOPIXELS];
byte ambientColorsRed[AMBIENT_NEOPIXELS];
byte ambientColorsGreen[AMBIENT_NEOPIXELS];
byte ambientColorsBlue[AMBIENT_NEOPIXELS];
const char* AMB_COMMAND_DIVIDER_CHAR = "-";

void ambientLights_Init() {

  ambientStrip.begin();
  ambientStrip.setBrightness(AMBIENT_BRIGHTNESS);
  ambientStrip.show();

  for(int i = 0; i < AMBIENT_NEOPIXELS; i ++) {

    ambientTargetColorsRed[i] = 0;
    ambientTargetColorsGreen[i] = 0;
    ambientTargetColorsBlue[i] = 0;
    ambientColorsRed[i] = 0;
    ambientColorsGreen[i] = 0;
    ambientColorsBlue[i] = 0;
  }
}

void ambientLights_Update() {

  for(int i = 0; i < AMBIENT_NEOPIXELS; i ++) {

    if (ambientColorsRed[i] != ambientTargetColorsRed[i])
      ambientColorsRed[i] = 
        tweenVal(
          ambientColorsRed[i], 
          ambientTargetColorsRed[i], 
          LED_TWEEN_SPEED);

    if (ambientColorsGreen[i] != ambientTargetColorsGreen[i])
      ambientColorsGreen[i] = 
        tweenVal(
          ambientColorsGreen[i], 
          ambientTargetColorsGreen[i], 
          LED_TWEEN_SPEED);

    if (ambientColorsBlue[i] != ambientTargetColorsBlue[i])
      ambientColorsBlue[i] = 
        tweenVal(
          ambientColorsBlue[i], 
          ambientTargetColorsBlue[i], 
          LED_TWEEN_SPEED);
          
    ambientStrip.setPixelColor(
      i, 
      ambientStrip.Color(
        ambientColorsRed[i], 
        ambientColorsGreen[i], 
        ambientColorsBlue[i]));
  }

  ambientStrip.show();
}

void ambientLights_Set(byte r, byte g, byte b, int ambientIndex) {

  ambientTargetColorsRed[ambientIndex] = r;
  ambientTargetColorsGreen[ambientIndex] = g;
  ambientTargetColorsBlue[ambientIndex] = b;
}

void ambientLights_Parse_Command(char* cmd) {

  char* indexChar = strtok(cmd, AMB_COMMAND_DIVIDER_CHAR);
  char* rChar = strtok(NULL, AMB_COMMAND_DIVIDER_CHAR);
  char* gChar = strtok(NULL, AMB_COMMAND_DIVIDER_CHAR);
  char* bChar = strtok(NULL, AMB_COMMAND_DIVIDER_CHAR);

  ambientLights_Set(byte(atoi(rChar)), byte(atoi(gChar)), byte(atoi(bChar)), byte(atoi(indexChar)));
}
