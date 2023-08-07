#include <Servo.h>
Servo myservo;
int ledState = LOW;
#define ledPin D9
unsigned long previousMillis = 0;
const long interval = 500;
unsigned long currentMillis;

uint8_t MOTOR1_1 = D7;
uint8_t MOTOR1_2 = D6;
uint8_t MOTOR2_1 = D5;
uint8_t MOTOR2_2 = D4;

int cm,duration;
int Degree=100;
int i=0;
enum State {reset,turn_move,right_check,turn_rigth,left_check,turn_left,terminate,move_check};
State state=reset;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  myservo.attach(D8);
  
  pinMode(D11, OUTPUT);
  pinMode(D10, INPUT);
   myservo.write(Degree);
    pinMode(MOTOR1_1, OUTPUT);
    pinMode(MOTOR1_2, OUTPUT);
    pinMode(MOTOR2_1, OUTPUT);
    pinMode(MOTOR2_2, OUTPUT);
}

void loop() {
  currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (ledState == LOW) { ledState = HIGH;} 
    else {ledState = LOW;}
    digitalWrite(ledPin, ledState); }
  ///////////////////////////////////////////
  
  Serial.print(cm);
  Serial.println('\n');
//////////////////////////  Switch and Case    //////////////
  // main state machine
  switch(state){
    case reset:
      // setup defalut statew
      state = move_check;
      break;
    case move_check:
      Degree=100;
      myservo.write(Degree);     
      delay(200);
      Distance();
      if(cm >= 20)
      {
        state=turn_move;  
      }
      else
      {
        state=right_check;
      }
      break;
    case right_check: 
      stop();      
      Degree=0;
      myservo.write(Degree);
      delay(200);
      Distance();  
      
      if(cm >= 18)
      {
        state=turn_rigth;  
      }
      else
      {
        state=left_check;
      }
      break;
  /////////////////////////


    case left_check:
      Distance();
      stop();
      Degree=190;
      myservo.write(Degree);    
       if(cm >= 18)
       {
         state=turn_left;
       }
       else
       {
         stop();
       }
       break;
    
    
   case turn_rigth:
     LEFT(); 
     delay(450);
     stop();    
     state=reset;
     break;

   case  turn_left:
     right();
     delay(450);
     stop();
     state=reset;
     break;

   case turn_move:
     back();
     state=reset;
     break;  

       default:
       state = reset;
     break;
  }
  // main state machine
  //  Degree = 100;
  //  myservo.write(Degree);
  //  Distance();
  //  if (cm >= 20)
  //   {
  //     back();
  //   } 
  //   else 
  //   {
  //     stop();
  //    Degree=60;
  //    myservo.write(Degree);
  //    Distance();
  //    if (cm >= 20)
  //    {
  //      LEFT();
  //    }
  //        else 
  //   {
  //     stop();
  //    Degree=0;
  //    myservo.write(Degree);
  //    Distance();
  //    if (cm >= 20)
  //    {
  //      right();
  //    }
  //    else 
  //   {
  //     stop();
  //   }

  //   }
  //   } 


  }
void fyont(void) {
  digitalWrite(MOTOR1_1, 1);
  digitalWrite(MOTOR1_2, 0);
  digitalWrite(MOTOR2_1, 1);
  digitalWrite(MOTOR2_2, 0);
}
void stop(void) {
  digitalWrite(MOTOR1_1, 0);
  digitalWrite(MOTOR1_2, 0);
  digitalWrite(MOTOR2_1, 0);
  digitalWrite(MOTOR2_2, 0);
}
void back(void) {
  digitalWrite(MOTOR1_1, 0);
  digitalWrite(MOTOR1_2, 1);
  digitalWrite(MOTOR2_1, 0);
  digitalWrite(MOTOR2_2, 1);
}

void right(void) {
  digitalWrite(MOTOR1_1, 1);
  digitalWrite(MOTOR1_2, 0);
  digitalWrite(MOTOR2_1, 0);
  digitalWrite(MOTOR2_2, 1);
}
void LEFT(void) {
  digitalWrite(MOTOR1_1, 0);
  digitalWrite(MOTOR1_2, 1);
  digitalWrite(MOTOR2_1, 1);
  digitalWrite(MOTOR2_2, 0);
}
void Distance(void) {
  digitalWrite(D11, 1);
  delayMicroseconds(20);
  digitalWrite(D11, LOW);
  duration = pulseIn(D10, 1);
  cm = duration / 29 / 2;
}
