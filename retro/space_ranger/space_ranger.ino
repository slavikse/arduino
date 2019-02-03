#include <LiquidCrystal.h>

// TODO WIP

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

int step = 0;

void setup()
{
  lcd.begin(16, 2);
  lcd.print("Hello!");
}

void loop()
{
  lcd.setCursor(step, 1);
  lcd.print("-");

  delay(200);

  lcd.clear();
  step = (step + 2) % 16;
}
