int PIN_LATCH = 2;
int PIN_CLOCK = 3;
int PIN_DATA = 4;
int PIN_MR = 5;
int PIN_OE = 6;
int BUT_R=7;
int BUT_L=8;


int pSt=3;
int r;
int pad_pos=0;
int y_pos=1;
int x_pos=2;
int st_x_pos=0;
int st_y_pos=0;
int BR_STATE=0;	
int x_pos_mirror=0;
int y_pos_mirror=0;
long previousMillis = 0; 
long interval = 100;
float speed = 300;
int pad[]={7,14,28,56,112,224};
byte pad_state[]={7,14,28,56,112,224,224};
byte x_pSt=254;
byte ballPx[]={0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
byte ballPy[]={254,253,251,247,239,223,191,127};
float start=0;
float startD=0;
unsigned long currentMillis = millis();





void setup() 
{
  pinMode(PIN_LATCH, OUTPUT);
  pinMode(PIN_CLOCK, OUTPUT);
  pinMode(PIN_DATA, OUTPUT);
  pinMode(PIN_OE, OUTPUT);
  pinMode(PIN_MR, OUTPUT);
  pinMode(BUT_R, INPUT);
  pinMode(BUT_L, INPUT);
  digitalWrite(PIN_OE, LOW);
  digitalWrite(PIN_MR, HIGH);
  randomSeed(analogRead(12));
}


void loop() 
{ 
  if (millis() - startD > 20000){
    startD = millis(); 
    speed=speed-50;
  }
  paddle();
  ballm();
}

void paddle()
{
  BR_STATE=0;
  if(pSt<6){
    for(int i=0; i<8;i++){
      digitalWrite(PIN_LATCH, LOW);
      shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, x_pSt);
      shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, pad_state[pSt]);
      digitalWrite(PIN_LATCH, HIGH);
      delayMicroseconds(1);
      digitalWrite(PIN_LATCH, LOW);
    } 
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;  
      if(digitalRead(BUT_R)==HIGH && BR_STATE==0){
        BR_STATE=1; 
        pSt++;
        pad_pos=pSt;
        if(pSt>5){
          pSt=0;
        };
      }
      if(digitalRead(BUT_L)==HIGH && BR_STATE==0){
        BR_STATE=1; 
        pSt=pSt-1;
        pad_pos=pSt;
        if(pSt<0){
          pSt=5;
        };
      }
    }
  }
}


void ballm()
{
  switch(r){
  case 1:
    forward_move();
    break;
  case 0:
    left_move();
    break;
  case 2:
    right_move();
    break;
  default : 
    right_move();
    break;
  }

  //-----------------------------------------------------


}
  // Прямая траектория вперед
