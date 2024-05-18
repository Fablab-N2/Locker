#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <AccelStepper.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27,16,2);

// Defines the number of steps per rotation
AccelStepper stepper;

// password per lock
String lock_1_pass = "1A56B"; // Hash of "1A56B"
String lock_2_pass = "584CA"; // Hash of "584CA"

// lock engaged (flase = open / true = closed)
bool lock_1 = true;
bool lock_2 = true;

String input = "";

// Configuration du clavier numérique dans une matrice
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {22, 21, 16, 7};
byte colPins[COLS] = {6, 5, 12, 14};
Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


void setup() {
  Serial.begin(115200);

  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);

  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();

  stepper.setMaxSpeed(100);
}


void loop() {
  lcd.setCursor(0,0);
  lcd.print("Enter your code:");
  char customKey = customKeypad.getKey();
  if (customKey){
    // Add the key to the input string
    input += customKey;
    Serial.print(customKey);
    // Check if the input length is 5
    if (input.length() == 5){
      Serial.print(" -> Full input: ");
      Serial.println(input);
      if (lock_1 == true && lock_1_pass == input) {
        digitalWrite(0, HIGH);
        Serial.println("Lock 1 has been opened");

        stepper.setAcceleration(20);
        stepper.moveTo(500);
        delay(60000);
        input = "";
      }
      else if (lock_2 == true && lock_2_pass == input) {
        digitalWrite(1, HIGH);
        Serial.println("Lock 2 has been opened");

        stepper.setAcceleration(20);
        stepper.moveTo(500);
        delay(60000);
        input = "";
      }
      else {
        digitalWrite(0, LOW);
        digitalWrite(1, LOW);
        Serial.println("A wrong attempts has occurred");
        input = "";
      }
    }
  }
  delay(200);
}