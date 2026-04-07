#include <IRremote.h>

//мотори 
//вілво
#define A_2A A2 // назад
#define A_1A A3 // вперед
//вправо
#define B_1A A5 // вперед
#define B_2A A4 // назад

//сенсори
#define left_sensor 13
#define right_sensor 12

//ІЧ приймач
#define IR_reciver 8

unsigned long code = 0;

void setup() {
   Serial.begin(9600);
   pinMode(A_2A, OUTPUT);
   pinMode(A_1A, OUTPUT);
   pinMode(B_2A, OUTPUT);
   pinMode(B_1A, OUTPUT);

   analogWrite(A_2A, 0);
   analogWrite(A_1A, LOW);
   analogWrite(B_2A, LOW);
   analogWrite(B_1A, LOW);

   IrReceiver.begin(IR_reciver, ENABLE_LED_FEEDBACK);
}

void loop() {
   //sensor_check();
   if(IrReceiver.decode()){
     code = IrReceiver.decodedIRData.decodedRawData;
     Serial.println(code, HEX);

     check();
     
     IrReceiver.resume();
   }
}

void check(){
  if(code == 0xF50ABF00){//впред
    analogWrite(A_2A, 0);
    analogWrite(A_1A, 255);
    analogWrite(B_2A, 0);
    analogWrite(B_1A, 255);
  }
  else if(code == 0xF708BF00){//назад
    analogWrite(A_2A, 255);
    analogWrite(A_1A, 0);
    analogWrite(B_2A, 255);
    analogWrite(B_1A, 0);
  }
  else if(code == 0xFB04BF00){//вліво
    analogWrite(A_2A, 0);
    analogWrite(A_1A, 255);
    analogWrite(B_2A, 255);
    analogWrite(B_1A, 0);
  }
  else if(code == 0xF906BF00){//вправо
    analogWrite(A_2A, 255);
    analogWrite(A_1A, 0);
    analogWrite(B_2A, 0);
    analogWrite(B_1A, 255);
  }
  else if(code == 0xFF00BF00){//стоп
    analogWrite(A_2A, 0);
    analogWrite(A_1A, 0);
    analogWrite(B_2A, 0);
    analogWrite(B_1A, 0);
  }
  //sensor_check();
}

/*void sensor_check(){
  if(digitalRead(left_sensor) == true){
    analogWrite(A_2A, HIGH);
    analogWrite(A_1A, LOW);
    analogWrite(B_2A, HIGH);
    analogWrite(B_1A, LOW);
    delay(1500);
    analogWrite(A_2A, LOW);
    analogWrite(A_1A, LOW);
    analogWrite(B_2A, LOW);
    analogWrite(B_1A, LOW);
  }
  if(digitalRead(right_sensor) == true){
    analogWrite(A_2A, HIGH);
    analogWrite(A_1A, LOW);
    analogWrite(B_2A, HIGH);
    analogWrite(B_1A, LOW);
    delay(1500);
    analogWrite(A_2A, LOW);
    analogWrite(A_1A, LOW);
    analogWrite(B_2A, LOW);
    analogWrite(B_1A, LOW);
  }
}*/