void forward_move()
{
  loose();   
  if(y_pos<8){
    if(y_pos==7){
      y_pos_mirror=1;
    }
    if(y_pos_mirror==0){
      for(int o=0; o<8;o++){
        digitalWrite(PIN_LATCH, LOW);
        shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, ballPy[y_pos]);
        shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, ballPx[x_pos]);
        digitalWrite(PIN_LATCH, HIGH);
        digitalWrite(PIN_LATCH, LOW);
      }
      if (millis() - start > speed){
        start = millis(); 
        y_pos++;
      }
    }
    else if(y_pos_mirror==1)
    { 
      for(int o=0; o<8;o++)
      {
        digitalWrite(PIN_LATCH, LOW);
        shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, ballPy[y_pos]);
        shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, ballPx[x_pos]);
        digitalWrite(PIN_LATCH, HIGH);
        digitalWrite(PIN_LATCH, LOW);
      }
      if (millis() - start > speed){
        start = millis(); 
        y_pos--;
      }
      if(y_pos_mirror==1 &&y_pos==1 ){
        if(pSt==0 &&(x_pos==0 || x_pos==1 || x_pos==2)){
          x_pos_mirror=0; 
          y_pos_mirror=0;
          st_x_pos=x_pos; 
          st_y_pos=y_pos;
          r=2;
        }
      }

      if(y_pos_mirror==1 && y_pos==1){
        if(pSt==1 &&(x_pos==1 || x_pos==2 || x_pos==3)){
          x_pos_mirror=0; 
          y_pos_mirror=0;
          st_x_pos=x_pos; 
          st_y_pos=y_pos;
          r=random(3);
        }
      }
      if(y_pos_mirror==1 && y_pos==1){
        if(pSt==2 &&(x_pos==2 || x_pos==3 || x_pos==4)){
          x_pos_mirror=0; 
          y_pos_mirror=0;
          st_x_pos=x_pos; 
          st_y_pos=y_pos;
          r=random(3);
        }
      }
      if(y_pos_mirror==1 && y_pos==1){
        if(pSt==3 &&(x_pos==3 || x_pos==4 || x_pos==5)){
          x_pos_mirror=0; 
          y_pos_mirror=0;
          st_x_pos=x_pos; 
          st_y_pos=y_pos;
          r=random(3);
        }
      }
      if(y_pos_mirror==1 && y_pos==1){
        if(pSt==4 &&(x_pos==4 || x_pos==5 || x_pos==6)){
          x_pos_mirror=0; 
          y_pos_mirror=0;
          st_x_pos=x_pos; 
          st_y_pos=y_pos;
          r=random(3);
        }
      }
      if(y_pos_mirror==1 && y_pos==1){
        if(pSt==5 &&(x_pos==5 || x_pos==6 || x_pos==7 )){
          x_pos_mirror=0; 
          y_pos_mirror=0;
          st_x_pos=x_pos; 
          st_y_pos=y_pos;
          r=0;
        }
      }
    }
  }
}
  //Влево
