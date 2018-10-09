#include <IRremote.h>
#include <IRremoteInt.h>

#define WHEELSIZE 21
#define R 0
#define G 1
#define B 2
#define W 3

/////////////////////////////////////////////////// Color Definitions ///////////////////////////////////////////////////
#define BLACK 0
#define RED 1
#define GREEN 2
#define BLUE 3
#define YELLOW 4
#define CYAN 5
#define MAGENTA 6

#define ORANGE 7
#define ORANGERED 8
#define LIMEGREEN 9
#define STEELBLUE 10
#define PINK 11
#define DARKORANGE 12
#define TURQUOISE 13
#define MIDNIGHTBLUE 14
#define DEEPPINK 15
#define LIGHTSEAGREEN 16
#define SEAGREEN 17
#define BLUEVIOLET 18
#define LIGHTCYAN 19

#define WHITE 20

int colorWheel[WHEELSIZE][4];

void colorDefinitionLoader() {
  colorWheel[BLACK][R] = 0;
  colorWheel[BLACK][G] = 0;
  colorWheel[BLACK][B] = 0;
  colorWheel[BLACK][W] = 0;

  colorWheel[RED][R] = 255;
  colorWheel[RED][G] = 0;
  colorWheel[RED][B] = 0;
  colorWheel[RED][W] = 0;

  colorWheel[GREEN][R] = 0;
  colorWheel[GREEN][G] = 255;
  colorWheel[GREEN][B] = 0;
  colorWheel[GREEN][W] = 0;

  colorWheel[BLUE][R] = 0;
  colorWheel[BLUE][G] = 0;
  colorWheel[BLUE][B] = 255;
  colorWheel[BLUE][W] = 0;

  colorWheel[YELLOW][R] = 255;
  colorWheel[YELLOW][G] = 255;
  colorWheel[YELLOW][B] = 0;
  colorWheel[YELLOW][W] = 0;

  colorWheel[CYAN][R] = 0;
  colorWheel[CYAN][G] = 255;
  colorWheel[CYAN][B] = 255;
  colorWheel[CYAN][W] = 0;

  colorWheel[MAGENTA][R] = 255;
  colorWheel[MAGENTA][G] = 0;
  colorWheel[MAGENTA][B] = 255;
  colorWheel[MAGENTA][W] = 0;


  colorWheel[ORANGE][R] = 255;
  colorWheel[ORANGE][G] = 165;
  colorWheel[ORANGE][B] = 0;
  colorWheel[ORANGE][W] = 0;

  colorWheel[ORANGERED][R] = 255;
  colorWheel[ORANGERED][G] = 69;
  colorWheel[ORANGERED][B] = 0;
  colorWheel[ORANGERED][W] = 0;

  colorWheel[LIMEGREEN][R] = 50;
  colorWheel[LIMEGREEN][G] = 205;
  colorWheel[LIMEGREEN][B] = 50;
  colorWheel[LIMEGREEN][W] = 0;

  colorWheel[STEELBLUE][R] = 70;
  colorWheel[STEELBLUE][G] = 130;
  colorWheel[STEELBLUE][B] = 180;
  colorWheel[STEELBLUE][W] = 0;

  colorWheel[PINK][R] = 255;
  colorWheel[PINK][G] = 192;
  colorWheel[PINK][B] = 203;
  colorWheel[PINK][W] = 0;

  colorWheel[DEEPPINK][R] = 255;
  colorWheel[DEEPPINK][G] = 20;
  colorWheel[DEEPPINK][B] = 147;
  colorWheel[DEEPPINK][W] = 0;


  colorWheel[DARKORANGE][R] = 255;
  colorWheel[DARKORANGE][G] = 140;
  colorWheel[DARKORANGE][B] = 0;
  colorWheel[DARKORANGE][W] = 0;

  colorWheel[TURQUOISE][R] = 72;
  colorWheel[TURQUOISE][G] = 209;
  colorWheel[TURQUOISE][B] = 204;
  colorWheel[TURQUOISE][W] = 0;

  colorWheel[MIDNIGHTBLUE][R] = 25;
  colorWheel[MIDNIGHTBLUE][G] = 25;
  colorWheel[MIDNIGHTBLUE][B] = 112;
  colorWheel[MIDNIGHTBLUE][W] = 0;

  colorWheel[LIGHTSEAGREEN][R] = 32;
  colorWheel[LIGHTSEAGREEN][G] = 178;
  colorWheel[LIGHTSEAGREEN][B] = 170;
  colorWheel[LIGHTSEAGREEN][W] = 0;

  colorWheel[SEAGREEN][R] = 46;
  colorWheel[SEAGREEN][G] = 139;
  colorWheel[SEAGREEN][B] = 87;
  colorWheel[SEAGREEN][W] = 0;

  colorWheel[BLUEVIOLET][R] = 138;
  colorWheel[BLUEVIOLET][G] = 43;
  colorWheel[BLUEVIOLET][B] = 226;
  colorWheel[BLUEVIOLET][W] = 0;

  colorWheel[LIGHTCYAN][R] = 224;
  colorWheel[LIGHTCYAN][G] = 255;
  colorWheel[LIGHTCYAN][B] = 255;
  colorWheel[LIGHTCYAN][W] = 0;

  colorWheel[WHITE][R] = 0;
  colorWheel[WHITE][G] = 0;
  colorWheel[WHITE][B] = 0;
  colorWheel[WHITE][W] = 255;

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



const int redPin = 10;
const int greenPin = 9;
const int bluePin = 6;
const int whitePin = 5;

const int RECV_PIN = 11;

//Residuati del selettore a potenziometro
const int potPin = A0;
int potValue = 0;

int brightness = 255; //Deve essere memorizzata su EPROM e vanno eseguiti controlli su range di valori
int velocity = 1000; //Deve essere memorizzata su EPROM e vanno eseguiti controlli su range di valori
int color = 0; //Deve essere memorizzata su EPROM e vanno eseguiti controlli su range di valori

boolean flash = false;
boolean jumpTre = false;
boolean fade = false;
int frame = 1;


/////////////////////////////////////////Roba per il fader/////////////////////////////////////////

// Set initial color
int redVal = 0;
int grnVal = 0;
int bluVal = 0;

// Initialize color variables
int prevR = redVal;
int prevG = grnVal;
int prevB = bluVal;

int indice = 1;
int indice2 = 0;

int stepR = 0;
int stepG = 0;
int stepB = 0;

int fadingRed = 0;
int fadingGrn = 0;
int fadingBlu = 0;

int MYDEBUG = 0;      // DEBUG counter; if set to 1, will write values back via serial
int loopCount = 60; // How often should DEBUG report?
///////////////////////////////////////////////////////////////////////////////////////////////////

unsigned long currentMillis = 0;
unsigned long previousMillis = 0;



IRrecv irrecv(RECV_PIN);

decode_results results;
long oldOne = 0;


void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(whitePin, OUTPUT);

  colorDefinitionLoader();

  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {

  if (irrecv.decode(&results)) {
    if (results.value == 0xFFFFFFFF)
      results.value = oldOne;
    if (results.value == 0xFFD02F && oldOne == 0xFFD02F)
      results.value = 0;
    if (results.value == 0xFF20DF && oldOne == 0xFF20DF)
      results.value = 0;
    if (results.value == 0xFF609F && oldOne == 0xFF609F)
      results.value = 0;
    getButton();
    Serial.println(results.value, HEX);
    oldOne = results.value;
    irrecv.resume(); // Receive the next value
  }
  currentMillis = millis();
  strb();
  jump3();
  fading();

  //setRGBW();

  setPWM();

}

void incrBrightness() {
  if (brightness < 255)
    brightness = brightness + 15;
  Serial.println(brightness);
}
void decrBrightness() {
  if (brightness > 0)
    brightness = brightness - 15;
  Serial.println(brightness);
}

void incrSpeed() {
  if (velocity < 1000)
    velocity = velocity + 20;
  Serial.println(velocity);
}
void decrSpeed() {
  if (velocity > 40)
    velocity = velocity - 20;
  Serial.println(velocity);
}


void getButton() {
  switch (results.value) {
    case 0xFFFFFFFF:
      Serial.println(oldOne, HEX);
      break;
    case 0xFF1AE5:
      color = RED;
      break;
    case 0xFF9A65:
      color = GREEN;
      break;
    case 0xFFA25D:
      color = BLUE;
      break;
    case 0xFF22DD:
      color = WHITE;
      break;
    case 0xFF2AD5:
      color = ORANGERED;
      break;
    case 0xFFAA55:
      color = LIMEGREEN;
      break;
    case 0xFF926D:
      color = STEELBLUE;
      break;
    case 0xFF12ED:
      color = PINK;
      break;
    case 0xFF0AF5:
      color = DARKORANGE;
      break;
    case 0xFF8A75:
      color = TURQUOISE;
      break;
    case 0xFFB24D:
      color = MIDNIGHTBLUE;
      break;
    case 0xFF32CD:
      color = DEEPPINK;
      break;
    case 0xFF38C7:
      color = ORANGE;
      break;
    case 0xFFB847:
      color = LIGHTSEAGREEN;
      break;
    case 0xFF7887:
      color = MAGENTA;
      break;
    case 0xFFF807:
      color = CYAN;
      break;
    case 0xFF18E7:
      color = YELLOW;
      break;
    case 0xFF9867:
      color = SEAGREEN;
      break;
    case 0xFF58A7:
      color = BLUEVIOLET;
      break;
    case 0xFFD827:
      color = LIGHTCYAN;
      break;
    case 0xFF3AC5:
      incrBrightness();
      break;
    case 0xFFBA45:
      decrBrightness();
      break;
    case 0xFF02FD:
      color = BLACK;
      break;
    case 0xFFE817:  //Quick
      decrSpeed();
      break;
    case 0xFFC837:  //Slow
      incrSpeed();
      break;
    case 0xFFD02F:  //Flash
      jumpTre = false;
      fade = false;
      flash = setAnim(flash);
      brightness = 255;
      break;
    case 0xFF20DF:  //jumpTre
      flash = false;
      fade = false;
      brightness = 255;
      jumpTre = setAnim(jumpTre);
      color = 1;
      break;
    case 0xFF609F:  //Fade
      flash = false;
      jumpTre = false;
      brightness = 255;
      fade = setAnim(fade);
      color = 1;
      break;
  }
}

/* Serviva per prendere i colori da consolle */
void getColor() {

  if (Serial.available() > 0) {
    color = Serial.parseInt();
    Serial.println(color);
  }
}

/* Trascrivere le definizioni dei colori prima di cancellare */
/*
  void setRGBW() {
  switch (color) {
    case RED:
      red = 255;
      green = 0;
      blue = 0;
      white = 0;
      break;
    case GREEN:
      red = 0;
      green = 255;
      blue = 0;
      white = 0;
      break;
    case BLUE:
      red = 0;
      green = 0;
      blue = 255;
      white = 0;
      break;
    case WHITE:
      red = 0;
      green = 0;
      blue = 0;
      white = 255;
      break;
    case YELLOW:
      red = 255;
      green = 255;
      blue = 0;
      white = 0;
      break;
    case CYAN:
      red = 0;
      green = 255;
      blue = 255;
      white = 0;
      break;
    case MAGENTA:
      red = 255;
      green = 0;
      blue = 255;
      white = 0;
      break;


    case ORANGE:
      red = 255;
      green = 165;
      blue = 0;
      white = 0;
      break;
    case ORANGERED:
      red = 255;
      green = 69;
      blue = 0;
      white = 0;
      break;
    case LIMEGREEN:
      red = 50;
      green = 205;
      blue = 50;
      white = 0;
      break;
    case STEELBLUE:
      red = 70;
      green = 130;
      blue = 180;
      white = 0;
      break;
    case PINK:
      red = 255;
      green = 192;
      blue = 203;
      white = 0;
      break;
    case DARKORANGE:
      red = 255;
      green = 140;
      blue = 0;
      white = 0;
      break;
    case TURQUOISE:
      red = 72;
      green = 209;
      blue = 204;
      white = 0;
      break;
    case MIDNIGHTBLUE:
      red = 25;
      green = 25;
      blue = 112;
      white = 0;
      break;
    case DEEPPINK:
      red = 255;
      green = 20;
      blue = 147;
      white = 0;
      break;
    case LIGHTSEAGREEN:
      red = 32;
      green = 178;
      blue = 170;
      white = 0;
      break;
    case SEAGREEN:
      red = 46;
      green = 139;
      blue = 87;
      white = 0;
      break;
    case BLUEVIOLET:
      red = 138;
      green = 43;
      blue = 226;
      white = 0;
      break;
    case LIGHTCYAN:
      red = 224;
      green = 255;
      blue = 255;
      white = 0;
      break;
    case BLACK:
      red = 0;
      green = 0;
      blue = 0;
      white = 0;
      break;
    default:
      break;
  }
  }
*/

void setPWM() {
  int redPwm, greenPwm, bluePwm, whitePwm;

  if (fade) {
    redPwm = map(brightness, 0, 255, 0, fadingRed);
    greenPwm = map(brightness, 0, 255, 0, fadingGrn);
    bluePwm = map(brightness, 0, 255, 0, fadingBlu);
    whitePwm = 0;

  } else {
    redPwm = map(brightness, 0, 255, 0, colorWheel[color][R]);
    greenPwm = map(brightness, 0, 255, 0, colorWheel[color][G]);
    bluePwm = map(brightness, 0, 255, 0, colorWheel[color][B]);
    whitePwm = map(brightness, 0, 255, 0, colorWheel[color][W]);
  }

  analogWrite(redPin, redPwm);
  analogWrite(greenPin, greenPwm);
  analogWrite(bluePin, bluePwm);
  analogWrite(whitePin, whitePwm);
}

boolean setAnim(boolean value) {
  if (value == true)
    value = false;
  else {
    value = true;
    frame = 1;
  }
  Serial.println(value);
  return value;
}


void strb() {
  if (flash) {
    //Serial.println(frame);
    //Serial.println(brightness);
    if (currentMillis - previousMillis >= velocity) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;

      if (frame == 0) {
        frame = 1;
      } else {
        frame = 0;
      }
    }
    brightness = 255 * frame;
  }
}

