int a = 2;
int b = 3;
int c = 4;
int d = 5;
int e = 6;
int f = 7;
int g = 8;


void setup() {
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
}

void loop() {
  // Display 0
//  digitalWrite(a, HIGH);
//  digitalWrite(b, HIGH);
//  digitalWrite(c, HIGH);
//  digitalWrite(d, HIGH);
//  digitalWrite(e, HIGH);
//  digitalWrite(f, HIGH);
//  digitalWrite(g, LOW);
//  delay(1000);

  // Display 1
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  delay(1000);
}
