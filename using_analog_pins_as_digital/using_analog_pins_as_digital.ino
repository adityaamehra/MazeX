#define FRS A0
#define FLS A1

int reading;

void setup() {
  // put your setup code here, to run once:
  pinMode(FRS, INPUT);
  pinMode(FLS, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  reading = digitalRead(FRS);
  Serial.print("Read 1 : ");
  Serial.println(reading);

  Serial.print("Read 2 : ");
  reading = digitalRead(FLS);
  Serial.println(reading);
  delay(500);
}