void jump3() {
  if (jumpTre) {
    //Serial.println(color);
    //Serial.println(brightness);
    if (currentMillis - previousMillis >= velocity) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      if (color < WHEELSIZE) {
        color++;
      }
      if (color == WHEELSIZE - 1) {
        color = 1;
      }
      Serial.println(color);
    }
  }
}


void fading() {
  if (fade) {
    if (indice < WHEELSIZE - 1) {
      if (MYDEBUG) {
        Serial.println("Cross con indice: " + String(indice));
        Serial.println("Cross con indice2: " + String(indice2));
      }
      crossFade(colorWheel[indice][R], colorWheel[indice][G], colorWheel[indice][B]);
      //indice++;
    } else {
      indice = 1;
      indice2 = 0;
    }
  }
}

/* BELOW THIS LINE IS THE MATH -- YOU SHOULDN'T NEED TO CHANGE THIS FOR THE BASICS

  The program works like this:
  Imagine a crossfade that moves the red LED from 0-10,
    the green from 0-5, and the blue from 10 to 7, in
    ten steps.
    We'd want to count the 10 steps and increase or
    decrease color values in evenly stepped increments.
    Imagine a + indicates raising a value by 1, and a -
    equals lowering it. Our 10 step fade would look like:

    1 2 3 4 5 6 7 8 9 10
  R + + + + + + + + + +
  G   +   +   +   +   +
  B     -     -     -

  The red rises from 0 to 10 in ten steps, the green from
  0-5 in 5 steps, and the blue falls from 10 to 7 in three steps.

  In the real program, the color percentages are converted to
  0-255 values, and there are 1020 steps (255*4).

  To figure out how big a step there should be between one up- or
  down-tick of one of the LED values, we call calculateStep(),
  which calculates the absolute gap between the start and end values,
  and then divides that gap by 1020 to determine the size of the step
  between adjustments in the value.
*/

