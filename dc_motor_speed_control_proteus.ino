int m1=13, m2=12, en=9;
int pot=A0, st=0;

void setup() {
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(en, OUTPUT);
}

void loop() {
  st=analogRead(pot)/4;
  analogWrite(en, st);
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);

}

// https://www.tinkercad.com/things/3VyjpR9BAji-pir-motion-sensor

// https://www.tinkercad.com/things/81TyBw5wEOz-sun-traking-solar-system
