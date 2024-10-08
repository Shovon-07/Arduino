#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16x2 display

// Define pin numbers
const int pin6 = 6; // Low water
const int pin7 = 7; // Medium water
const int pin8 = 8; // Full water
const int pin9 = 9; // Overflow
const int pin5 = 5; // Output as load
const int pin4 = 4; // Buzzer
const int pin3 = 3; // Mode switch

unsigned long startTime = 0;
bool loadOn = false;
bool autoMode = true; // Start in auto mode by default

void setup() {
  // Initialize I2C LCD
  lcd.begin();
  lcd.backlight();

  // Set pins 6-9 as input with pull-up resistors
  pinMode(pin6, INPUT_PULLUP);
  pinMode(pin7, INPUT_PULLUP);
  pinMode(pin8, INPUT_PULLUP);
  pinMode(pin9, INPUT_PULLUP);
  
  // Set pin 5 as output (load) and pin 4 as output (buzzer)
  pinMode(pin5, OUTPUT);
  pinMode(pin4, OUTPUT);

  // Mode switch as input
  pinMode(pin3, INPUT);

  // Initial state of outputs
  digitalWrite(pin5, LOW);
  digitalWrite(pin4, LOW);

  // Display initial messages
  lcd.setCursor(1, 0);
  lcd.print("System Started");
  delay(1000);  // Initial message delay for better readability
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Automatic Pump");
  lcd.setCursor(3, 1);
  lcd.print("Controller");
  delay(1000);  // Initial message delay for better readability
  lcd.clear();
}

void loop() {
  // Check the mode (Auto or Manual)
  autoMode = digitalRead(pin3); // If pin3 is HIGH, autoMode is true; else manual mode

  // Display mode and pump status on the first row in short form
  lcd.setCursor(0, 0);
  if (autoMode) {
    lcd.clear();
    lcd.print("Auto"); // Display Auto mode in short form
  } else {
    lcd.print("Manual"); // Display Manual mode in short form
  }

  lcd.setCursor(8, 0);
  if (loadOn) {
    lcd.print("Pump ON "); // Display Pump ON status
  } else {
    lcd.print("Pump OFF"); // Display Pump OFF status
  }

  // Manual mode functionality
  if (!autoMode) {
    checkWaterLevelsManual(); // Call the manual mode function
  }

  // Auto mode functionality
  if (autoMode) {
    checkWaterLevelsAuto(); // Call the auto mode function
  }

  delay(500); // Slight delay for stability
}

// Function to check water levels in Auto Mode
// Function to check water levels in Auto Mode
void checkWaterLevelsAuto() {
  // Read the status of pins 6-9
  bool waterLow = digitalRead(pin6);      // HIGH means low water
  bool waterMid = digitalRead(pin7);      // HIGH means below medium water, LOW means medium water
  bool waterFull = digitalRead(pin8);     // LOW means full water
  bool waterOverflow = digitalRead(pin9); // LOW means overflow

  // Auto mode: check the status of pin 6 (low water) for 5 seconds
  if (waterLow == HIGH) {
    if (millis() - startTime >= 5000) {
      digitalWrite(pin5, HIGH); // Turn on load (pump)
      lcd.setCursor(0, 1);
    lcd.print("Low Water     ");
      loadOn = true;
    }
  } else {
    startTime = millis();
  }

  // If all pull-up resistors are low, turn off the load
  if (waterLow == LOW && waterMid == LOW && waterFull == LOW && waterOverflow == LOW) {
    digitalWrite(pin5, LOW); // Turn off load (pump)
    loadOn = false;
  }

  // Independent checks for each water level
  if (waterOverflow == LOW) {
    lcd.setCursor(0, 1);
    lcd.print("Overflow      ");
    digitalWrite(pin5, LOW);  // Turn off load on overflow
    digitalWrite(pin4, HIGH); // Activate buzzer
    delay(1000);              // Buzzer for 1 second
    digitalWrite(pin4, LOW);  // Turn off buzzer
  } else if (waterFull == LOW) {
    lcd.setCursor(0, 1);
    lcd.print("Full Water    ");
  } else if (waterMid == LOW) {
    lcd.setCursor(0, 1);
    lcd.print("Medium Water  ");
  } else if (waterMid == HIGH) {  // Check if pin7 is HIGH for "Below Medium"
    lcd.setCursor(0, 1);
    lcd.print("Below Medium  ");  // Display "Below Medium" when pin7 is HIGH
  } else if (waterLow == HIGH) {
    lcd.setCursor(0, 1);
    lcd.print("Low Water     ");
  }
}

// Function to check water levels in Manual Mode
void checkWaterLevelsManual() {
  // Read the status of pins 6-9
  bool waterLow = digitalRead(pin6);      // HIGH means low water
  bool waterMid = digitalRead(pin7);      // LOW means medium water
  bool waterFull = digitalRead(pin8);     // LOW means full water
  bool waterOverflow = digitalRead(pin9); // LOW means overflow

  // In manual mode, just display the water levels without controlling the pump
  if (waterOverflow == LOW) {
    lcd.setCursor(0, 1);
    lcd.print("Overflow      ");
    digitalWrite(pin4, HIGH); // Activate buzzer
    delay(1000);              // Buzzer for 1 second
    digitalWrite(pin4, LOW);  // Turn off buzzer
  } 
  else if (waterFull == LOW) {
    lcd.setCursor(0, 1);
    lcd.print("Full Water    ");
  } 
  else if (waterMid == LOW) {
    lcd.setCursor(0, 1);
    lcd.print("Medium Water  ");

     } 
     else if (waterMid == HIGH) {  // Check if pin7 is HIGH for "Below Medium"
    lcd.setCursor(0, 1);
    lcd.print("Below Medium  "); 

     }
  else if (waterLow == HIGH) {
    lcd.setCursor(10, 1);
    lcd.print("Low Water     ");
    delay(1000);
    digitalWrite(pin4, HIGH); // Activate buzzer
  }
}
