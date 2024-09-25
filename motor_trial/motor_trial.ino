const int ena = 8;
#define LM1 9
#define LM2 10

#define RM1 11
#define RM2 12
const int enb = 13;

void setup() {
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);

  analogWrite(ena, 125);
  analogWrite(enb, 110);  
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
}
