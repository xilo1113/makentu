//http://arduino.esp8266.com/stable/package_esp8266com_index.json,https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
#include <Wire.h>
#include <BH1750.h>
#include <math.h>
#include <ArduinoJson.h>
#define GY30_ADDRESS 0x23
BH1750 lightMeter;
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);
#include <WiFi.h>

const char* ssid = "MI10T";
const char* password = "123212321";
String data ;
String response;
String weather;
int color = 0;
int bright = 0;
void setup() {
  
  pinMode(2, OUTPUT);
  pinMode(4, INPUT);
  Wire.begin();
  Wire.setClock(400000);
  lightMeter.begin();
  Serial.println(F("BH1750 Test"));
    // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(2,HIGH);
}
#include <HTTPClient.h>
String httpGETRequest(String serverName) {
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "--"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
void loop() {
  StaticJsonDocument<2000> doc;
  weather = httpGETRequest("http://api.weatherapi.com/v1/current.json?key=5bb0286661684d428ab70922233004&q=Panchiao&aqi=no");
  DeserializationError error = deserializeJson(doc, weather);
  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  delay(1000);
  //////////////////////////////////////////////////////////////////////////////////////
  String sss = ""; //just use for start
  String serverlink = sss+"http://192.168.43.186/lightmeter?"+"color="+color+"&bright="+bright;
  response = httpGETRequest(serverlink);
  delay(1000);
  int lux = (int)lightMeter.readLightLevel();
  Serial.print(" lux: ");
  Serial.print(lux);
  Serial.println();

  if( lux > 3000) bright = 10;
  else if(lux<0)  bright = 100;
  else bright = 100-(25 - pow(12.5,1/(lux+1))-pow(12.5,1/(lux+2))+ 75*lux/1000);

  String weather_text = doc["current"]["condition"]["text"]; // Overcast Mist Patchy rain possible Moderate or heavy rain shower   Torrential rain shower
  //Light rain shower Heavy rain Moderate rain Moderate rain at times Light rain Patchy light rain Light drizzle Patchy light drizzle
  String times = doc["current"]["last_updated"];
  String cloudy = doc["current"]["cloud"];
  String real_time = "";
  int real_time_int = 0;
  for(int i = 11;i<13;i++)
  {
    real_time += times[i];
    lux= times[i]-48;
    real_time_int = 10*real_time_int + lux;
  }
  

  
  for(int i=0;i<=23;i++){
    if( real_time_int>=4 && real_time_int<=23){
      if(real_time_int == i)
        color = 100 - abs(i-12.5)*12;
    }
    else
      color = 0; // 0是最黃 晚上偏黃
  }
  color = color*7/10 +(100-atoi(cloudy.c_str())) *3/10;
//  if(
//  if(weather_text =="sunny") bright = 40;
//  else if(weather_text =="Partly cloudy") bright = 60;
//  else if(weather_text =="Cloudy") bright = 60;
//  else if(weather_text =="Overcase") bright = 80;
//  else if(weather_text =="Mist") bright = 80;
//  else bright = 100;
//  
  // Overcast Mist Patchy rain possible Moderate or heavy rain shower   Torrential rain shower
  //Light rain shower Heavy rain Moderate rain Moderate rain at times Light rain Patchy light rain Light drizzle Patchy light drizzle
  
  if(color < 0){
    color = 0;
  }  
  Serial.print("color");
  Serial.print(color);
  Serial.print("bright");
  Serial.print(bright);
  Serial.println("");
  
}
