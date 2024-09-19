int irSensorPin = 2; // Pin where the IR sensor is connected
int irValue = 0;   // Variable to store the value from the sensor

long d;
int dis;

const int tp=10;
const int ep=11;
void setup() {
  pinMode(irSensorPin, INPUT); // Set the IR sensor pin as input
  pinMode(13,OUTPUT);
  pinMode(tp,OUTPUT);
  pinMode(ep,INPUT);
  Serial.begin(9600);     // Initialize serial communication at 9600 baud rate
}

void loop() {
  irValue = digitalRead(irSensorPin); // Read the value from the sensor

  if (irValue == HIGH) {
    Serial.println("Object detected"); // Print message if an object is detected

    digitalWrite(tp,LOW);
    delayMicroseconds(2);
    digitalWrite(tp,HIGH);
    delayMicroseconds(10);
    digitalWrite(tp,LOW);
    digitalWrite(13,LOW);
    d=pulseIn(ep,HIGH);

    dis=d*0.034/2;
    Serial.print("Distace :");
    Serial.println(dis);
  } else {
    Serial.println("No object detected"); // Print message if no object is detected
    digitalWrite(13,HIGH);
  }

  delay(500); // Wait for half a second before checking again
}