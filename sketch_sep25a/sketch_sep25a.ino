#define RS A2
#define MS A3
#define LS A4 // Pin where the IR sensor is connected

long dur;
int dis;

const int ena = 8;
#define LM1 9
#define LM2 10

#define RM1 11
#define RM2 12
const int enb = 13;

const int tp = 3; // Trigger Pin for Ultrasonic
const int ep = 4; // Echo Pin for Ultrasonic

void setup() {
  // Define pin modes
  pinMode(MS, INPUT);
  pinMode(LS, INPUT);
  pinMode(RS, INPUT);
  pinMode(tp, OUTPUT);
  pinMode(ep, INPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);

  analogWrite(ena, 125);
  analogWrite(enb, 110);

  Serial.begin(9600);
}

void loop() {
  Serial.print("MS : ");
  Serial.println(digitalRead(MS));
  Serial.print("RS : ");
  Serial.println(digitalRead(RS));
  Serial.print("LS : ");
  Serial.println(digitalRead(LS));
  if (digitalRead(MS)) {  // Middle Sensor On Line
    if (!digitalRead(LS) && !digitalRead(RS)) {  // LS and RS not on line
      Serial.println("move forward");
      forward();
    }
    else if (digitalRead(LS) && !digitalRead(RS)) {  // Sharp Left
      Serial.println("Sharp Left");
      sharpLeft();
    }
    else if (!digitalRead(LS) && digitalRead(RS)) {  // Sharp Right
      Serial.println("Sharp Right");
      sharpRight();
    }
    else if (digitalRead(LS) && digitalRead(RS)) {
      stop();
      Serial.println("Stop");
    }
  }
  else {
    if (digitalRead(LS) && !digitalRead(RS)) {  // Turn left
      left();
      Serial.println("Left");
    }
    else if (!digitalRead(LS) && digitalRead(RS)) {  // Turn right
      right();
      Serial.println("Right");
    }
    else if (!digitalRead(LS) && !digitalRead(RS)) {  // Stop
      stop();
    }
  }

  delay(50);  // Increase delay slightly for better sensor response
}

void forward() {
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
}

void sharpLeft() {
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
}

void sharpRight() {
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
}

void left() {
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
}

void right() {
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
}

void stop() {
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
}

long getDistance() {
  digitalWrite(tp, LOW);
  delayMicroseconds(2);
  digitalWrite(tp, HIGH);
  delayMicroseconds(10);
  digitalWrite(tp, LOW);

  dur = pulseIn(ep, HIGH);
  dis = dur * 0.034 / 2;  // Distance in cm
  return dis;
}
