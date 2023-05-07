//http://arduino.esp8266.com/stable/package_esp8266com_index.json,https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <BH1750.h>
#include <math.h>
#include <ArduinoJson.h>
#define GY30_ADDRESS 0x23
BH1750 lightMeter;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x60);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);
#include <WiFi.h>

const char* ssid = "MI10T";
const char* password = "123212321";
String response;
int L11,L12,L21,L22,L31,L32,L41,L42;
void DecodeRes(String res){
  L11 = (res[0] - '0')*10 + (res[1] - '0');
  L12 = (res[2] - '0')*10 + (res[3] - '0');
  L21 = (res[4] - '0')*10 + (res[5] - '0');
  L22 = (res[6] - '0')*10 + (res[7] - '0');
  L31 = (res[8] - '0')*10 + (res[9] - '0');
  L32 = (res[10] - '0')*10 + (res[11] - '0');
  L41 = (res[12] - '0')*10 + (res[13] - '0');
  L42 = (res[14] - '0')*10 + (res[15] - '0');
}
void WritePWM(int bright,int color,int id){
  bright = bright*40; //4096/100
  // int w1 = bright /(1 + exp(-0.06 * (100-color) + 3));
  // int w2 = bright /(1 + exp(-0.1 * color + 5));
  int w1 = bright * (99-color) / 100;
  int w2 = bright * color / 100;
  w1 = max(0,w1);
  w1 = min(4000,w1);
  w2 = max(0,w2);
  w2 = min(4000,w2);
  w1 = w1 *10 / 25;
  w2 = w2 *10 / 25;
  pwm.setPWM(id*2-1, 0, w1);//w
  pwm.setPWM(id*2-2, 0, w2);//y
  // Serial.print(w1);
  // Serial.print("  ");
  // Serial.println(w2);
}
void setup() {
  
  
  pinMode(4, INPUT);
  pinMode(2,OUTPUT);
  Serial.println("16 channel PWM test!");
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(2000);  // This is the maximum PWM frequency
  pwm.setOutputMode(true);// true for totempole mode(push and pull), false for open drain mode
  Wire.begin();
  Wire.setClock(400000);
  lightMeter.begin();
  for(int i = 0;i<8;i++){
    pwm.setPWM(i, 0, 0);
  }

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
String httpGETRequest(const char* serverName) {
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "5050505050505050"; 
  
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


  //////////////////////////////////////////////////////////////////////////////////////
  response = httpGETRequest("http://192.168.43.186/blub");
  //Serial.print(response);
  DecodeRes(response);
  WritePWM(L11,L12,1);
  WritePWM(L21,L22,2);
  WritePWM(L31,L32,3);
  WritePWM(L41,L42,4);
  Serial.println();
  delay(1000);
   
}
