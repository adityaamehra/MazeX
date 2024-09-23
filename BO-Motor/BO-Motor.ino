/*
* in3 (HIGH) := Is going backwards of right when looking from the perspective of ultrasonic
* in1 (HIGH) := Is going backwards of left when looking from the perspective of ultrasonic
*/

const int ispr = 11;
const int ispm = 12;
const int ispl = 13; // Pin where the IR sensor is connected
int ivm = 0;
int ivl = 0;
int ivr = 0;   // Variable to store the value from the sensor

long dur;
int dis;

const int ena = 5;
const int in1 = 6;
const int in2 = 7;

const int in3 = 8;
const int in4 = 9;
const int enb = 10;

const int tp = 3;
const int ep = 4;

void left()
{
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    analogWrite(enb,150);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
}

void right()
{
    analogWrite(ena,150);
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);
}

void stop()
{
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);
}

void backward()
{
    analogWrite(ena,150);
    analogWrite(enb,150);
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
}

void forward()
{
    analogWrite(ena,150);
    analogWrite(enb,150);
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
}

void setup() {
  // Define pin modes
  pinMode(ispm, INPUT);
  pinMode(ispl, INPUT);
  pinMode(ispr, INPUT);
  pinMode(tp,OUTPUT);
  pinMode(ep,INPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  ivm = digitalRead(ispm); // Read the value from the sensor
  ivl = digitalRead(ispl);
  ivr = digitalRead(ispr);

  digitalWrite(tp,LOW);
  digitalWrite(tp,HIGH);
  delayMicroseconds(10);
  digitalWrite(tp,LOW);
  delayMicroseconds(2);
  
  dur = pulseIn(ep,HIGH);

  if(dur !=0)
  {
    dis=dur*0.034/2;
    if(dis < 10)
    {
      stop();
    }
    else
    {
      if(ivm == LOW && ivr == HIGH && ivl == HIGH)
      {
        forward();
      }
      else if (ivm == LOW && ivr == HIGH && ivl == LOW)
      {
        left();
      }
      else if (ivm == LOW && ivr == LOW && ivl == HIGH)
      {
        right();
      }
      else
      {
        stop();
      }
    }
  }
}