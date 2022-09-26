#include"SoftwareSerial.h"
#include"PubSubClient.h"
#include"ESP8266WiFi.h"
WiFiClient esp;
PubSubClient client(esp);
const char* ssid="HaoHao";
const char* pass="hoanhao159";
const char* server="192.168.1.6";
String topicsub="topicsub";
String topicpub="topicpub";
int port=1883;
const int RX=D5;
const int TX=D6;
String ChuoiSendWebJson="";
SoftwareSerial myserial(RX,TX);
String data="";
String data1="";
bool trangthaiinput=false;
int t,h;
long last=0;
int bien1=0,bien2=0,bienmode=0;
void setup()
{
  Serial.begin(9600);
  myserial.begin(9600);
  WiFi.begin(ssid,pass);
  while(WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.print(".");
  }
  Serial.println(" kết nối WiFi Thành Công ");
  client.setServer(server,port);
  delay(10);
  client.setCallback(callback);
  delay(10);
  last= millis();
  myserial.println("on");
  myserial.flush();
}
void loop()
{
  if(!client.connected()){
    reconnect();
  }
  client.loop();
  if(millis()-last >=1000){
    readuart();
    DataJson(String(t),String(h),String(bien1),String(bien2),String(bienmode));
    
    last=millis();
  }

}
void readuart(){
   while(myserial.available()){
    char doc=myserial.read();
    data+=doc;
    if(doc=='\n'){
      trangthaiinput=true;
    }
    if(trangthaiinput==true){
      Serial.println(data);
      xulidata(data);
      data="";
      trangthaiinput=false;
    }
  }
}
void xulidata(String data){
  int TimA=data.indexOf("A");
  int TimB=data.indexOf("B");
  int TimC=data.indexOf("C");
  int TimD=data.indexOf("D");
  int TimE=data.indexOf("E");
  int TimF=data.indexOf("F");
  if(TimA >=0 && TimB >=0){
    String bienab =data.substring(TimA+1,TimB);
    t=bienab.toInt();
  }
  if(TimB >=0 && TimC >=0){
    String bienbc=data.substring(TimB+1,TimC);
    h=bienbc.toInt();
  }
   if(TimC >=0 && TimD >=0){
    String biencd=data.substring(TimC+1,TimD);
    bien1=biencd.toInt();
  }
   if(TimD >=0 && TimE >=0){
    String biende =data.substring(TimD+1,TimE);
    bien2=biende.toInt();
  }
  if(TimE >=0 && TimF >=0){
    String bienef =data.substring(TimE+1,TimF);
    bienmode=bienef.toInt();
  }
}
void reconnect(){
  while(!client.connected()){
    String clientid=String(random(0xffff),HEX);
    if(client.connect(clientid.c_str())){
      client.subscribe(topicsub.c_str());
    }
  }
}
void callback(char* a,byte* payload,unsigned int length){
  for(int i=0;i<length;i++){
    data1+=char(payload[i]);
  }
  myserial.print(data1);
  myserial.flush();
  Serial.println(data1);
  data1="";
}
void DataJson( String sensor1 ,  String sensor2 ,  String sensor3 , String sensor4 , String sensor5)
{

  ChuoiSendWebJson = "{\"ND\":\"" + String(sensor1) + "\"," +
                     "\"DA\":\"" + String(sensor2) + "\"," +
                     "\"TB1\":\"" + String(sensor3) + "\"," +
                     "\"TB2\":\"" + String(sensor4) + "\"," +
                     "\"Mode\":\"" + String(sensor5) + "\"}";

  client.publish(topicpub.c_str(),ChuoiSendWebJson.c_str());
  Serial.println(ChuoiSendWebJson.c_str());
}
