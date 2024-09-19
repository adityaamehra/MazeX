long d;
int dis;

const int tp=10;
const int ep=11;

void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  pinMode(tp,OUTPUT);
  pinMode(ep,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(tp,LOW);
  delayMicroseconds(2);
  digitalWrite(tp,HIGH);
  delayMicroseconds(10);
  
  digitalWrite(tp,LOW);

  d = pulseIn(ep,HIGH);

  dis=d*0.034/2;

  if(dis !=0)
  {
    if(dis>=10)
    digitalWrite(13,LOW);
    else
    digitalWrite(13,HIGH);
    Serial.print("Distance : ");
    Serial.println(dis);
  }
}
