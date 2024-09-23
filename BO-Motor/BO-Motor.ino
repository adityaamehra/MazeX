//MOTOR1 PINS
const int ena = 5;
const int in1 = 6;
const int in2 = 7;

const int in3 = 8;
const int in4 = 9;
const int enb = 10;

void setup() {
  // Define pin modes
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  //MOTOR_A CLOCKWISE MAX SPEED
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(ena, 255);

  //MOTOR_B CLOCKWISE MAX SPEED
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(enb, 255);
  delay(1000);

  //STOP
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  delay(500);

  //MOTOR_A COUNTERCLOCKWISE MAX SPEED
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  analogWrite(ena, 255);

  //MOTOR_B COUNTERCLOCKWISE MAX SPEED
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  analogWrite(enb, 255);

  delay(1000);

  //STOP
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  delay(500);


  //MOTOR_A TURNS RIGHT MAX SPEED
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(ena, 255);

  //MOTOR_B CLOCKWISE HALF SPEED
  // digitalWrite(in3,HIGH);
  // digitalWrite(in4,LOW);
  // analogWrite(enb, 127);
  delay(1000);

  //STOP
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  delay(500);

  //MOTOR_A COUNTERCLOCKWISE MAX SPEED
  // digitalWrite(in1,LOW);
  // digitalWrite(in2,HIGH);
  // analogWrite(ena, 127);

  //MOTOR_B COUNTERCLOCKWISE MAX SPEED
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(enb, 255);
  delay(1000);

  //STOP
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  delay(8000); 
}