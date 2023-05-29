//Maverick 1 Pro Arduino Code
//By Andrew Burton of BOESFX


#include <Joystick.h>
#include <FastLED.h>

#define NUM_LEDS 26
#define LED_PIN 2

#define ledButton 4
#define greenButton 5
#define redButton 6
#define yellowButton 7
#define blueButton 8
#define orangeButton 9
#define starButton 15
#define startButton 14
#define up2Button 18
#define up1Button 19
#define down1Button 16
#define down2Button 10
#define wammy2Button 21
#define wammy1Button 20

CRGB leds[NUM_LEDS];

Joystick_ Joystick(0x15, JOYSTICK_TYPE_JOYSTICK, 10, 0, false, false, false, false, false, false, false, false, false, false, false);

const bool initAutoSendState = true;

int lastLedButtonState = 0;
int lastGreenButtonState = 0;
int lastRedButtonState = 0;
int lastYellowButtonState = 0;
int lastBlueButtonState = 0;
int lastOrangeButtonState = 0;
int lastStarButtonState = 0;
int lastStartButtonState = 0;
int lastUpButtonState = 0;
int lastDownButtonState = 0;
int lastWammyButtonState = 0;

int ledButtonIndex = 0;
uint8_t gHue = 0;
 



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);

  FastLED.setBrightness(50);

  //Buttons on board are pulled up with a 4.7K OHM resistor
  pinMode(ledButton, INPUT);
  pinMode(greenButton, INPUT);
  pinMode(redButton, INPUT);
  pinMode(yellowButton, INPUT);
  pinMode(blueButton, INPUT);
  pinMode(orangeButton, INPUT);
  pinMode(starButton, INPUT);
  pinMode(startButton, INPUT);
  pinMode(up1Button, INPUT);
  pinMode(up2Button, INPUT);
  pinMode(down1Button, INPUT);
  pinMode(down2Button, INPUT);
  pinMode(wammy1Button, INPUT);
  pinMode(wammy2Button, INPUT);

  Joystick.begin();
}

void loop() {
  //Button input

//*********************GREEN FRET*******************************
  int currentGreenButtonState = !digitalRead(greenButton);

  if (currentGreenButtonState != lastGreenButtonState)
  {
    Joystick.setButton (0, currentGreenButtonState);
    lastGreenButtonState = currentGreenButtonState;
  }

//*********************RED FRET****************************
  int currentRedButtonState = !digitalRead(redButton);

  if (currentRedButtonState != lastRedButtonState)
  {
    Joystick.setButton (1, currentRedButtonState);
    lastRedButtonState = currentRedButtonState;
  }

//*********************YELLOW FRET*****************************
  int currentYellowButtonState = !digitalRead(yellowButton);

  if (currentYellowButtonState != lastYellowButtonState)
  {
    Joystick.setButton (2, currentYellowButtonState);
    lastYellowButtonState = currentYellowButtonState;
  }

//*********************BLUE FRET******************************
  int currentBlueButtonState = !digitalRead(blueButton);

  if (currentBlueButtonState != lastBlueButtonState)
  {
    Joystick.setButton (3, currentBlueButtonState);
    lastBlueButtonState = currentBlueButtonState;
  }

//********************ORANGE FRET****************************
  int currentOrangeButtonState = !digitalRead(orangeButton);

  if (currentOrangeButtonState != lastOrangeButtonState)
  {
    Joystick.setButton (4, currentOrangeButtonState);
    lastOrangeButtonState = currentOrangeButtonState;
  }

//********************STAR BUTTON*******************************
 int currentStarButtonState = !digitalRead(starButton);

  if (currentStarButtonState != lastStarButtonState)
  {
    Joystick.setButton (5, currentStarButtonState);
    lastStarButtonState = currentStarButtonState;
  }

//********************START BUTTON*****************************
   int currentStartButtonState = !digitalRead(startButton);

  if (currentStartButtonState != lastStartButtonState)
  {
    Joystick.setButton (6, currentStartButtonState);
    lastStartButtonState = currentStartButtonState;
  }

//********************UP STRUM*****************************
   int currentUpButtonState = !digitalRead(up1Button) || !digitalRead(up2Button);

  if (currentUpButtonState != lastUpButtonState)
  {
    Joystick.setButton (7, currentUpButtonState);
    lastUpButtonState = currentUpButtonState;
  }

//********************DOWN STRUM********************************
   int currentDownButtonState = !digitalRead(down1Button) || !digitalRead(down2Button);

  if (currentDownButtonState != lastDownButtonState)
  {
    Joystick.setButton (8, currentDownButtonState);
    lastDownButtonState = currentDownButtonState;
  }

//********************WHAMMY********************************
   int currentWammyButtonState = !digitalRead(wammy1Button) || !digitalRead(wammy2Button);

  if (currentWammyButtonState != lastWammyButtonState)
  {
    Joystick.setButton (9, currentWammyButtonState);
    lastWammyButtonState = currentWammyButtonState;
  }


//********************LED INDEXING********************************

  if(digitalRead(ledButton) == LOW)
  {
    ledButtonIndex++;
    delay(250);
  }

  if(ledButtonIndex > 18)
  {
    ledButtonIndex = 0;
  }

  EVERY_N_MILLISECONDS( 20 ) { gHue++; }

  FastLED.show();

  switch (ledButtonIndex)
  {
    case 0:
    MainLEDSequence();
    break;
    case 1:
    SingleColorButtonSequence(255, 0, 0);
    break;
    case 2:
    SingleColorButtonSequence(255, 80, 0);
    break;
    case 3:
    SingleColorButtonSequence(255, 255, 0);
    break;
    case 4:
    SingleColorButtonSequence(100, 255, 0);
    break;
    case 5:
    SingleColorButtonSequence(0, 255, 0);
    break;
    case 6:
    SingleColorButtonSequence(0, 255, 100);
    break;
    case 7:
    SingleColorButtonSequence(0, 255, 255);
    break; 
    case 8:
    SingleColorButtonSequence(0, 100, 255);
    break;   
    case 9:
    SingleColorButtonSequence(0, 0, 255);
    break;
    case 10:
    SingleColorButtonSequence(100, 0, 255);
    break;
    case 11:
    SingleColorButtonSequence(255, 0, 255);
    break;
    case 12:
    SingleColorButtonSequence(255, 0, 100);
    break;
    case 13:
    rainbow();
    break;
    case 14:
    rainbowWithGlitter();
    break;
    case 15:
    confetti();
    break;
    case 16:
    sinelon();
    break;
    case 17:
    juggle();
    break;
    case 18:
    bpm();
    break;

  }

}

