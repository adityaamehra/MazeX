/*
* in3 (HIGH) := Is going backwards of right when looking from the perspective of ultrasonic
* in1 (HIGH) := Is going backwards of left when looking from the perspective of ultrasonic
*/

#define FRS A1
#define FLS A5
#define RS A2
#define MS A3
#define LS A4 // Pin where the IR sensor is connected
int ivm = 0;
int ivl = 0;
int ivr = 0;   // Variable to store the value from the sensor

int turn=0;

long dur;
int dis;

const int ena = 5;
#define LM1 10
#define LM2 9

#define RM1 12
#define RM2 11
const int enb = 6;

const int tp = 3;
const int ep = 4;
void reset(void)
{
  analogWrite(ena,140);
  analogWrite(enb,125);
}
// void uturn()
// {
//     analogWrite(ena,105);
//     digitalWrite(in1,HIGH);
//     digitalWrite(in2,LOW);
//     analogWrite(enb,90);
//     digitalWrite(in3,LOW);
//     digitalWrite(in4,HIGH);
//     delay(390);
//     stop();
// }

// void left()
// {
//     stop();
//     delay(100);
//     forward();
//     delay(100);
//     analogWrite(ena,105);
//     digitalWrite(in1,HIGH);
//     digitalWrite(in2,LOW);
//     analogWrite(enb,90);
//     digitalWrite(in3,LOW);
//     digitalWrite(in4,HIGH);
//     delay(500);
//     stop();
// }

// void right()
// {
//     stop();
//     delay(100);
//     forward();
//     delay(100);
//     analogWrite(ena,105);
//     digitalWrite(in1,LOW);
//     digitalWrite(in2,HIGH);
//     analogWrite(enb,90);
//     digitalWrite(in3,HIGH);
//     digitalWrite(in4,LOW);
//     delay(500);
//     stop();
// }

// void stop()
// {
//     digitalWrite(in1,LOW);
//     digitalWrite(in2,LOW);
//     digitalWrite(in3,LOW);
//     digitalWrite(in4,LOW);
// }

// void backward()
// {
//     analogWrite(ena,105);
//     analogWrite(enb,90);
//     digitalWrite(in1,HIGH);
//     digitalWrite(in2,LOW);
//     digitalWrite(in3,HIGH);
//     digitalWrite(in4,LOW);
// }

// void forward()
// {
//     analogWrite(ena,105);
//     analogWrite(enb,90);
//     digitalWrite(in1,LOW);
//     digitalWrite(in2,HIGH);
//     digitalWrite(in3,LOW);
//     digitalWrite(in4,HIGH);
// }

void setup() {
  // Define pin modes
  pinMode(MS, INPUT);
  pinMode(LS, INPUT);
  pinMode(RS, INPUT);
  pinMode(FRS, INPUT);
  pinMode(FLS, INPUT);
  pinMode(tp,OUTPUT);
  pinMode(ep,INPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);

  analogWrite(ena,140);
  analogWrite(enb,125);

  Serial.begin(9600);
}

void loop() {
  

  // if(digitalRead(MS))     // Middle Sensor On Line
  // {
  //   if((!digitalRead(LS) || !digitalRead(FLS)) && (!digitalRead(RS) || !digitalRead(FRS))) //LS and RS not on line
  //   {
  //   Serial.println("move forward");
  //   digitalWrite(LM1, LOW);
  //   digitalWrite(LM2, HIGH);
  //   digitalWrite(RM1, LOW);
  //   digitalWrite(RM2, HIGH);
  //   }
  //   else if((digitalRead(LS) || digitalRead(FLS))&& (!digitalRead(RS) || !digitalRead(FRS))) //Sharp Left
  //   {
  //   Serial.println("Sharp Left");
  //   digitalWrite(LM1, LOW);
  //   digitalWrite(LM2, HIGH);
  //   digitalWrite(RM1, HIGH); 
  //   digitalWrite(RM2, LOW);
  //   }
  //   else if((!digitalRead(FLS) || !digitalRead(LS)) && (digitalRead(RS) || digitalRead(FRS))) //Sharp Right
  //   {
  //   Serial.println("Sharp Right");
  //   digitalWrite(LM1, HIGH);
  //   digitalWrite(LM2, LOW);
  //   digitalWrite(RM1, LOW);
  //   digitalWrite(RM2, HIGH);
  //   }
  //   else if((digitalRead(LS) || digitalRead(FLS))&& (digitalRead(RS) || digitalRead(FRS)))
  //   {
  //   digitalWrite(LM1, LOW);
  //   digitalWrite(LM2, LOW);
  //   digitalWrite(RM1, LOW);
  //   digitalWrite(RM2, LOW);
  //   Serial.println("Stop");
  //   }
  // }
  turn=digitalRead(FLS)+digitalRead(LS)-digitalRead(RS)-digitalRead(FRS);
  if(digitalRead(MS))     // Middle Sensor On Line
  {
    if(!digitalRead(LS) && !digitalRead(RS)) //LS and RS not on line
    {
    Serial.println("move forward");
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    }
    else if(digitalRead(LS) && !digitalRead(RS) || turn >0 ) //Sharp Left
    {
          analogWrite(ena,70);
    analogWrite(enb,90);
    Serial.println("Sharp Left");
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH); 
    digitalWrite(RM2, LOW);
    reset();
    }
    else if(!digitalRead(LS) && digitalRead(RS) || turn < 0) //Sharp Right
    {
          analogWrite(ena,70);
    analogWrite(enb,90);
    Serial.println("Sharp Right");
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
        reset();
    }
    else if(digitalRead(LS) && digitalRead(RS))
    {
      Serial.println("move forward");
      digitalWrite(LM1, LOW);
      digitalWrite(LM2, HIGH);
      digitalWrite(RM1, LOW);
      digitalWrite(RM2, HIGH);
    }
  }
  else
  {
  if((!digitalRead(LS) && !digitalRead(FLS)) && (!digitalRead(RS) && !digitalRead(FRS))) // U-Turn
  {
    analogWrite(ena,100);
    analogWrite(enb,120);
    Serial.println("U-TURN");
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH); 
    digitalWrite(RM2, LOW);
        reset();
  }
  else if(turn > 0)   // Turn left
  {
    if(digitalRead(FLS))
    {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, LOW); 
    digitalWrite(RM2, LOW);
    }
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, LOW); 
    digitalWrite(RM2, LOW);
    Serial.println("Left");
  }
  else if(turn < 0)     // turn right
  {
    if(digitalRead(FRS))
    {
    digitalWrite(LM1, LOW); 
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    }
    digitalWrite(LM1, LOW); 
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    Serial.println("Right");
  } 
    else if((digitalRead(LS) && digitalRead(FLS)) && (digitalRead(RS) && digitalRead(FRS)))     // STOP
  {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
  }
  }
  delay(5);
}