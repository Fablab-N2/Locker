#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Stepper.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27,16,2);

// Defines the number of steps per rotation
Stepper myStepper = Stepper(1000, 13,12,11,10);

// password per lock
const char lock_1_pass = "d5ef4ecfee2a85a668be66ca615d2b2d"; // Hash of "1A56B"
const char lock_2_pass = "b51fc8660eba0dd914d96510642fad92"; // Hash of "584CA"

const char plainText = "d5ef4ecfee2a85a668be66ca615d2b2d";

// lock engaged (flase = open / true = closed)
bool lock_1 = true;
bool lock_2 = true;

// Configuration du clavier numérique dans une matrice
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {13, 12, 27, 33}; // Connecter les lignes du clavier numérique aux broches de la carte wifi
byte colPins[COLS] = {4, 5, 18, 19 }; // Connecter les colonnes du clavier numérique aux broches de la carte wifi

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


void setup() {
  Serial.begin(115200);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
}


void loop() {
  
  lcd.setCursor(0,0);
  lcd.print("Enter your code:");

  if (lock_1 == true && lock_1_pass == plainText) {
    // turn on the light
    digitalWrite(2, HIGH);

    // use the motor to open the lock
    myStepper.setSpeed(10);
    myStepper.step(100);
    delay(2000);
  }
  else {
    digitalWrite(2, LOW);
  }
  

  if (lock_2 == true && lock_2_pass == plainText) {
    // turn on the light
    digitalWrite(3, HIGH);

    // use the motor to open the lock
    myStepper.setSpeed(10);
    myStepper.step(2038);
    delay(200);
  }
  else {
    digitalWrite(3, LOW);
  }
}