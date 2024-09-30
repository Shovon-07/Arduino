#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Connect sda in A3 pin and scl in A5 pin
LiquidCrystal_I2C lcd(0x27, 16,2);

void setup() {
//  lcd.begin();
  lcd.init();
  lcd.clear();
  lcd.backlight();
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Al Jubair Shovon");

  lcd.setCursor(0,1);
  lcd.print("Study in CSE");

  delay(500);
  lcd.noDisplay();
  delay(500);
  lcd.display();
}
