/*
* in3 (HIGH) := Is going backwards of right when looking from the perspective of ultrasonic
* in1 (HIGH) := Is going backwards of left when looking from the perspective of ultrasonic
*/

#define RS 11
#define MS 12
#define LS 13 // Pin where the IR sensor is connected
int ivm = 0;
int ivl = 0;
int ivr = 0;   // Variable to store the value from the sensor

long dur;
int dis;

const int ena = 5;
#define LM1 7
#define LM2 6

#define RM1 9
#define RM2 8
const int enb = 10;

const int tp = 3;
const int ep = 4;

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
  pinMode(tp,OUTPUT);
  pinMode(ep,INPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);

  analogWrite(ena,125);
  analogWrite(enb,110);

  Serial.begin(9600);
}

void loop() {
  

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
    else if(digitalRead(LS) && !digitalRead(RS)) //Sharp Left
    {
    Serial.println("Sharp Left");
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH); 
    digitalWrite(RM2, LOW);
    }
    else if(!digitalRead(LS) && digitalRead(RS)) //Sharp Right
    {
    Serial.println("Sharp Right");
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    }
    else if(digitalRead(LS) && digitalRead(RS)) 
    {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
    Serial.println("Stop");
    }
  }
  else
  {
  if(digitalRead(LS) && !digitalRead(RS))     // Turn left
  {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, LOW); 
    digitalWrite(RM2, LOW);
    Serial.println("Left");
  }
  else if(!digitalRead(LS) && digitalRead(RS))     // turn right
  {
    digitalWrite(LM1, LOW); 
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    Serial.println("Right");
  } 
    else if(!digitalRead(LS) && !digitalRead(RS))     // turn right
  {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
  }
  }
  delay(5);
}