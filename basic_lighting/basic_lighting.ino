/*
 * =====================================================================================
 *
 *       Filename:  current_teensy_sketch.c
 *
 *    Description:  :
 *
 *        Version:  1.0
 *        Created:  05/28/2016 20:18:05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * ============b=========================================================================
 */



#include <OctoWS2811.h>
#include <stdio.h>

int INDICATOR_PIN = 13;
int BAUD_RATE = 115200;

byte pinstate=LOW;

const int WORD_LENGTH_BYTES = 3;
unsigned char CONTROL_HEADER[WORD_LENGTH_BYTES] = {255, 255, 255};

unsigned char controlIdentificationBuffer[WORD_LENGTH_BYTES] = {0, 0, 0};
unsigned char wordBuffer[WORD_LENGTH_BYTES] = {0, 0, 0};

int controlIdentificationIndex = WORD_LENGTH_BYTES - 1;
int wordIndex = WORD_LENGTH_BYTES - 1;

typedef int serialReadState;

const serialReadState READING_IMAGE = 0;
const serialReadState READING_FRAME_RATE = 1;
const serialReadState READING_WIDTH = 2;
const serialReadState READING_HEIGHT = 3;


serialReadState currentState = READING_IMAGE;

int cursorRow = 0;
int cursorCol = 0;


// likely to change, setting as a reasonable value for expressiveness
short frameWidth = 500;
short frameHeight = 8;

const int MAX_TEENSY_STRIPS = 8;

DMAMEM int *displayBuffer;
int *drawBuffer;


OctoWS2811 *getLedsInstance(short width_, short height_) {
  int totalLeds = width_ * height_;
  int ledsPerStrip = totalLeds / MAX_TEENSY_STRIPS;
  displayBuffer = (int *)malloc(ledsPerStrip * 6 * sizeof(int));
  drawBuffer = (int *)malloc(ledsPerStrip * 6 * sizeof(int));
  const int CONFIGURATION = WS2811_GRB | WS2811_800kHz; // might need to cange this value
  return new OctoWS2811 (
    ledsPerStrip,
    displayBuffer,
    drawBuffer,
    CONFIGURATION
  );
}

OctoWS2811 *leds = NULL;


short shortBytesToShort(unsigned char lsb, unsigned char msb) {
    return ((short) msb) << 8 | lsb;
}


unsigned int rbgToInt(unsigned char r, unsigned char b, unsigned char g) {
  return (
    ((unsigned int)r << 16) |
    ((unsigned int)g << 8) |
    (unsigned int)b
  );
}



void setup() {

    Serial.begin(BAUD_RATE);
    Serial.setTimeout(0);

    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(INDICATOR_PIN, OUTPUT);
    digitalWrite(INDICATOR_PIN, HIGH);

    leds = getLedsInstance(frameWidth, frameHeight);
    leds->begin();
}


int BUFFER_SIZE = 512;
char *imageBuffer = (char *) malloc(BUFFER_SIZE);
int movingOffset = 0;
int loopCounter = 0;


void loop() {
  loopCounter++;
  if(loopCounter % 3 == 0) {
    //movingOffset++;  
  }
  
  for(int r=0; r<frameHeight; r++) {
    for(int c=0; c<frameWidth; c++) {

      int movedCol = (movingOffset + c) % frameWidth;
      int pixelIndex = r * frameWidth;
      pixelIndex += movedCol;
      int color;

      /*
      if((c / 30) % 2 == 0) {
        color = rbgToInt(0, 0, 255);
      } else {
        color = rbgToInt(255, 0, 0);
      }
      */
      
      
      color = rbgToInt(35, 4, 23);
      color = rbgToInt(35, 4, 21);
      color = rbgToInt(17, 2, 10);
      //color = rbgToInt(15, 15, 5);
      //color = rbgToInt(255, 0, 0);
      //color = rbgToInt(70, 8, 46);
      leds->setPixel(
        pixelIndex,
        //r,b,g
        color
      );
        
    }
  }
  leds->show();
}

