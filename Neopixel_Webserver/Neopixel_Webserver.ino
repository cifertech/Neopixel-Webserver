#include <Adafruit_NeoPixel.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

// Webserver Config
const char *ssid = "C1F3R";
const char *password = "314159265";
ESP8266WebServer server ( 80 );

// Neopixel Config
#define NeoPIN D4
#define NUM_LEDS 8
int brightness = 150;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, NeoPIN, NEO_RGB + NEO_KHZ800);


const int led = 13;

void setup ( void ) {

  Serial.begin ( 115200 );

  // ##############
  // NeoPixel start
  Serial.println();
  strip.setBrightness(brightness);
  strip.begin();
  strip.show(); 
  delay(50);
  Serial.println("NeoPixel started");
  
  // #########
  // Webserver
  pinMode ( led, OUTPUT );
  digitalWrite ( led, 0 );
  
  WiFi.begin ( ssid, password );
  Serial.println ( "" );

  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  Serial.println ( "" );
  Serial.print ( "Connected to " );
  Serial.println ( ssid );
  Serial.print ( "IP address: " );
  Serial.println ( WiFi.localIP() );

  if ( MDNS.begin ( "esp8266" ) ) {
    Serial.println ( "MDNS responder started" );
  }

  // what to do with requests
  server.on ( "/", handleRoot );
  server.onNotFound ( handleNotFound );
  server.begin();

  
  
  Serial.println ( "HTTP server started" );
}

void loop ( void ) {
  // waiting fo a client
  server.handleClient();
}


void handleRoot() {
  Serial.println("Client connected");
  digitalWrite ( led, 1 );
  
  // data from the colorpicker (e.g. #FF00FF)
  String color = server.arg("c");
  Serial.println("Color: " + color);
  // setting the color to the strip 
  setNeoColor(color);

  // building a website
  char temp[5000];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;
  char clr [7];
  color.toCharArray(clr, 7);
  snprintf ( temp, 5000,

"<!DOCTYPE html>\n<html>\n\
  <head>\n\
    <title>wifi pixel</title>\n\
    <style>\
      body { background-color: #F08262; font-family: Arial; Color: #fff; }\
      h1 {text-align: center;}\
      p {text-align: center;}\
      form {text-align: center;}\
    </style>\n\
    <meta name=\"viewport\" content=\"width=device-width, height=device-height, initial-scale=1.0, user-scalable=0, minimum-scale=1.0, maximum-scale=1.0\" />\n\
  </head>\n\
  <body>\n\
    <h1>CiferTech</h1>\n\
    <p>pick the color!</p>\n\
    \n\
    <form action=\"\" name=\"pick\" method=\"post\">\n\
    <input type=\"color\" name=\"c\" value=\"%02d\" onchange=\"document.forms['pick'].submit();\" />\n\
    &nbsp;<span onclick=\"document.forms['pick'].submit();\" style=\"font-size:16pt;\"> </span>\n\
    </form>\n\
    \n\
  </body>\
</html>",

    hr, min % 60, sec % 60, clr
  );
  server.send ( 200, "text/html", temp );
  digitalWrite ( led, 0 );
}

void handleNotFound() {
  digitalWrite ( led, 1 );
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }

  server.send ( 404, "text/plain", message );
  digitalWrite ( led, 0 );
}



void setNeoColor(String value){
  Serial.print("Setting Neopixel...");
  // converting Hex to Int
  int number = (int) strtol( &value[1], NULL, 16);
  
  // splitting into three parts
  int r = number >> 16;
  int g = number >> 8 & 0xFF;
  int b = number & 0xFF;
  
  // DEBUG
  Serial.print("RGB: ");
  Serial.print(r, DEC);
  Serial.print(" ");
  Serial.print(g, DEC);
  Serial.print(" ");
  Serial.print(b, DEC);
  Serial.println(" ");
  
  // setting whole strip to the given color
  for(int i=0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color( g, r, b ) );
  }
  // init
  strip.show();
  
  Serial.println("on.");
}
