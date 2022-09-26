#define rxpin 5
#define rx_input DDRD&=~(1<<DDD5)
#define readdata() ((PIND &(1<<PIND5))?HIGH:LOW)
bool status = false;
int uartcycle =0;
int i=0;
char data[30];
void uartbegin(int baud){
  uartcycle = 1.0/baud *1000*1000;
  rx_input;
}
uint8_t uart_readbyte(){
  uint8_t byte_in = 0;
  int res=0;
  while(readdata() == HIGH);
  delayMicroseconds(uartcycle+uartcycle/2);
  for(int i=0;i<8;i++){
    res = readdata();
    res= res<<i;
    byte_in |= res;
    delayMicroseconds(uartcycle); 
  }
  res = readdata();
  if(res == 0){
    return 0;
  }
  return byte_in;
}
uint8_t x;
void clearstring(char *p){
  for(int i=0;i<strlen(p);i++){
    p[i]=0;
  }
}
void readstring(char x){
    if( x != '\n'){
    data[i] = char(x);
    i++;
  }else{
    data[i+1]='\0';
  Serial.println(data);
  clearstring(data);
  i=0;
  }
}
void setup() {
  Serial.begin(9600);
  uartbegin(9600);
}
void loop() {
  x = uart_readbyte();
  readstring(x);
//Serial.println("hello world");
//delay(300);
}