void MainLEDSequence()
{

  //Start Button
  leds[0] = CRGB(255, 255, 255);
  leds[1] = CRGB(255, 255, 255);

  //Up 2 Button
  leds[2] = CRGB(255, 255, 255);
  leds[3] = CRGB(255, 255, 255);

  //Up 1 Button
  leds[4] = CRGB(255, 255, 255);
  leds[5] = CRGB(255, 255, 255);

  //Whammy 1 Button
  leds[6] = CRGB(255, 255, 255);
  leds[7] = CRGB(255, 255, 255);

  //Whammy 2 Button
  leds[8] = CRGB(255, 255, 255);
  leds[9] = CRGB(255, 255, 255);

  //Down 2 Button
  leds[10] = CRGB(255, 255, 255);
  leds[11] = CRGB(255, 255, 255);

  //Down 1 Button
  leds[12] = CRGB(255, 255, 255);
  leds[13] = CRGB(255, 255, 255);

  //Star Button
  leds[14] = CRGB(255, 255, 255);
  leds[15] = CRGB(255, 255, 255);

  //Orange Button
  leds[16] = CRGB(255, 100, 0);
  leds[17] = CRGB(255, 100, 0);

  //Blue Button
  leds[18] = CRGB(0, 0, 255);
  leds[19] = CRGB(0, 0, 255);

  //Yellow Button
  leds[20] = CRGB(255, 255, 0);
  leds[21] = CRGB(255, 255, 0);

  //Red Button
  leds[22] = CRGB(255, 0, 0);
  leds[23] = CRGB(255, 0, 0);

  //Green Button
  leds[24] = CRGB(0, 255, 0);
  leds[25] = CRGB(0, 255, 0);
}

void SingleColorButtonSequence(int r, int g, int b)
{

    //Start Button
  leds[0] = CRGB(r, g, b);
  leds[1] = CRGB(r, g, b);

  //Up 2 Button
  leds[2] = CRGB(r, g, b);
  leds[3] = CRGB(r, g, b);

  //Up 1 Button
  leds[4] = CRGB(r, g, b);
  leds[5] = CRGB(r, g, b);

  //Whammy 1 Button
  leds[6] = CRGB(r, g, b);
  leds[7] = CRGB(r, g, b);

  //Whammy 2 Button
  leds[8] = CRGB(r, g, b);
  leds[9] = CRGB(r, g, b);

  //Down 2 Button
  leds[10] = CRGB(r, g, b);
  leds[11] = CRGB(r, g, b);

  //Down 1 Button
  leds[12] = CRGB(r, g, b);
  leds[13] = CRGB(r, g, b);

  //Star Button
  leds[14] = CRGB(r, g, b);
  leds[15] = CRGB(r, g, b);

  //Orange Button
  leds[16] = CRGB(r, g, b);
  leds[17] = CRGB(r, g, b);

  //Blue Button
  leds[18] = CRGB(r, g, b);
  leds[19] = CRGB(r, g, b);

  //Yellow Button
  leds[20] = CRGB(r, g, b);
  leds[21] = CRGB(r, g, b);

  //Red Button
  leds[22] = CRGB(r, g, b);
  leds[23] = CRGB(r, g, b);

  //Green Button
  leds[24] = CRGB(r, g, b);
  leds[25] = CRGB(r, g, b);
}

void rainbow()
{
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }

}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);

}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 192);

}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }

}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  uint8_t dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }

}


