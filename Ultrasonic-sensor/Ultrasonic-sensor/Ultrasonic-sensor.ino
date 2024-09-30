int powerRelease = 12;
int trigger = A0;
int echo = A1;
long duration;
long distance;

void setup() {
  pinMode(powerRelease, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  // For clear previous pulse
  digitalWrite(trigger, LOW);
  delay(1);

  // Release sound for 10 micro second
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  // Calculation
  duration = pulseIn(echo, HIGH);
  distance = ((0.00034 * duration) / 2) * 39.37; // Divided by 2 for get outgoing time.
                                                 // Multimply by 100 for convert m to cm.
  if (distance > 5) {
    digitalWrite(powerRelease, HIGH);
  } else if (distance < 2) {
    digitalWrite(powerRelease, LOW);
  }
  delay(1000);
}
