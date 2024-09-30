int led = 13;
int pirInput = 12;
int state;


void setup() {
  pinMode(led,OUTPUT);
  pinMode(pirInput,INPUT);
}

void loop() {
  state = digitalRead(pirInput);
  digitalWrite(led,state);
  delay(100);
  digitalWrite(led,state);
  delay(100);
}
