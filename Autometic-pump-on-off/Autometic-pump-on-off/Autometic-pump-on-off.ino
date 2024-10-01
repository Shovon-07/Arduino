#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int powerRelease = 12;
int trigger = A0;
int echo = A1;
double timeInMicro;
double distance;

void setup() {
  lcd.begin();
//  lcd.init();
  lcd.clear();
  lcd.backlight();
  pinMode(powerRelease, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  lcd.setCursor(2,0);
  lcd.print("Level");
  lcd.setCursor(10,0);
  lcd.print("Status");
}

void loop() {
  // For clear previous pulse
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);

  // Release sound for 10 micro second
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  // Calculation
  timeInMicro = pulseIn(echo, HIGH);
  distance = timeInMicro * 0.034 / 2;    // Its return distance in 'cm'.
  distance = (distance / 152.4) * 100;  // Convert 'cm' to % .
  lcd.setCursor(0,1);
  lcd.print(distance);

  lcd.setCursor(7,1);
  lcd.print("%");
    
  if (distance > 10) {
    digitalWrite(powerRelease, HIGH);    
    lcd.setCursor(12,1);
    lcd.print("On");
    lcd.setCursor(14,1);
    lcd.print(" ");
  } else if (distance < 5) {
    digitalWrite(powerRelease, LOW);
    lcd.setCursor(12,1);
    lcd.print("Off");
  }
  delay(1000);
}

/***
 *   
 * cm to % = (cm / total length : 152.4 cm) * 100
 * 
 * 
***/
