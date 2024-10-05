int digit[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

int arduinoPins[] = {0, 1, 2, 3, 4, 5, 6};

void setup() {
  for (int x = 0; x <= 6; x++) {
    pinMode(arduinoPins[x], OUTPUT);
  }
}

void loop() {
  for (int y = 0; y <= 9; y++) {
    for (int i = 0; i <= 6; i++) {
      digitalWrite(arduinoPins[i], digit[y][i]);
    }
    delay(1000);
  }
}
