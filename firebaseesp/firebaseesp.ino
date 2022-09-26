#include"ESP8266WiFi.h"
#include"FirebaseESP8266.h"
#define ssid "HaoHao"
#define pass "hoanhao159"
FirebaseData firebase;
#define host "esp82266-54add-default-rtdb.firebaseio.com"
#define auth "igYk4leDkPYiY0UPCmDWt1bx4DvYMdUtzvY90vUn"
String path = "/";
int nhietdo=0;
int doam=0;
long last =0;
long last1 =0;
void capnhatdata(){
  Firebase.setInt(firebase,path+"/nhietdo",nhietdo);
  Firebase.setInt(firebase,path+"/doam",doam);
}
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid,pass);
  Firebase.begin(host,auth);
  last = millis();
  last1 = millis();
  

}

void loop() {
  if(last - millis() >=1000){
  capnhatdata();
  doam++;
  nhietdo++;
  last =0;
  }

}