void left_move()
{
  loose(); 
  for(int s=0; s<millis(); s=s+millis())
  {
    if(y_pos<8){
      if(x_pos==0){ 
        x_pos_mirror=1;
      }
      if(y_pos==7){
        y_pos_mirror=1;
      }
      if(x_pos==7){
        x_pos_mirror=2;
      }
      if(x_pos_mirror==0 && y_pos_mirror==0)
      {
        for(int o=0; o<8;o++){
          digitalWrite(PIN_LATCH, LOW);
          shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, ballPy[y_pos]);
          shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, ballPx[x_pos]);
          digitalWrite(PIN_LATCH, HIGH);
          digitalWrite(PIN_LATCH, LOW);
        }
        if (millis() - start > speed){
          start = millis(); 
          y_pos++;
          x_pos--;
        }
      }
      else if(x_pos_mirror==1 && y_pos_mirror==0){ 
        for(int o=0; o<8;o++){
          digitalWrite(PIN_LATCH, LOW);
          shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, ballPy[y_pos]);
          shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, ballPx[x_pos]);
          digitalWrite(PIN_LATCH, HIGH);
          digitalWrite(PIN_LATCH, LOW);
        }
        if (millis() - start > speed){
          start = millis(); 
          y_pos++;
          x_pos++;
        }
      }
      else if(x_pos_mirror==1 && y_pos_mirror==1){
        for(int o=0; o<8;o++){
          digitalWrite(PIN_LATCH, LOW);
          shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, ballPy[y_pos]);
          shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, ballPx[x_pos]);
          digitalWrite(PIN_LATCH, HIGH);
          digitalWrite(PIN_LATCH, LOW);
        }
        if (millis() - start > speed){
          start = millis(); 
          y_pos--;
          x_pos++;
        }
      }   
      else if(x_pos_mirror==2 && y_pos_mirror==1){
        for(int o=0; o<8;o++){
          digitalWrite(PIN_LATCH, LOW);
          shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, ballPy[y_pos]);
          shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, ballPx[x_pos]);
          digitalWrite(PIN_LATCH, HIGH);
          digitalWrite(PIN_LATCH, LOW);
        }
        if (millis() - start > speed){
          start = millis(); 
          y_pos--;
          x_pos--;
        }
      }   
      if(x_pos_mirror==1 && y_pos==1){
        if(pSt==0 &&(x_pos==0 || x_pos==1 || x_pos==2)){
          r=random(3);
          x_pos_mirror=0; 
          y_pos_mirror=0;
          st_x_pos=x_pos; 
          st_y_pos=y_pos;
        }
      }
      if(x_pos_mirror==2 && y_pos==1){
        if(pSt==1 &&(x_pos==1 || x_pos==2 || x_pos==3)){
          r=random(3);
          x_pos_mirror=0; 
          y_pos_mirror=0;
          st_x_pos=x_pos; 
          st_y_pos=y_pos;
        }
      }
      if(x_pos_mirror==2 && y_pos==1){
        if(pSt==2 &&(x_pos==2 || x_pos==3 || x_pos==4)){
          r=random(3);
          x_pos_mirror=0; 
          y_pos_mirror=0;
          st_x_pos=x_pos; 
          st_y_pos=y_pos;
        }
      }
      if(x_pos_mirror==2 && y_pos==1){
        if(pSt==3 &&(x_pos==3 || x_pos==4 || x_pos==5)){
          r=random(3);
          x_pos_mirror=0; 
          y_pos_mirror=0;
          st_x_pos=x_pos; 
          st_y_pos=y_pos;
        }
      }
      if(x_pos_mirror==2 && y_pos==1){
        if(pSt==4 &&(x_pos==4 || x_pos==5 || x_pos==6)){
          r=random(3);
          x_pos_mirror=0; 
          y_pos_mirror=0;
          st_x_pos=x_pos; 
          st_y_pos=y_pos;
        }
      }
      if(x_pos_mirror==1 && y_pos==1){
        if(pSt==5 &&(x_pos==5 || x_pos==6 || x_pos==7 )){
          r=random(3);
          x_pos_mirror=0; 
          y_pos_mirror=0;
          st_x_pos=x_pos; 
          st_y_pos=y_pos;
        }
      }
      if(x_pos_mirror==2 && y_pos==1){
        if(pSt==5 &&(x_pos==5 || x_pos==6 || x_pos==7)){
          r=random(3);
          x_pos_mirror=0; 
          y_pos_mirror=0;
          st_x_pos=x_pos; 
          st_y_pos=y_pos;
        }
      }  
    }
  }
}  

  //Вправо
