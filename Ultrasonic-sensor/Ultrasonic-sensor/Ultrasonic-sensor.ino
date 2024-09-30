#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int powerRelease = 12;
int trigger = A0;
int echo = A1;
double duration;
double distance;

void setup() {
  lcd.begin();
//  lcd.init();
  lcd.clear();
  lcd.backlight();
  pinMode(powerRelease, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  lcd.setCursor(0,0);
  lcd.print("Lavel");
  lcd.setCursor(10,0);
  lcd.print("Status");
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
//  distance = ((0.000332 * duration) / 2) * 39.37; // Divided by 2 for get outgoing time.
                                                 // Multimply by 100 for convert m to cm.
  distance = (0.000166 * duration) * 39.37;

  lcd.setCursor(0,1);
  lcd.print(distance);

  lcd.setCursor(6,1);
  lcd.print("in");
    
  if (distance > 10) {
    digitalWrite(powerRelease, HIGH);    
    lcd.setCursor(13,1);
    lcd.print(" ");
    lcd.setCursor(14,1);
    lcd.print("On");
  } else if (distance < 5) {
    digitalWrite(powerRelease, LOW);
    lcd.setCursor(13,1);
    lcd.print("Off");
  }
  delay(1000);
}
