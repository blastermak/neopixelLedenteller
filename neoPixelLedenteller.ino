#include <Adafruit_NeoPixel.h>
//array containing the correct sequences for displaying a number
const int displayGetal[10][7] = {{0,1,1,1,1,1,1}, //0
                                  {0,0,0,1,1,0,0}, //1
                                  {1,0,1,1,0,1,1}, //2
                                  {1,0,1,1,1,1,0}, //3
                                  {1,1,0,1,1,0,0}, //4
                                  {1,1,1,0,1,1,0}, //5
                                  {1,1,1,0,1,1,1}, //6
                                  {0,0,1,1,1,0,0}, //7
                                  {1,1,1,1,1,1,1}, //8
                                  {1,1,1,1,1,0,0}};  //9
//storing the displaynumber in an array                                  
int displayNumber[3] = {0,0,0};
//rgb values for the neopixel strip
int rgb[3] = {255,0,0};
//variable for setting interval for changing of rgb values
long int timer = 0;

//defing correct pins for neopixel strip and button
#define onePin  6
#define tenPin  5
#define hunPin  4
#define buttonPin 7
//number of pixels in strip
#define pixel 56

int buttonState = 0;
int tens = false;
int hun = false;

Adafruit_NeoPixel getalEen = Adafruit_NeoPixel(pixel, onePin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel getalTen = Adafruit_NeoPixel(pixel, tenPin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel getalHun = Adafruit_NeoPixel(16, hunPin, NEO_GRB + NEO_KHZ800);

//logic for turning off all leds in strip
void turnOffLed(){
  for (int i =0;i<pixel;i++){
    getalEen.setPixelColor(i,0,0,0);
    getalTen.setPixelColor(i,0,0,0);
    getalHun.setPixelColor(i,0,0,0);
  }
  getalEen.show();
  getalTen.show();
  getalHun.show();
}
//logic for displaying correct number in the first ngle digit slot
void handleNumberOnes(){
  for (int i = 0; i < 16;i++){
    if (displayGetal[displayNumber[2]][i] == 1){
      if (i == 0){
        for (int j = 0;j<8;j++){
          getalEen.setPixelColor(j,rgb[0],rgb[1],rgb[2]);
          getalEen.show();
        }
      } else {
        for (int j = (i*8); j<(i*8)+8;j++){
          getalEen.setPixelColor(j,rgb[0],rgb[1],rgb[2]);
          getalEen.show();
        }
      }
    }
  }
}
//logic for displaying correct number in the second digit slot
void handleNumberTens(){
  for (int i = 0; i < 16;i++){
    if (displayGetal[displayNumber[1]][i] == 1){
      if (i == 0){
        for (int j = 0;j<8;j++){
          getalTen.setPixelColor(j,rgb[0],rgb[1],rgb[2]);
          getalTen.show();
        }
      } else {
        for (int j = (i*8); j<(i*8)+8;j++){
          getalTen.setPixelColor(j,rgb[0],rgb[1],rgb[2]);
          getalTen.show();
        }
      }
    }
  }
}
//logic for displaying correct number in the third digit slot
void handleNumberHun(){
  for (int i =0;i<16;i++){
    getalHun.setPixelColor(i,rgb[0],rgb[1],rgb[2]);
  }
  getalHun.show();
}

void setup(){
  //init first neopixel strip
  getalEen.begin();
  getalEen.setBrightness(25);
  getalEen.show();

  //init second neopixel strip
  getalTen.begin();
  getalTen.setBrightness(25);
  getalTen.show();

  //init third neopixel strip
  getalHun.begin();
  getalHun.setBrightness(25);
  getalHun.show();

  //init serial for debugging
  Serial.begin(9600);

  //init button with internal pullup resistor
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);

  //init display to show 00
  handleNumberOnes();
  handleNumberTens();
}
//logic for correctly incrementing the number for display
//by setting the correct values in the array
void incrementDisplay(){
//  Serial.println("increment display before");
//  Serial.print(displayNumber[0]); Serial.print(" ");
//  Serial.print(displayNumber[1]); Serial.print(" ");
//  Serial.print(displayNumber[2]); Serial.println();
  if (displayNumber[2] == 9 && displayNumber[1] != 9){
    displayNumber[1]++;
    tens = true;
    displayNumber[2] = -1;
  } else if ( (displayNumber[1] == 9) && (displayNumber[2] == 9)){
    displayNumber[0] = 1;
    hun = true;
    displayNumber[1] = 0;
    displayNumber[2] = -1;
  }
  
    displayNumber[2]++;
//  Serial.println("increment display after");
//  Serial.print(displayNumber[0]); Serial.print(" ");
//  Serial.print(displayNumber[1]); Serial.print(" ");
//  Serial.print(displayNumber[2]); Serial.println();
}

void loop(){
  //handling what a button press does
  //incrementing the internal array
  //then showing it on the neopixel strip
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW){
    turnOffLed();
    incrementDisplay();
    handleNumberTens();
    handleNumberOnes();
    if (hun == true){
      handleNumberHun();
    }
    //delay for preventing button mashing
    delay(500); 
  }

 timer++;
  //change rgb values after set period of time
  if(timer == 600000){
    rgb[0] = random(1,255);
    rgb[1] = random(1,255);
    rgb[2] = random(1,255);
    handleNumberOnes();
    handleNumberTens();
    if (displayNumber[0] != 0){
      handleNumberTens();
      handleNumberHun();
    }
    timer = 0;
  }
  
}