int calculateStep(int prevValue, int endValue) {
  int step = endValue - prevValue; // What's the overall gap?
  if (step) {                      // If its non-zero,
    step = 1020 / step;            //   divide by 1020
  }
  return step;
}

/* The next function is calculateVal. When the loop value, i,
   reaches the step size appropriate for one of the
   colors, it increases or decreases the value of that color by 1.
   (R, G, and B are each calculated separately.)
*/

int calculateVal(int step, int val, int i) {

  if ((step) && i % step == 0) { // If step is non-zero and its time to change a value,
    if (step > 0) {              //   increment the value if step is positive...
      val += 1;
    }
    else if (step < 0) {         //   ...or decrement it if step is negative
      val -= 1;
    }
  }
  // Defensive driving: make sure val stays in the range 0-255
  if (val > 255) {
    val = 255;
  }
  else if (val < 0) {
    val = 0;
  }
  return val;
}

/* crossFade() loops 1020 times, checking to see if
   the value needs to be updated each time, then writing
   the color values to the correct pins.
*/

void crossFade(int red, int green, int blue) {

  if (indice2 == 0) {
    stepR = calculateStep(prevR, red);
    stepG = calculateStep(prevG, green);
    stepB = calculateStep(prevB, blue);
  }

  //for (int i = 0; i <= 1020; i++)

  int crosVelocity = map(velocity, 40, 1000, 0, 20);
  if (currentMillis - previousMillis >= crosVelocity) {
    //Serial.println("Previous: " + String(previousMillis));
    //Serial.println("Current: " + String(currentMillis));
    //Serial.println("Difference: " + String(currentMillis - previousMillis));
    previousMillis = currentMillis;
    if (indice2 <= 1020) {
      redVal = calculateVal(stepR, redVal, indice2);
      grnVal = calculateVal(stepG, grnVal, indice2);
      bluVal = calculateVal(stepB, bluVal, indice2);

      fadingRed = redVal;
      fadingGrn = grnVal;
      fadingBlu = bluVal;

      if (MYDEBUG) { // If we want serial output, print it at the
        if (indice2 == 0 or indice2 % loopCount == 0) { // beginning, and every loopCount times
          Serial.print("Loop/RGB: #");
          Serial.print(indice2);
          Serial.print("\t|\t");
          Serial.print(redVal);
          Serial.print("\t/ ");
          Serial.print(grnVal);
          Serial.print("\t/ ");
          Serial.println(bluVal);
        }
        MYDEBUG++;
      }
      indice2++;
    }
    if (indice2 > 1020) {
      indice++;
      indice2 = 0;
    }
    // Update current values for next loop
    prevR = redVal;
    prevG = grnVal;
    prevB = bluVal;
    //delay(hold); // Pause for optional 'wait' milliseconds before resuming the loop
  }
}

