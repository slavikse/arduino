#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const byte SHOT_BUTTON_PIN = 10;
const byte BUZZER_PIN = 6;

const byte PLAYER_HEALTH_PIN = 13;
const byte PLAYER_TOP_PIN = 8;
const byte PLAYER_BOTTOM_PIN = 9;

// Размеры экрана.
const byte horizontal = 16;
const byte vertical = 2;

const byte cycleTime = 200;

// 0 - Вверху, 1 - Внизу.
byte playerVertical = 0;
byte score = 0;
byte health = 3;

const byte shotCost = 1;
const byte healthCost = 5;

// 0 - значение инвертируется на выводе.
// Верхний.
byte enemyPosition0 = 0;
// Нижний.
byte enemyPosition1 = 0;

// Начальные позиции врагов. Смещены, чтобы не следовали в один ряд с первого прохода.
const byte enemyShift0 = 19;
const byte enemyShift1 = 16;

// Нужно сохранять разницу: enemyCursorShift == enemyDrawShift + 1.
const byte enemyCursorShift = 3;
const byte enemyDrawShift = 2;

void setup()
{
  // Serial.begin(9600);
  // Serial.print("message");

  screenSetup();
  setupStatusBar();

  // Приветственная мелодия.
  tone(BUZZER_PIN, 1600, 800);
  delay(100);
  tone(BUZZER_PIN, 700, 600);
  delay(80);
  tone(BUZZER_PIN, 1500, 1000);
  delay(100);
  tone(BUZZER_PIN, 700, 600);
  delay(80);
  tone(BUZZER_PIN, 1800, 700);
  delay(60);
  tone(BUZZER_PIN, 1800, 700);
  delay(100);
  tone(BUZZER_PIN, 2000, 1000);
}

void screenSetup()
{
  lcd.begin(horizontal, vertical);

  lcd.setCursor(5, 0);
  lcd.print("Hi man!");

  lcd.setCursor(1, 1);
  lcd.print("I am ARKANOID!");

  delay(3000);

  lcd.clear();
}

void setupStatusBar()
{
  // Вывод строки с набранными баллами.
  lcd.setCursor(0, 0);
  lcd.print("$");
  setScore();

  // Вывод строки с количеством здоровья.
  lcd.setCursor(0, 1);
  lcd.print("H");
  setHealth();
}

void loop()
{
  hasIntersection();

  playerShot();
  playerBuyHealth();
  playerMove();

  clearEnemies();
  drawEnemy("*");
  enemyMove();
}

void setScore()
{
  lcd.setCursor(1, 0);
  lcd.print(score);
}

void setHealth()
{
  lcd.setCursor(1, 1);
  lcd.print(health);
}

void hasIntersection()
{
  // Будет равен -1, когда достигнет возможного расположения игрока.
  if (enemyPosition0 - enemyShift0 == -1)
  {
    intersection(0);
  }
  else if (enemyPosition1 - enemyShift1 == -1)
  {
    intersection(1);
  }
}

void intersection(byte position)
{
  if (playerVertical == position)
  {
    changeHealth(-1);

    if (health == 0)
    {
      gameOver();
    }
  }
  else
  {
    changeScore(+1);
  }
}

void changeHealth(byte num)
{
  health += num;

  // Защита от переполнения.
  if (health >= 99)
  {
    health = 0;
  }

  setHealth();
  tone(BUZZER_PIN, 1000, 100);
}

void changeScore(byte num)
{
  score += num;

  // Защита от переполнения.
  if (score >= 99)
  {
    score = 0;
  }

  setScore();
}

// Перезапуск через кнопку сброса на плате.
void gameOver()
{
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Game Over!");
  lcd.setCursor(7, 1);
  lcd.print(">_<");

  tone(BUZZER_PIN, 2000, 800);
  delay(100);
  tone(BUZZER_PIN, 1500, 1000);
  delay(100);
  tone(BUZZER_PIN, 2000, 800);

  delay(99999999999);
}

void playerShot()
{
  bool keyUp = digitalRead(SHOT_BUTTON_PIN);

  if (!keyUp && score >= shotCost)
  {
    changeScore(-shotCost);

    if (playerVertical == 0)
    {
      enemyPosition0 = 0;
    }
    else if (playerVertical == 1)
    {
      enemyPosition1 = 0;
    }

    // Первые 4 ячейки служебные.
    // Блокирующий. Scheduler - не работает с UNO. Но оно того стоит. Прерывания??? \oO/
    for (byte i = 4; i < horizontal; i++)
    {
      tone(BUZZER_PIN, 6000, 50);

      lcd.setCursor(i, playerVertical);
      lcd.print("-");
      delay(100);
      lcd.setCursor(i, playerVertical);
      lcd.print(" ");
    }
  }
}

void playerBuyHealth()
{
  bool healthKeyUp = digitalRead(PLAYER_HEALTH_PIN);

  if (!healthKeyUp && score >= healthCost)
  {
    changeScore(-healthCost);
    changeHealth(+1);

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
  lcd.print(">");
}

// Очищает текущие ячейки, рисует в следующих.
void clearEnemies()
{
  clearEnemy0();
  clearEnemy1();
}

void clearEnemy0()
{
  lcd.setCursor(enemyShift0 + enemyCursorShift - enemyPosition0, 0);
  lcd.print(" ");
}

void clearEnemy1()
{
  lcd.setCursor(enemyShift1 + enemyCursorShift - enemyPosition1, 1);
  lcd.print(" ");
}

void drawEnemy(String ch)
{
  lcd.setCursor(enemyShift0 + enemyDrawShift - enemyPosition0, 0);
  lcd.print(ch);

  lcd.setCursor(enemyShift1 + enemyDrawShift - enemyPosition1, 1);
  lcd.print(ch);
}

void enemyMove()
{
  delay(cycleTime);

  enemyPosition0 = (enemyPosition0 + 1) % enemyShift0;
  enemyPosition1 = (enemyPosition1 + 1) % enemyShift1;
}
