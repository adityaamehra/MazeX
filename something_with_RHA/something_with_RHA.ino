#define FRS A1
#define FLS A5
#define RS A2
#define MS A3
#define LS A4 // Pin where the IR sensor is connected

const int ena = 5;
#define LM1 10
#define LM2 9
#define RM1 12
#define RM2 11
const int enb = 6;

const int tp = 3;
const int ep = 4;

int ivm = 0, ivl = 0, ivr = 0; // Sensor values
int ifrs = 0, ifls = 0; // Far sensor values

#define MAX_PATH_LENGTH 100
char path[MAX_PATH_LENGTH];
int pathIndex = 0;

void setup() {
  // Define pin modes
  pinMode(MS, INPUT);
  pinMode(LS, INPUT);
  pinMode(RS, INPUT);
  pinMode(FRS, INPUT);
  pinMode(FLS, INPUT);
  pinMode(tp, OUTPUT);
  pinMode(ep, INPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);

  analogWrite(ena, 100);
  analogWrite(enb, 120);

  Serial.begin(9600);
}

void loop() {
  ivr = digitalRead(RS);
  ivm = digitalRead(MS);
  ivl = digitalRead(LS);
  ifrs = digitalRead(FRS);
  ifls = digitalRead(FLS);

  Serial.print("Right Sensor: ");
  Serial.print(ivr);
  Serial.print(" Middle Sensor: ");
  Serial.print(ivm);
  Serial.print(" Left Sensor: ");
  Serial.print(ivl);
  Serial.print(" Far Right Sensor: ");
  Serial.print(ifrs);
  Serial.print(" Far Left Sensor: ");
  Serial.println(ifls);

  if (ivm && ivl  && ivr && ifrs  && ifls ) { // All sensors not on the line
    makeUTurn();
  } else if (ifrs) { // No wall on the far right
    move('R');
  } else if (ivm) { // Wall in front
    move('L');
  } else { // Wall on the right, no wall in front
    move('F');
  }

  delay(100); // Small delay to stabilize the readings
}

void move(char direction) {
  switch (direction) {
    case 'R': // Turn right
      digitalWrite(LM1, LOW);
      digitalWrite(LM2, HIGH);
      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, LOW);
      break;
    case 'L': // Turn left
      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      digitalWrite(RM1, LOW);
      digitalWrite(RM2, HIGH);
      break;
    case 'F': // Move forward
      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, LOW);
      break;
  }
  trackPath(direction);
}

void makeUTurn() {
  // U-turn logic
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
  delay(1000); // Adjust delay as needed for making a U-turn
  trackPath('U');
}

void trackPath(char direction) {
  if (pathIndex < MAX_PATH_LENGTH) {
    path[pathIndex++] = direction;
  }
}

void reversePath() {
  for (int i = pathIndex - 1; i >= 0; i--) {
    char direction = path[i];
    switch (direction) {
      case 'R': // Reverse right turn
        move('L');
        break;
      case 'L': // Reverse left turn
        move('R');
        break;
      case 'F': // Reverse forward move
        moveBackward();
        break;
      case 'U': // Reverse U-turn
        makeUTurn();
        break;
    }
    delay(500); // Adjust delay as needed for turning/moving
  }
}

void moveBackward() {
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
}