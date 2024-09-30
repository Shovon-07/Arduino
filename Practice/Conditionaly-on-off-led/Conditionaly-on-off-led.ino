int led = 12;
int regulator = A0;
int val;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(regulator, INPUT);
}

void loop() {
  val = analogRead(regulator);
  if (val < 4) {
    digitalWrite(led, LOW);
  } else {
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);
  }
}
