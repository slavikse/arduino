#include <math.h>

const int FIRST_LED_PIN = 2;
const int LED_COUNT = 10;

void setup()
{
  Serial.begin(9600);

  for (int i = 0; i < LED_COUNT; i++)
  {
    pinMode(FIRST_LED_PIN + i, OUTPUT);
  }
}

void loop()
{
  float voltage = analogRead(A0) * 5.0 / 1023.0;
  float temperature = 1.0 / (log(voltage / 2.5) / 4300.0 + 1.0 / 298.0) - 273.0;

  for (int i = 0; i < LED_COUNT; i++)
  {
    bool enableSegment = temperature >= 21 + i;
    Serial.println(temperature);
    digitalWrite(FIRST_LED_PIN + i, enableSegment);
  }
}
