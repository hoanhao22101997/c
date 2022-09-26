#define txpin 4
#define txoutput DDRD |= (1<<DDD4)
#define writetx(x) PORTD = ((x)?(PORTD | B00010000):(PORTD &(~(B00010000))))
unsigned int uartcycle = 0;
void uartbegin(unsigned int baud){
  uartcycle = 1.0/baud *1000000;
  writetx(1);
  txoutput;
}
void uart_writestring(char *p){
  int i=0;
  while(p[i] != 0x00){
    uart_writebyte(p[i]);
    i++;
  }
}
void uart_writebyte(uint8_t byteout){
  writetx(0);
  int b;
  delayMicroseconds(uartcycle);
  for(int i=0;i<8;i++){
    b = byteout & 0x01;
    writetx(b);
    byteout = byteout >>1;
    delayMicroseconds(uartcycle);
  }
  writetx(1);
  delayMicroseconds(uartcycle);
    writetx(1);
}
uint8_t x='a';
void setup() {
  Serial.begin(9600);
  uartbegin(9600);
  delay(100);

}

void loop() {
uart_writestring("hello\n");
  delay(300);
//    Serial.print('a');
//    delay(500);

}
