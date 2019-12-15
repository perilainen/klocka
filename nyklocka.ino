#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include "WiFiManager.h"          //https://github.com/tzapu/WiFiManager

#include <NTPClient.h>

#include <Timezone.h> 
#include <FastLED.h>


#define LED_PIN     5
#define NUM_LEDS    110
CRGB leds[NUM_LEDS];
int brightness = 100; // Initial brightness
ESP8266WebServer server(80); //Server on port 80

TimeChangeRule CEST = {"CEST", Last, Sun, Mar, 2, 120};     // Central European Summer Time
TimeChangeRule CET = {"CET ", Last, Sun, Oct, 3, 60};       // Central European Standard Time
Timezone CE(CEST, CET);

unsigned int localPort = 2390;  
IPAddress timeServerIP; // time.nist.gov NTP server address
 
const char* ntpServerName = "pool.ntp.org";
//uint8_t brightness, red, green, blue;
String LocalTime ="";
String page = "";
WiFiUDP udp;
NTPClient timeClient(udp, ntpServerName);//, 0, 60000);

//int red = 1;
//int green = 1;
//int blue = 1;





void handleRoot() {
  page = "<h4>"+String(LocalTime)+"</h4></br><h4>"+
  String(brightness)+"</h4></br>"+
  "<form>Brighness:<br><input value="+brightness+"></form> "+
  "<form action=\"/LED\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form>";
 //String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", page); //Send web page
}
void handleLED() {                          // If a POST request is made to URI /LED
  brightness=brightness+1;      // Change the state of the LED
  server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
}

void setup() {

 
  // put your setup code here, to run once:
  Serial.begin(9600);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);
  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  //reset settings - for testing
  //wifiManager.resetSettings();

  //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
  wifiManager.setAPCallback(configModeCallback);
  wifiManager.autoConnect("KLOCKA");
  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  if(!wifiManager.autoConnect()) {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
   // ESP.reset();
    delay(1000);
  } 

  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");
  timeClient.begin();
  server.on("/", handleRoot);      //Which routine to handle at root location
  server.on("/LED", HTTP_POST, handleLED);
  server.begin();    
  
  
}



void loop() {
  
  Serial.println(brightness);
  //red = storage.red;
  //green = storage.green;
  //blue = storage.blue;
  server.handleClient();   
  timeClient.update();
  printDateTime(CE,timeClient.getEpochTime(),"Stockholm2");
  lightClock(CE,timeClient.getEpochTime());
  
  Serial.println("TEST");
  for (int i = 1; i <=7; i++){
    
    leds[i] = CRGB (brightness,brightness,brightness);
  }
  delay(1000);
  Serial.println("Showing in loop");
  FastLED.show();
  Serial.println("Loop finished");
  delay(1000);
}

// given a Timezone object, UTC and a string description, convert and print local time with time zone
void printDateTime(Timezone tz, time_t utc, const char *descr)
{
    char buf[40];
    char m[4];    // temporary storage for month string (DateStrings.cpp uses shared buffer)
    TimeChangeRule *tcr;        // pointer to the time change rule, use to get the TZ abbrev

    time_t t = tz.toLocal(utc, &tcr);
    
    strcpy(m, monthShortStr(month(t)));
    sprintf(buf, "%.2d:%.2d:%.2d %s %.2d %s %d %s",
        hour(t), minute(t), second(t), dayShortStr(weekday(t)), day(t), m, year(t), tcr -> abbrev);
    LocalTime = buf;
    Serial.print(buf);
    Serial.print(' ');
    Serial.println(descr);
}
void lightClock(Timezone tz, time_t utc ){
  Serial.println("lightning clock");
  for (int i = 1; i<=10; i++){
    leds[i] = CRGB (200,200,200); 
  }
  char buf[40];
    char m[4];    // temporary storage for month string (DateStrings.cpp uses shared buffer)
    TimeChangeRule *tcr;        // pointer to the time change rule, use to get the TZ abbrev

    time_t t = tz.toLocal(utc, &tcr);
    strcpy(m, monthShortStr(month(t)));

  if (minute(t)>=25){
    lightHour(1+hour(t)%12);
  }
  else{
    lightHour(hour(t)%12);
  }
  
  
  
  lightMinutes(minute(t)/5 *5);
  Serial.println(leds[1]);
  //FastLED.show();
  Serial.println("Fastled Show");
  
  
}

void lightHour(int our){
  Serial.print("Lightning: dddd: ");
  Serial.print(our);
  for (int i = 55; i <=109; i++){
    
    leds[i] = CRGB (0,0,0);
  }
  switch (our){
    
    
    case 1:
      for (int i = 63; i<=65; i++){
        leds[i] = CRGB (brightness,brightness,brightness);  
      }
      
      break;
    case 2:
      for (int i = 55; i<=57; i++){
        leds[i] = CRGB (brightness,brightness,brightness);  
      }
      break;
    case 3:
      for (int i = 66; i<=68; i++){
        leds[i] = CRGB (brightness,brightness,brightness); 
      }
      break;
    case 4:
      for (int i = 73; i<=76; i++){
        leds[i] = CRGB (brightness,brightness,brightness);  
      }
      break;
    case 5:
      for (int i = 85; i<=87; i++){
        leds[i] = CRGB (brightness,brightness,brightness);  
      }
      break;
    case 6:
      for (int i = 77; i<=79; i++){
        leds[i] = CRGB (brightness,brightness,brightness);
        //FastLED.show();  
      }
      break;
    case 7:
      for (int i = 88; i<=90; i++){
        leds[i] = CRGB (brightness,brightness,brightness);  
      }
      break;
    case 8:
    
      for (int i = 91; i<=94; i++){
        leds[i] = CRGB (brightness,brightness,brightness);
      }
      break;
    case 9:
      for (int i = 96; i<=98; i++){
        leds[i] = CRGB (brightness,brightness,brightness); 
      }
      break;
    case 10:
      for (int i = 107; i<=109; i++){
        leds[i] = CRGB (brightness,brightness,brightness); 
      }
      break;
    case 11:
      for (int i = 103; i<=106; i++){
        leds[i] = CRGB (brightness,brightness,brightness); 
      }
      break;
    case 12:
      for (int i = 99; i<=102; i++){
        leds[i] = CRGB (brightness,brightness,brightness); 
      }
      break;
  }
  
}

void lightMinutes(int minutes){
  Serial.print(":");
  Serial.println(minutes);
  for (int i = 11; i <=54; i++){
    leds[i] = CRGB (0,0,0);
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
  for (int i = 14; i <= 15; i++){
        leds[i] = CRGB (brightness,brightness,brightness);
  }
}

void light15(){
  for (int i = 22; i <= 26; i++){
        leds[i] = CRGB (brightness,brightness,brightness);
  }
}

void light20(){
  for (int i = 39; i <= 43; i++){
        leds[i] = CRGB (brightness,brightness,brightness);
  }
}

void light5(){
  for (int i = 19; i <= 21; i++){
        leds[i] = CRGB (brightness,brightness,brightness); 
  }
}

void lightOver(){
  for (int i = 44; i <= 47; i++){
    leds[i] = CRGB (brightness,brightness,brightness);
  }
}

void lightIn(){
    leds[35] = CRGB (brightness,brightness,brightness); 
  
}
void lightHalv(){
  for (int i = 51; i <= 54; i++){
    leds[i] = CRGB (brightness,brightness,brightness);
  }
}