void right_move(){
  loose(); 
  if(y_pos<8){
    if(x_pos==7){ 
      x_pos_mirror=1;
    }
    if(y_pos==7){
      y_pos_mirror=1;
    }
    if(x_pos==0){
      x_pos_mirror=2;
    }
    if(y_pos==0){
      y_pos_mirror=2;
    }
    if(x_pos_mirror==0 && y_pos_mirror==0){
      for(int o=0; o<8;o++){
        digitalWrite(PIN_LATCH, LOW);
        shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, ballPy[y_pos]);
        shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, ballPx[x_pos]);
        digitalWrite(PIN_LATCH, HIGH);
        digitalWrite(PIN_LATCH, LOW);
      }
      if (millis() - start > speed){
        start = millis(); 
        y_pos++;
        x_pos++;
      }
    }
    else if(x_pos_mirror==1 && y_pos_mirror==0){ 
      for(int o=0; o<8;o++){
        digitalWrite(PIN_LATCH, LOW);
        shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, ballPy[y_pos]);
        shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, ballPx[x_pos]);
        digitalWrite(PIN_LATCH, HIGH);
        digitalWrite(PIN_LATCH, LOW);
      }
      if (millis() - start > speed){
        start = millis(); 
        y_pos++;
        x_pos--;
      }
    }
    else if(x_pos_mirror==1 && y_pos_mirror==1){
      for(int o=0; o<8;o++){
        digitalWrite(PIN_LATCH, LOW);
        shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, ballPy[y_pos]);
        shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, ballPx[x_pos]);
        digitalWrite(PIN_LATCH, HIGH);
        digitalWrite(PIN_LATCH, LOW);
      }
      if (millis() - start >speed){
        start = millis(); 
        y_pos--;
        x_pos--;
      }
    }   
    else if(x_pos_mirror==2 && y_pos_mirror==1){
      for(int o=0; o<8;o++){
        digitalWrite(PIN_LATCH, LOW);
        shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, ballPy[y_pos]);
        shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, ballPx[x_pos]);
        digitalWrite(PIN_LATCH, HIGH);
        digitalWrite(PIN_LATCH, LOW);
      }
      if (millis() - start > speed){
        start = millis(); 
        y_pos--;
        x_pos++;
      }
    }   
    if(x_pos_mirror==1 && y_pos==1){
      if(pSt==0 &&(x_pos==0 || x_pos==1 || x_pos==2)){
        r=random(3); 
        x_pos_mirror=0; 
        y_pos_mirror=0;
        st_x_pos=x_pos; 
        st_y_pos=y_pos;
      }
    }
    if(x_pos_mirror==2 && y_pos==1){
      if(pSt==0 &&(x_pos==0 || x_pos==1 || x_pos==2)){
        r=random(3);
        x_pos_mirror=0; 
        y_pos_mirror=0;
        st_x_pos=x_pos; 
        st_y_pos=y_pos;
      }
    }
    if(x_pos_mirror==2 && y_pos==1){
      if(pSt==1 &&(x_pos==1 || x_pos==2 || x_pos==3)){
        r=random(3);
        x_pos_mirror=0; 
        y_pos_mirror=0;
        st_x_pos=x_pos; 
        st_y_pos=y_pos;
      }
    }
    if(x_pos_mirror==2 && y_pos==1){
      if(pSt==2 &&(x_pos==2 || x_pos==3 || x_pos==4)){
        x_pos_mirror=0; 
        y_pos_mirror=0;
        st_x_pos=x_pos; 
        st_y_pos=y_pos;
        r=random(3);
      }
    }
    if(x_pos_mirror==2 && y_pos==1){
      if(pSt==3 &&(x_pos==3 || x_pos==4 || x_pos==5)){
        r=random(3);
        x_pos_mirror=0; 
        y_pos_mirror=0;
        st_x_pos=x_pos; 
        st_y_pos=y_pos;
      }
    }
    if(x_pos_mirror==2 && y_pos==1){
      if(pSt==4 &&(x_pos==4 || x_pos==5 || x_pos==6)){
        r=random(3);
        x_pos_mirror=0; 
        y_pos_mirror=0;
        st_x_pos=x_pos; 
        st_y_pos=y_pos;
      }
    }
    if(x_pos_mirror==1 && y_pos==1){
      if(pSt==5 &&(x_pos==5 || x_pos==6 || x_pos==7 )){
        r=random(3);
        x_pos_mirror=0; 
        y_pos_mirror=0;
        st_x_pos=x_pos; 
        st_y_pos=y_pos;
      }
    }
  }
}   

void loose(){

  if(y_pos==0 && y_pos_mirror==1){
    y_pos=1;
    x_pos=4;
    y_pos_mirror=0;
    y_pos_mirror=0;
    start=0;
    startD=0;
    speed=300;
    for(int i=0; i<8;i++){
      digitalWrite(PIN_LATCH, LOW);
      shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, 0);
      for(int j=0; j<8; j++){
        shiftOut(PIN_DATA, PIN_CLOCK, MSBFIRST, 255);
        digitalWrite(PIN_LATCH, HIGH);
        delay(10);
        digitalWrite(PIN_LATCH, LOW); 
      }
    }
  }
}






