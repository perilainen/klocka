#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    110

CRGB leds[NUM_LEDS];
int brightness = 240; // Initial brightness

int timmar =2;
int minuter = 0;
int sekunder = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);
  Serial.println("setting up");
  int timmar =2;
int minuter = 0;
int sekunder = 0;
  
}

void loop() {
  Serial.println(timmar);
  Serial.println(minuter);
  Serial.println(sekunder);
    // put your main code here, to run repeatedly:
  minuter=minuter+1;
  Serial.print("seconds");
  Serial.println(sekunder);
  delay(1000);
  if(sekunder==60){
  sekunder=0;
  minuter=minuter+1;

 }
   
 if(minuter==60)
 {
  minuter=0;
  timmar=timmar+1;
 }
 if(timmar==13)
 {
  timmar=1;
 }
 lightClock(timmar,minuter);

}

void lightClock(int hour, int minutes){
  
  lightHour(hour);
  
  lightMinutes(minutes/5 *5);
  
  
}

void lightHour(int our){
  Serial.print("sekunder är: ");
  Serial.println(sekunder);
  for (int i = 55; i <=109; i++){
    
    leds[i] = CRGB (0,0,0);
    FastLED.show();
  }
  Serial.print("sekunder är nu: ");
  Serial.println(sekunder);
  switch (our){
    
    
    case 1:
      for (int i = 54; i<=56; i++){
        leds[i] = CRGB (brightness,brightness,brightness);
        FastLED.show();  
      }
      
      break;
    case 2:
    Serial.print("sekunder är: ");
  Serial.println(sekunder);
      for (int i = 56; i<=58; i++){
        leds[i] = CRGB (brightness,brightness,brightness);
        FastLED.show();  
        Serial.print("sekunder är: ");
  Serial.println(sekunder);
      }
      
    case 3:
      for (int i = 67; i<=69; i++){
        leds[i] = CRGB (brightness,brightness,brightness);
        FastLED.show();  
      }
      break;
    case 4:
      for (int i = 74; i<=77; i++){
        leds[i] = CRGB (brightness,brightness,brightness);
        FastLED.show();  
      }
      break;
    case 5:
      for (int i = 86; i<=88; i++){
        leds[i] = CRGB (brightness,brightness,brightness);
        FastLED.show();  
      }
      break;
    case 6:
      for (int i = 78; i<=80; i++){
        leds[i] = CRGB (brightness,brightness,brightness);
        FastLED.show();  
      }
      break;
    case 7:
      for (int i = 89; i<=91; i++){
        leds[i] = CRGB (brightness,brightness,brightness);
        FastLED.show();  
      }
      break;
    case 8:
      for (int i = 92; i<=95; i++){
        leds[i] = CRGB (brightness,brightness,brightness);
        FastLED.show();  
      }
      break;
    case 9:
      for (int i = 97; i<=99; i++){
        leds[i] = CRGB (brightness,brightness,brightness);
        FastLED.show();  
      }
      break;
    case 10:
      for (int i = 108; i<=110; i++){
        leds[i] = CRGB (brightness,brightness,brightness);
        FastLED.show();  
      }
      break;
    case 11:
      for (int i = 104; i<=107; i++){
        leds[i] = CRGB (brightness,brightness,brightness);
        FastLED.show();  
      }
      break;
    case 12:
      for (int i = 100; i<=103; i++){
        leds[i] = CRGB (brightness,brightness,brightness);
        FastLED.show();  
      }
      break;
  }
  
}

void lightMinutes(int minutes){
  Serial.print("lighting minutes: ");
  Serial.println(minutes);
  for (int i = 12; i <=55; i++){
    leds[i] = CRGB (0,0,0);
    FastLED.show();
  }
  switch (minutes){
    case 5:
      lightOver();
      light5();
      break;
    case 10:
      light10();
      lightOver();
      break;
    case 15:
      light15();
      lightOver();
      break;
    case 20:
      light20();
      lightOver();
      break;
    case 25:
      light5();
      lightIn();
      lightHalv();
      break;
    case 30:
      lightHalv();
      break;
    case 35:
      light5();
      lightOver();
      lightHalv();
      break;
    case 40:
      light20();
      lightIn();
      break;
    case 45:
      light15();
      lightIn();
      break;
    case 50:
      light10();
      lightIn();
      break;
    case 55:
      light5();
      lightIn();
  }
  
}
void light10(){
  for (int i = 14; i <= 16; i++){
        leds[i] = CRGB (brightness,brightness,brightness);
        FastLED.show(); 
  }
}

void light15(){
  for (int i = 23; i <= 27; i++){
        leds[i] = CRGB (brightness,brightness,brightness);
        FastLED.show();
  }
}

void light20(){
  for (int i = 40; i <= 44; i++){
        leds[i] = CRGB (brightness,brightness,brightness);
        FastLED.show(); 
  }
}

void light5(){
  for (int i = 20; i <= 22; i++){
        leds[i] = CRGB (brightness,brightness,brightness);
        FastLED.show(); 
  }
}

void lightOver(){
  for (int i = 45; i <= 48; i++){
    leds[i] = CRGB (brightness,brightness,brightness);
    FastLED.show(); 
  }
}

void lightIn(){
    leds[36] = CRGB (brightness,brightness,brightness);
    FastLED.show(); 
  
}
void lightHalv(){
  for (int i = 52; i <= 55; i++){
    leds[i] = CRGB (brightness,brightness,brightness);
    FastLED.show(); 
  }
}
