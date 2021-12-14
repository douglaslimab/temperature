#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int x;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1);
  
  lcd.clear();
  lcd.begin(16, 2);
  lcd.setCursor(1, 0);
  lcd.print("Done!!");
  delay(100);
}

void loop() {
  while (!Serial.available());
  x = Serial.readString().toInt();
  Serial.print(x + 1);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(x);
}
