#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte currentStep = 0;
byte score = 0;
byte health = 3;

void setup()
{
  screenSetup();
  setupStatusBar();
}

void screenSetup()
{
  lcd.begin(16, 2);

  lcd.print("Hi man!");
  lcd.setCursor(0, 1);
  lcd.print("I am a new game!");

  // TODO кнопка старт
  delay(1000);

  lcd.clear();
}

void setupStatusBar()
{
  // Вывод строки с набранными баллами.
  lcd.setCursor(0, 0);
  lcd.print("$");
  lcd.setCursor(1, 0);
  lcd.print(score);

  // Вывод строки с количеством здоровья.
  lcd.setCursor(0, 1);
  lcd.print("H");
  lcd.setCursor(1, 1);
  lcd.print(health);
}

void loop()
{
  clearCharacter();
  drawCharacter("-");

  nextStep();
}

void clearCharacter()
{
  lcd.setCursor(18 - currentStep, 1);
  lcd.print(" ");
}

void drawCharacter(String ch)
{
  lcd.setCursor(17 - currentStep, 1);
  lcd.print(ch);
}

void nextStep()
{
  delay(200);
  // Слева экрана будет свободно 3 ячейки.
  currentStep = (currentStep + 1) % 15;
}
