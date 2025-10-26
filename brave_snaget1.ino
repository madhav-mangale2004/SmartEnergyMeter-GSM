#include <LiquidCrystal.h>

// LCD pin connections: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // RS=12, E=11, DB4=5, DB5=4, DB6=3, DB7=2

float voltage, current, power, energy = 0.0;
float rate = 7.5; // Rs per kWh
unsigned long previousMillis = 0;
const long interval = 3000; // update every 3 seconds

void setup() {
  lcd.begin(16, 2);        // initialize 16x2 LCD
  Serial.begin(9600);      // for simulated GSM output

  // Welcome message
  lcd.print("Smart Energy");
  lcd.setCursor(0, 1);
  lcd.print("Meter System");
  delay(2000);
  lcd.clear();
}

void loop() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // --- Simulate energy metering IC readings ---
    voltage = random(210, 241); // 210V–240V
    current = random(1, 10);    // 1A–10A

    // --- DSP logic ---
    power = voltage * current;      // Instantaneous Power
    energy += power * (interval / 3600000.0); // Energy in kWh

    float bill = energy * rate;     // Billing calculation

    // --- Display all info on LCD ---
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("V:");
    lcd.print(voltage);
    lcd.print(" I:");
    lcd.print(current);

    lcd.setCursor(0, 1);
    lcd.print("P:");
    lcd.print(power, 0);
    lcd.print(" E:");
    lcd.print(energy, 2);

    delay(2000); // short pause

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Bill: Rs");
    lcd.print(bill, 2);

    lcd.setCursor(0, 1);
    lcd.print("V:");
    lcd.print(voltage);
    lcd.print(" I:");
    lcd.print(current);

    // --- Simulate GSM transmission ---
    Serial.print("Sending via GSM -> ");
    Serial.print("V=");
    Serial.print(voltage);
    Serial.print("V  I=");
    Serial.print(current);
    Serial.print("A  P=");
    Serial.print(power, 0);
    Serial.print("W  E=");
    Serial.print(energy, 2);
    Serial.print("kWh  Bill=");
    Serial.print(bill, 2);
    Serial.println(" Rs");
  }
}
