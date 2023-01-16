/*
  Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-http-get-post-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  
  Code compatible with ESP8266 Boards Version 3.0.0 or above 
  (see in Tools > Boards > Boards Manager > ESP8266)
*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
// #include <ESP8266WebServer.h>
// #include <string.h>  


//Your Domain name with URL path or IP address with path
String serverName = "http://localhost/waterlevel/api.php";

const char *ssid = "JEMPOLAN EATERY 1";  //Nama Wifi
const char *password = "JEMPOLAN5758"; // pass wifi

WiFiClient client; 
HTTPClient http;

void setup() {
  delay(1000);
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}

void loop() {
  kirim_data2();
  if (Serial.available()) {
    int a = Serial.parseInt();

    if (a > 0) {
      kirim_data();
    }
  }
  delay(1000);
}

void kirim_data() {

  int tegangan, arus, suhu, kelembaban;
  bool test = false;
  int sensor12 = random(0, 12); 
  int sensor22 = random(0, 3); 
  suhu = random(28, 32); 
  kelembaban = random(50, 95); 
  // String data = "temperature=" + String(temperature) + "&humidity=" + String(humidity);
  String postData = (String)"sensor1=" + sensor12 + "&sensor2=" + sensor22
                    + "&waterpump=" + test;                 
  WiFiClient client;  
  
  HTTPClient http;
  http.begin(client, serverName);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpCode = http.POST(postData);
  String payload = http.getString();
  int stCode = http.GET();
  Serial.println(postData);
  Serial.println(payload);

  http.end();
}

void kirim_data2() {

  int sensor1 = 20;
  int sensor2 = 25;
  bool waterpump = false;
  String postData;
  String postData2;

  // postData = "sensor1=" + sensor1 + "&sensor2=" + sensor2 + "&waterpump=" + waterpump;
  postData2 = "sensor1=210&sensor2=99&waterpump=0";
  
  http.begin(client,"http://localhost/waterlevel/api.php");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpCode = http.POST(postData2);
  String payload = http.getString();

  Serial.println(postData2);
  int stCode = http.GET();
  Serial.println(stCode);
  // Serial.println(http.payload);
  Serial.println(payload);

  http.end();
}