#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const byte SHOT_BUTTON_PIN = 10;
const byte BUZZER_PIN = 6;

const byte PLAYER_TOP_PIN = 9;
const byte PLAYER_BOTTOM_PIN = 8;

// Размеры экрана.
const byte horizontal = 16;
const byte vertical = 2;

// 0 - Внизу, 1 - Вверху.
byte playerVertical = 0;
byte score = 0;
byte health = 3;

// 0 - значение инвертируется на выводе.
byte enemyPosition1 = 0;
byte enemyShotPosition1 = 0;

void setup()
{
  // Serial.begin(9600);

  screenSetup();
  setupStatusBar();
}

void screenSetup()
{
  lcd.begin(horizontal, vertical);

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
  playerShot();
  playerMove();

  clearEnemy();
  drawEnemy("-");
  enemyMove();
}

void playerShot()
{
  bool keyUp = digitalRead(SHOT_BUTTON_PIN);

  if (!keyUp)
  {
    tone(BUZZER_PIN, 3500, 20);
  }
}

void playerMove()
{
  bool topKeyUp = digitalRead(PLAYER_TOP_PIN);
  bool bottomKeyUp = digitalRead(PLAYER_BOTTOM_PIN);

  if (!topKeyUp)
  {
    setPlayerPosition(1);
  }

  if (!bottomKeyUp)
  {
    setPlayerPosition(0);
  }

  clearPlayer();
  drawPlayer();
}

void setPlayerPosition(byte position)
{
  // Serial.print(playerVertical);
  playerVertical = position;
  tone(BUZZER_PIN, 2000, 20);
}

void clearPlayer()
{
  for (byte i = 0; i < 2; i++)
  {
    lcd.setCursor(3, i);
    lcd.print(" ");
  }
}

void drawPlayer()
{
  lcd.setCursor(3, playerVertical);
  lcd.print("E");
}

void clearEnemy()
{
  lcd.setCursor(18 - enemyPosition1, 1);
  lcd.print(" ");
}

void drawEnemy(String ch)
{
  lcd.setCursor(17 - enemyPosition1, 1);
  lcd.print(ch);
}

void enemyMove()
{
  delay(200);
  // Слева экрана будет свободно 3 ячейки.
  enemyPosition1 = (enemyPosition1 + 1) % 15;
}
