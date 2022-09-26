#define writePIND(x,i) PORTD =((x) ? (PORTD | (1<<i)):(PORTD&(~(1<<i)))) 
char led7doan[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90 }; 
int nd=0;
int da=0;
char buf[1];
void doccambien(){
  nd++;
  da+=2;
  if(nd== 99){
    nd=0;
  }
  if(da == 99){
    da=0;
  }
}
void hc595(char *x,int n){
  for(int j=0;j<n;j++){
  char b = *(x+n-j-1);
  for(int i=0;i<8;i++){
     writePIND(b & (0x80>>i),1);
     writePIND(1,2);
     writePIND(0,2);
  }
  writePIND(1,0);
  writePIND(0,0);
  }
}
void setup() {
  DDRD |= 0xFF;

  
}
void loop() {
  doccambien();
  buf[0]=0x02;
  hc595(buf,1);
  delay(500);
    buf[0]=0x00;
  hc595(buf,1);
  delay(500);
}
 
